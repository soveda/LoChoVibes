//
//  LoChoVibes.cpp
//
//
//  Created by Adrian Vos on 25/05/2026.
//

#include "ComputerCard.h"
#include <cstdint>

class LoChoVibes : public ComputerCard
{
public:

    enum LFOShape
    {
        Triangle,
        Sine,
        Square
    };

    static constexpr int32_t SAMPLE_RATE = 48000;
    static constexpr int32_t DELAY_SIZE = 2048;
    static constexpr uint32_t SINE_TABLE_SIZE = 256;

    int16_t delayBufferL[DELAY_SIZE] = {};
    int16_t delayBufferR[DELAY_SIZE] = {};

    int32_t writeIndex = 0;

    // Unsigned overflow is intentional for cyclic LFO phase.
    uint32_t lfoPhase = 0;

    LFOShape currentShape = Triangle;

    int32_t overlayTimer = 0;

    // 256-point sine lookup table.
    // Range: -2047 to +2047

    static constexpr int16_t sineTable[SINE_TABLE_SIZE] =
    {
        0,   50,  100,  151,  201,  251,  300,  350,
      399,  449,  497,  546,  594,  642,  690,  737,
      783,  830,  875,  920,  965, 1009, 1052, 1095,
     1137, 1179, 1219, 1259, 1299, 1337, 1375, 1411,
     1447, 1483, 1517, 1550, 1582, 1614, 1644, 1674,
     1702, 1729, 1756, 1781, 1805, 1828, 1850, 1871,
     1891, 1910, 1927, 1944, 1959, 1973, 1986, 1997,
     2008, 2017, 2025, 2032, 2037, 2041, 2045, 2046,
     2047, 2046, 2045, 2041, 2037, 2032, 2025, 2017,
     2008, 1997, 1986, 1973, 1959, 1944, 1927, 1910,
     1891, 1871, 1850, 1828, 1805, 1781, 1756, 1729,
     1702, 1674, 1644, 1614, 1582, 1550, 1517, 1483,
     1447, 1411, 1375, 1337, 1299, 1259, 1219, 1179,
     1137, 1095, 1052, 1009,  965,  920,  875,  830,
      783,  737,  690,  642,  594,  546,  497,  449,
      399,  350,  300,  251,  201,  151,  100,   50,
        0,  -50, -100, -151, -201, -251, -300, -350,
     -399, -449, -497, -546, -594, -642, -690, -737,
     -783, -830, -875, -920, -965,-1009,-1052,-1095,
    -1137,-1179,-1219,-1259,-1299,-1337,-1375,-1411,
    -1447,-1483,-1517,-1550,-1582,-1614,-1644,-1674,
    -1702,-1729,-1756,-1781,-1805,-1828,-1850,-1871,
    -1891,-1910,-1927,-1944,-1959,-1973,-1986,-1997,
    -2008,-2017,-2025,-2032,-2037,-2041,-2045,-2046,
    -2047,-2046,-2045,-2041,-2037,-2032,-2025,-2017,
    -2008,-1997,-1986,-1973,-1959,-1944,-1927,-1910,
    -1891,-1871,-1850,-1828,-1805,-1781,-1756,-1729,
    -1702,-1674,-1644,-1614,-1582,-1550,-1517,-1483,
    -1447,-1411,-1375,-1337,-1299,-1259,-1219,-1179,
    -1137,-1095,-1052,-1009, -965, -920, -875, -830,
     -783, -737, -690, -642, -594, -546, -497, -449,
     -399, -350, -300, -251, -201, -151, -100,  -50

    };

