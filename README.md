# LoCho Vibes

LoCho Vibes is a stereo lo-fi chorus and vibrato effect for the Music Thing Modular Workshop Computer.

Inspired by the unstable movement and degraded character of the ZVEX Lo-Fi Junky, this card focuses on animated pitch movement, stereo widening, soft saturation, compression-style coloration, and broken cassette-style modulation.

---

# Features

* Stereo chorus and vibrato modes
* Triangle, sine, and smoothed square-wave LFOs
* Bipolar Character control
* Lo-fi degradation and compression behaviour
* Soft tape-style saturation
* Stereo modulated delay architecture
* Stereo chorus widening
* Temporary LED overlay for LFO shape selection

---

# Controls

| Control                 | Function                          |
| ----------------------- | --------------------------------- |
| Main                    | Modulation rate                   |
| X                       | Modulation depth                  |
| Y                       | Character (Lo-Fi ↔ Compression)   |
| Switch Up               | Vibrato mode                       |
| Switch Middle           | Chorus mode                      |
| Switch Down (momentary) | Cycle LFO shape                   |

---

# Character Control

The Character knob is bipolar.

## Counter-Clockwise — Lo-Fi

Turning the control counter-clockwise introduces:

* softer headroom
* degraded saturation
* darker transient response
* unstable cassette-style texture
* reduced signal clarity


## Center Position — Neutral

At approximately 12 o’clock:

* saturation becomes minimal
* dynamics remain mostly unchanged
* modulation becomes cleaner and more transparent

## Clockwise — Compression

Turning clockwise introduces:

* gain increase
* soft limiting
* compressed transient response
* denser modulation texture
* more forward chorus character
---

# Modes

## Chorus

In chorus mode:

* dry signal remains blended with the delay line
* modulation is intentionally restrained
* stereo delay offsets widen the image
* chorus remains relatively subtle and musical

The chorus voicing is designed to sit closer to vintage modulation pedals and tape chorus than exaggerated modern DSP chorus.

## Vibrato

In vibrato mode:

* output becomes fully wet
* dry signal is completely removed
* pitch modulation becomes much more obvious
* behaves more like warped tape playback or unstable cassette transport

At higher depths this mode can become heavily seasick and degraded.

---

# LFO Shapes

## Triangle

Smooth and classic.

Good for traditional chorus movement and subtle stereo animation.

## Sine

Softer and more liquid.

Useful for drifting modulation and gentler tape-style wobble.

## Square

Abrupt stepped modulation with smoothing applied internally.

Produces broken cassette-style pitch jumps, unstable stutter movement, and aggressive lo-fi modulation textures.

---

# Stereo Behaviour

LoCho Vibes converts incoming audio to mono internally before generating a stereo modulation field.

The left and right channels use different delay offsets and opposite modulation movement to create:

* stereo widening
* animated spatial movement
* unstable tape-style drift
* asymmetrical chorus behaviour
---

# LED Behaviour

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
* LEDs animate with the active LFO

---



# Current Status

LoCho Vibes is now in a stable and musically usable state.

