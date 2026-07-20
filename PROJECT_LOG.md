# Project Log — Wireless Audio Transmission Walkie-Talkie

A running log of the build, problems hit, and fixes applied. Update this as the project evolves.

## Status: ✅ Fully Functional

Both units transmit and receive voice clearly. Known limitation: bringing the two units close together causes audio feedback/echo (expected acoustic feedback, not a fault).

---

## Parts List

- 2x Arduino UNO
- 2x MAX9814 microphone module
- 2x PAM8403 amplifier
- 2x nRF24L01+ PA/LNA (external antenna)
- 2x 4Ω 10W speaker
- Resistors: 220Ω (later swapped to 47Ω), 1000Ω, 10kΩ
- Capacitors: 1µF 50V, 10µF 50V
- 2x push buttons (PTT)
- 2x breadboard + breadboard power supply modules (3.3V/5V, originally 12V input)
- 9V power adapter (final, replacing 12V)

## Software

- Arduino IDE
- Libraries: `RF24` (TMRh20), `RF24Audio` (TMRh20, installed manually via ZIP since not in Library Manager)

## Wiring Summary

**nRF24L01+ PA/LNA** (SPI): VCC→3.3V rail, GND→GND, CE→D7, CSN→D8, SCK→D13, MOSI→D11, MISO→D12. 10µF decoupling capacitor across VCC/GND at the module.

**MAX9814 mic**: VDD→5V, GND→GND, OUT→A0 (hardcoded by RF24Audio library).

**PAM8403 amp**: 5V→5V rail, GND→GND rail. Audio in: Arduino D9 → resistor → Pin 5 (L IN). Filter cap between Pin 5 and Pin 6 (GND). Speaker on Pins 1/2.

**PTT button**: one leg to D3, other to GND. Uses `INPUT_PULLUP` (LOW = pressed).

**Common ground**: 3.3V rail GND and 5V rail GND bridged together, then tied to Arduino GND.

---

## Issues Encountered & Fixes

| Issue | Cause | Fix |
|---|---|---|
| `RF24Audio.h: No such file` | Library not in Arduino Library Manager index | Downloaded ZIP from GitHub, installed via *Sketch → Include Library → Add .ZIP Library* |
| `isTransmitting()` not a member | Tutorial code used a non-existent library method | Added a custom `bool isTransmitting` flag in the sketch to track state manually |
| PTT logic inverted | `INPUT_PULLUP` means LOW = pressed, code checked HIGH | Flipped condition to check for `LOW` |
| Total silence, no audio at all | Multiple causes — diagnosed step by step | See below |
| → Amplifier silent even when touching input pin | Bad ground/power connection | Verified 5V/GND wiring to PAM8403 — resolved |
| → Radio not detected | Loose SPI wiring | Added `radio.isChipConnected()` diagnostic — confirmed wiring was actually fine |
| → Radio worked but crashed after ~5 sec of transmission | AMS1117 regulator on breadboard power module overheating (12V→5V drop = ~2.1W heat, thermal shutdown) | Reduced radio power to `RF24_PA_MIN` temporarily; ultimately fixed by lowering input voltage |
| Power supply repeatedly cutting out | Same AMS1117 thermal shutdown, confirmed by touch-testing the regulator | Switched from 12V adapter to **9V adapter** (heat dropped to ~0.75W, well within safe limits) |
| Audio was pure static/humming, no voice | Wrong resistor used (1000Ω instead of 220Ω) — RC filter cutoff dropped to ~159 Hz, blocking voice frequencies | Recalculated filter for telephony clarity (~2–3.4 kHz cutoff); switched to **47Ω resistor + 1µF capacitor** |
| Loud screeching noise on PTT press | Acoustic feedback (Larsen effect) — units too close together, mic picking up own speaker's output | Physical separation between units; lowered `rfAudio.setVolume()` from 5 to 3 |
| Voice audible but muffled/distorted | MAX9814 gain too high (default 60dB), causing clipping | Connected MAX9814 **GAIN pin to VCC** to drop gain to 40dB; also re-checked filter capacitor polarity (electrolytic cap was backwards on one unit) |
| Voice unclear after capacitor fix | Capacitor polarity — negative leg must go to GND (Pin 6), positive to L IN (Pin 5) | Rewired with correct polarity — **voice became clear** |

## Final Working Configuration

- Power: 9V adapter → breadboard regulator (stable, no thermal shutdown)
- Radio: `RF24_PA_HIGH` (safe now that power supply is stable)
- Audio filter: 47Ω resistor + 1µF capacitor (correct polarity)
- Mic gain: MAX9814 GAIN pin tied to VCC (40dB)
- Volume: `rfAudio.setVolume(3)` to avoid feedback
- Result: Clear two-way voice transmission. Echo/feedback only occurs when units are placed very close together — expected acoustic behavior, not a defect.

---

## Next Steps / Ideas

- Move from breadboard to a soldered/perfboard build for the final presentation
- Design an enclosure (3D printed or foam board/acrylic chassis)
- Add TX/RX status LEDs for visual feedback during demo
- Prepare system block diagram and filter-response graph for presentation slides
