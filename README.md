# LoCho Vibes

LoCho Vibes is a stereo lo-fi chorus and vibrato effect for the Music Thing Modular Workshop Computer.

Inspired by the unstable movement and degraded character of the ZVEX Lo-Fi Junky, this card focuses on animated pitch movement, stereo widening, soft saturation, compression-style coloration, and broken cassette-style modulation.

---

# Features

* Stereo chorus and vibrato modes
* Triangle, sine, and slow drift LFO
* Bipolar Character control
* Lo-fi degradation and compression behaviour
* Soft tape-style saturation
* Stereo modulated delay architecture
* Stereo chorus widening
* External pulse-clockable LFO
* CV modulation inputs
* Dual animated CV LFO outputs
* Temporary LED overlay for LFO shape selection

---

# Controls

| Control                 | Function                        |
| ----------------------- | ------------------------------- |
| Main                    | Modulation rate                 |
| X                       | Modulation depth                |
| Y                       | Character (Lo-Fi ↔ Compression) |
| Switch Up               | Vibrato mode                    |
| Switch Middle           | Chorus mode                     |
| Switch Down (momentary) | Cycle LFO shape                 |

---

# Inputs & Outputs

| Input / Output | Function                       |
| -------------- | ------------------------------ |
| Audio In 1 + 2 | Mono summed audio input        |
| Audio Out 1    | Left audio output              |
| Audio Out 2    | Right audio output             |
| CV In 1        | Modulates modulation depth     |
| CV In 2        | Modulates Character control    |
| Pulse In 1     | External LFO clock input       |
| CV Out 1       | Main LFO modulation output     |
| CV Out 2       | Inverted LFO modulation output |

---

# External Clocking

LoCho Vibes supports external pulse clocking via Pulse In 1.

When an external pulse source is connected:

* the internal LFO synchronizes to incoming clock pulses
* modulation speed follows the pulse interval
* clock transitions are smoothed internally
* if clock pulses stop, the module automatically returns to internal modulation

This allows synchronized chorus and vibrato movement with sequencers, trigger generators, clocks, and rhythm systems.

---

# CV Modulation

## CV In 1 — Depth Modulation

CV In 1 modulates the X control.

This allows external control over:

* modulation intensity
* stereo width movement
* vibrato depth
* dynamic chorus animation

Incoming CV is internally attenuated for musical modulation response.

## CV In 2 — Character Modulation

CV In 2 modulates the Y Character control.

This allows dynamic movement between:

* degraded cassette-style saturation
* neutral response
* compressed modulation texture

Slow CV sources can create evolving tonal drift while faster modulation produces unstable and animated textures.

---

# CV Outputs

LoCho Vibes outputs the internal LFO as control voltage signals.

## CV Out 1

Outputs the main LFO waveform.

## CV Out 2

Outputs an inverted version of the LFO.

These outputs can be used for:

* filter modulation
* stereo panning
* synchronized movement elsewhere in a patch
* clocked animation of external modules
* opposing modulation movement

The output reflects the currently selected waveform and external clock synchronization state.

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

| LED   | Function           |
| ----- | ------------------ |
| LED 0 | Modulation rate    |
| LED 1 | Modulation depth   |
| LED 2 | Lo-fi amount       |
| LED 3 | Compression amount |
| LED 4 | LFO phase          |
| LED 5 | Inverted LFO phase |

LED brightness reflects both modulation movement and current parameter state.

---

# Internal Processing

Internally the effect uses:

* stereo modulated delay lines
* continuously running LFO modulation
* smoothed waveform transitions
* tape-style soft clipping
* soft limiting and saturation stages
* clock-synchronized modulation behaviour
* bipolar character processing

The signal path is intentionally voiced toward unstable analog tape movement rather than pristine digital chorus.

---

# Current Status

Still testing code
