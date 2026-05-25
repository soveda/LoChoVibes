# LoCho Vibes

LoCho Vibes is a stereo lo-fi chorus and vibrato effect for the Music Thing Modular Workshop Computer.

Inspired by the unstable movement and degraded character of the [ZVEX Lo-Fi Junky](https://zvexmodular.com/lo-fi-junky/?utm_source=chatgpt.com), this card focuses on animated pitch movement, stereo widening, soft saturation, and broken cassette-style modulation.

This is not a clean studio chorus.

It is designed to wobble, smear, drift, and occasionally misbehave in musically useful ways.

---

# Features

* Stereo chorus and vibrato modes
* Triangle, sine, and square-wave LFOs
* Abrupt square-wave “stutter” modulation
* Soft saturation stage
* Stereo modulated delay architecture
* Temporary LED overlay for LFO shape selection
* Timing-safe integer DSP
* Designed specifically for Workshop Computer hardware character

---

# Controls

| Control                 | Function               |
| ----------------------- | ---------------------- |
| Main                    | Modulation rate        |
| X                       | Modulation depth       |
| Y                       | Saturation / character |
| Switch Up               | Chorus mode            |
| Switch Middle           | Vibrato mode           |
| Switch Down (momentary) | Cycle LFO shape        |

---

# Modes

## Chorus

In chorus mode:

* Dry signal remains mixed with the delay line
* Left and right modulation phases differ
* Produces stereo width and motion
* Works well for subtle widening or unstable tape chorus

## Vibrato

In vibrato mode:

* Output becomes fully wet
* Pitch modulation becomes much more obvious
* Behaves more like warped tape or unstable cassette playback

---

# LFO Shapes

## Triangle

Smooth and classic.

Good for traditional chorus movement.

## Sine

Softer and more liquid.

Useful for gentle vibrato and drifting modulation.

## Square

Abrupt delay jumps.

Creates the broken stutter texture associated with warped cassette playback and the Lo-Fi Junky sound.

The clicks are intentional.

---

# LED Behaviour

The LEDs perform two different jobs.

## Shape Display Overlay

When the switch is tapped downward:

* the LFO shape changes
* LEDs briefly display the selected waveform
* after a short timeout the LEDs return to normal mode

| Shape    | LEDs       |
| -------- | ---------- |
| Triangle | Top row    |
| Sine     | Middle row |
| Square   | Bottom row |

## Normal Display Mode

During normal operation:

* LEDs display modulation activity
* brightness reflects movement and parameter state
* mappings may evolve during tuning

---

# DSP Notes

LoCho Vibes uses:

* fixed-point DSP
* integer arithmetic
* short modulated delay lines
* lightweight interpolation
* soft clipping

The RP2040 has no hardware floating point, so the design avoids expensive floating-point DSP inside `ProcessSample()`.

The implementation intentionally preserves some roughness and modulation texture rather than aggressively smoothing everything away.

---

# Technical Notes

* Audio runs at 48kHz using the ComputerCard framework
* Designed for ComputerCard v0.3.0
* Optimised for timing stability on Workshop Computer hardware
* Intended to run using:

  * `copy_to_ram`
  * `PICO_XOSC_STARTUP_DELAY_MULTIPLIER=64`

---

# Current Status

Early architecture and DSP scaffold.

Current focus:

* modulation behaviour
* stereo movement
* LFO interaction
* Workshop UI behaviour
* core lo-fi character

Future possibilities may include:

* noise injection
* tape dropouts
* clock instability
* compander-style compression
* CV modulation
* pulse-synchronised modulation
* feedback textures

---

# Build Notes

Recommended CMake options:

```cmake
pico_set_binary_type(locho_vibes copy_to_ram)

target_compile_definitions(locho_vibes PRIVATE
    PICO_XOSC_STARTUP_DELAY_MULTIPLIER=64
)
```

---

# Platform

Built for the Music Thing Modular Workshop Computer.

* [Workshop Computer](https://www.musicthing.co.uk/workshopsystem/?utm_source=chatgpt.com)
* [Program Cards](https://www.musicthing.co.uk/Computer_Program_Cards/?utm_source=chatgpt.com)
* [Workshop Computer Cards Repository](https://tomwhitwell.github.io/Workshop_Computer/?utm_source=chatgpt.com)
