<img width="3456" height="4608" alt="Wireless Audio Transmission" src="https://github.com/user-attachments/assets/a20773ef-056d-4886-9546-55cb2278bbc0" />

# Wireless Audio Transmission Walkie-Talkie

A multi-course integration project combining embedded systems, communication engineering, DSP, and data communication concepts into a working Arduino-based walkie-talkie.

## Overview

This project implements a two-unit wireless walkie-talkie system using Arduino UNO microcontrollers and NRF24L01+PA+LNA RF modules. It was developed as a capstone integration project and has been approved by the course supervisor.

## Hardware

| Component | Purpose |
|---|---|
| Arduino UNO (x2) | Main microcontroller for each unit |
| NRF24L01+PA+LNA | Long-range wireless RF communication |
| MAX9814 | Microphone amplifier with AGC |
| PAM8403 | Class-D audio amplifier |
| 4Ω 10W Speaker | Audio output |

## Project Status

- ✅ **Bidirectional LED wireless communication** — working
- ✅ **Audio loopback** (mic → amp → speaker, wired) — working
- ✅ **Wireless audio transmission** — fully functional, clear two-way voice

### Notes

Both units transmit and receive voice clearly over the nRF24L01+PA+LNA link. The earlier packet sync / power instability issue was resolved by switching to a 9V power adapter (reducing regulator heat) and correcting the RC audio filter (47Ω resistor + 1µF capacitor) and mic gain settings.

One expected behavior: bringing both units very close together causes audio feedback/echo (acoustic feedback loop, not a hardware fault) — keep them a room apart during testing/demo.

See [`PROJECT_LOG.md`](./PROJECT_LOG.md) for the full build log, issues hit, and fixes applied.

## Repository Structure

```
├── walkie_talkie_unit_1/   # Final code for unit 1
├── walkie_talkie_unit_2/   # Final code for unit 2
├── uni_TX_LED/             # LED transmit test
├── uni_RX_LED/             # LED receive test
├── bi_unit1_LED/           # Bidirectional LED test - unit 1
├── bi_unit2_LED/           # Bidirectional LED test - unit 2
├── Mic_Input/              # Microphone input test
├── mic_n_speaker_test/     # Audio loopback test
└── WAT.docx                # Project documentation
```

## Course Integration

This project draws on concepts from:
- **Embedded Systems** — microcontroller programming, peripheral interfacing
- **Communication Engineering** — RF transmission, modulation
- **Digital Signal Processing** — audio signal handling
- **Data Communication** — packet-based wireless protocols

 [Wireless Audio Transmission.pdf](https://github.com/user-attachments/files/31242341/Wireless.Audio.Transmission.pdf)

