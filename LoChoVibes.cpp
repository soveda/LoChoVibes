//
//  LoChoVibes.cpp
//
//
//  Created by Adrian Vos on 25/05/2026.
//


#include "ComputerCard.h"

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

    int16_t delayBufferL[DELAY_SIZE];
    int16_t delayBufferR[DELAY_SIZE];

    int32_t writeIndex = 0;

    int32_t lfoPhase = 0;
    LFOShape currentShape = Triangle;

    int32_t overlayTimer = 0;

    virtual void ProcessSample()
    {
        // Read audio inputs.
        // Workshop Computer audio range is approximately
        // -2048 to +2047.
        int32_t inL = AudioIn1();
        int32_t inR = AudioIn2();

        // Read controls.
        int32_t rateKnob = KnobVal(Knob::Main);
        int32_t depthKnob = KnobVal(Knob::X);
        int32_t characterKnob = KnobVal(Knob::Y);

        // Switch handling.
        // Down position is momentary and used to
        // cycle LFO shapes.
        if (SwitchChanged() && SwitchVal() == Switch::Down)
        {
            currentShape = static_cast<LFOShape>((currentShape + 1) % 3);
            overlayTimer = SAMPLE_RATE / 2;
        }

        bool vibratoMode = (SwitchVal() == Switch::Middle);

        // Basic soft saturation.
        // This is intentionally simple for now.
        inL = SoftClip(inL, characterKnob);
        inR = SoftClip(inR, characterKnob);

        // Generate modulation waveform.
        int32_t lfo = GenerateLFO();

        // Delay modulation depth.
        int32_t depth = depthKnob >> 3;

        // Create stereo offsets.
        int32_t delayL = 128 + ((lfo * depth) >> 12);
        int32_t delayR = 128 - ((lfo * depth) >> 12);

        int32_t outL = ReadDelay(delayBufferL, delayL);
        int32_t outR = ReadDelay(delayBufferR, delayR);

        // Chorus keeps dry signal.
        // Vibrato becomes fully wet.
        if (!vibratoMode)
        {
            outL = (outL + inL) >> 1;
            outR = (outR + inR) >> 1;
        }

        // Store incoming audio into delay lines.
        delayBufferL[writeIndex] = inL;
        delayBufferR[writeIndex] = inR;

        writeIndex++;
        writeIndex &= (DELAY_SIZE - 1);

        // Update LEDs.
        UpdateLEDs(rateKnob, depthKnob, lfo);

        AudioOut1(outL);
        AudioOut2(outR);
    }

private:

    int32_t SoftClip(int32_t input, int32_t amount)
    {
        // Very simple saturation stage.
        // This will likely evolve significantly.

        int32_t drive = 2048 + amount;
        int32_t x = (input * drive) >> 11;

        if (x > 2047)
            x = 2047;

        if (x < -2048)
            x = -2048;

        return x;
    }

    int32_t GenerateLFO()
    {
        // Advance phase accumulator.
        // Exact scaling still to be tuned.

        lfoPhase += 2000;

        switch(currentShape)
        {
            case Triangle:
            {
                int32_t tri = (lfoPhase >> 19) & 0x1FFF;

                if (tri > 4095)
                    tri = 8191 - tri;

                return tri - 2048;
            }

            case Sine:
            {
                // Placeholder.
                // Replace with lookup table later.
                int32_t tri = (lfoPhase >> 20) & 4095;
                return tri - 2048;
            }

            case Square:
            {
                return (lfoPhase & 0x80000000) ? 2047 : -2048;
            }
        }

        return 0;
    }

    int32_t ReadDelay(int16_t* buffer, int32_t delaySamples)
    {
        int32_t readIndex = writeIndex - delaySamples;

        while (readIndex < 0)
            readIndex += DELAY_SIZE;

        return buffer[readIndex & (DELAY_SIZE - 1)];
    }

    void UpdateLEDs(int32_t rate, int32_t depth, int32_t lfo)
    {
        // Temporary overlay mode.
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

        // Normal display mode.
        // These mappings are placeholders.

        LedBrightness(0, rate);
        LedBrightness(2, depth);
        LedBrightness(4, lfo + 2048);

        LedBrightness(1, depth);
        LedBrightness(3, rate);
        LedBrightness(5, 2048 - lfo);
    }
};

int main()
{
    LoChoVibes card;
    card.Run();
}