    void ProcessSample() override
    {
        // Read audio inputs.
        // Workshop Computer audio range:
        // approximately -2048 to +2047.

        int32_t mono =
            (AudioIn1() + AudioIn2()) >> 1;

        int32_t inL = mono;
        int32_t inR = mono;
        // Read controls.

        int32_t rateKnob = KnobVal(Knob::Main);
        int32_t depthKnob = KnobVal(Knob::X);
        int32_t characterKnob = KnobVal(Knob::Y);

        // Switch handling.
        //
        // Up      = Chorus
        // Middle  = Vibrato
        // Down    = Momentary LFO shape select

        if (SwitchChanged() && SwitchVal() == Switch::Down)
        {
            currentShape =
                static_cast<LFOShape>(
                    (static_cast<int>(currentShape) + 1) % 3
                );

            overlayTimer = SAMPLE_RATE / 2;
        }

        bool vibratoMode =
            (SwitchVal() == Switch::Middle);

        // Saturation stage.

        inL = SoftClip(inL, characterKnob);
        inR = SoftClip(inR, characterKnob);

        // Generate modulation waveform.

        int32_t lfo = GenerateLFO(rateKnob);

        // Delay modulation depth.

        int32_t depth =
            16 + depthKnob;

        int32_t modulation =
            (lfo * depth) >> 10;

        // Stereo modulation offsets.

        int32_t delayL =
            48 + modulation;

        int32_t delayR =
            96 - modulation;

        // Prevent invalid negative delay values.

        if (delayL < 1)
            delayL = 1;

        if (delayR < 1)
            delayR = 1;

        int32_t outL =
            ReadDelay(delayBufferL, delayL);

        int32_t outR =
            ReadDelay(delayBufferR, delayR);

        // Chorus retains dry signal.
        // Vibrato is fully wet.

        if (!vibratoMode)
        {
            outL =
                ((inL * 3) + (outL * 2)) / 5;

            outR =
                ((inR * 3) + (outR * 2)) / 5;
        }

        // Write incoming audio into delay buffers.

        delayBufferL[writeIndex] = inL;
        delayBufferR[writeIndex] = inR;

        writeIndex++;
        writeIndex &= (DELAY_SIZE - 1);

        // LED handling.

        UpdateLEDs(rateKnob, depthKnob, lfo);

        // Output audio.

        AudioOut1(ClampAudio(outL));
        AudioOut2(ClampAudio(outR));
    }

private:

    int16_t ClampAudio(int32_t v)
    {
        if (v > 2047)
            return 2047;

        if (v < -2048)
            return -2048;

        return static_cast<int16_t>(v);
    }

    int32_t SoftClip(int32_t input, int32_t amount)
    {
        // Gentle drive scaling.

        int32_t drive =
            2048 + (amount >> 3);

        int32_t x =
            (input * drive) >> 11;

        // Simple soft knee.

        if (x > 1536)
        {
            x = 1536 + ((x - 1536) >> 2);
        }

        if (x < -1536)
        {
            x = -1536 + ((x + 1536) >> 2);
        }

        return x;
    }

    int32_t GenerateLFO(int32_t rate)
    {
        // Rate scaling.
        // Will likely need tuning by ear.

        lfoPhase += 1500 + (rate << 9);

        switch(currentShape)
        {
            case Triangle:
            {
                int32_t tri =
                    (lfoPhase >> 19) & 0x1FFF;

                if (tri > 4095)
                    tri = 8191 - tri;

                return tri - 2048;
            }

            case Sine:
            {
                uint32_t index =
                    (lfoPhase >> 24) & 0xFF;

                return sineTable[index];
            }

            case Square:
            {
                return
                    (lfoPhase & 0x80000000)
                    ? 2047
                    : -2048;
            }
        }

        return 0;
    }

    int32_t ReadDelay(const int16_t* buffer,
                      int32_t delaySamples)
    {
        int32_t readIndex =
            writeIndex - delaySamples;

        while (readIndex < 0)
            readIndex += DELAY_SIZE;

        return
            buffer[
                readIndex &
                (DELAY_SIZE - 1)
            ];
    }

    uint16_t ClampLED(int32_t v)
    {
        if (v < 0)
            return 0;

        if (v > 4095)
            return 4095;

        return static_cast<uint16_t>(v);
    }

    void UpdateLEDs(int32_t rate,
                    int32_t depth,
                    int32_t lfo)
    {
        // Overlay display for shape selection.

        if (overlayTimer > 0)
        {
            overlayTimer--;

            LedOff(0);
            LedOff(1);
            LedOff(2);
            LedOff(3);
            LedOff(4);
            LedOff(5);

            switch(currentShape)
            {
                case Triangle:

                    LedOn(0);
                    LedOn(1);

                    break;

                case Sine:

                    LedOn(2);
                    LedOn(3);

                    break;

                case Square:

                    LedOn(4);
                    LedOn(5);

                    break;
            }

            return;
        }

        // Normal parameter display.

        LedBrightness(0, ClampLED(rate));
        LedBrightness(1, ClampLED(depth));

        LedBrightness(2, ClampLED(depth));
        LedBrightness(3, ClampLED(rate));

        LedBrightness(4,
            ClampLED(lfo + 2048));

        LedBrightness(5,
            ClampLED(2048 - lfo));
    }
};

int main()
{
    LoChoVibes card;
    card.Run();
}
