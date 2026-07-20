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
- ⚠️ **Wireless audio transmission** — in progress

### Known Issue

Wireless audio transmission is currently unresolved. Symptoms point to packet sync corruption, likely caused by power instability on the NRF24L01+PA+LNA modules under load. Next steps include adding dedicated decoupling capacitors and/or a separate regulated power supply for the RF modules.

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
- **Theory of Computation** — system/protocol design

## Author

Developed by [your name] — Department of ICT, Mawlana Bhashani Science and Technology University (MBSTU)
