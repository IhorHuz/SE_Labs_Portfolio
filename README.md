# Software Engineering Labs Portfolio

## Overview

Hello to one and all. This repository contains the cumulative coursework and documentation for the Software Engineering lab series. The primary focus of this portfolio is the complete systems analysis, requirements engineering, and UML architectural modeling for a basic ESP32 Room Climate Station.

## Project Context: ESP32 Climate Station

The core project modeled in this repository is a headless IoT environmental monitor. The system utilizes an ESP32 microcontroller and an I2C SHTC3 sensor to read ambient conditions, logs a rolling 24-hour data buffer to internal SPIFFS memory, and integrates with the Telegram Bot API for remote alerting and commands.

## Repository Structure

This portfolio is organized chronologically by lab assignments, moving from initial requirements gathering to dynamic behavioral modeling:

- **`/SRS`**
  Contains the complete version history of the Software Requirements Specification (SRS) documents (Versions 1-4 and the final PDF build). These documents outline all functional and non-functional engineering requirements.
- **`/LabEx`**
  Contains the UML architectural models divided by specific lab assignments:
  - `Lab2`: High-level Use Case diagrams establishing system boundaries and actor interactions.
  - `Lab3`: Static Class diagrams detailing object-oriented architecture and relationships.
  - `Lab4`: Dynamic behavioral models (Sequence, State, and Activity diagrams).
- **`/Project`**
  Reserved for the core project files and associated assets for the final system deployment.

## Deployment Guide — ESP32 Climate Station

### Prerequisites

- Hardware: ESP32 Dev Board, SHTC3 sensor, 16×2 I2C LCD, button on GPIO 4
- Software: VS Code + [PlatformIO extension](https://platformio.org/install), or PlatformIO CLI
- Telegram bot token and chat ID

### Setup & Configuration

1. Open the `Project/` folder in VS Code (PlatformIO auto-detects it)
2. Copy your credentials into `Project/include/env.h`:
   ```cpp
   #define SECRET_SSID "your_wifi"
   #define SECRET_PASS "your_password"
   #define SECRET_BOT_TOKEN "your_token"
   #define SECRET_CHAT_ID "your_chat_id"
   ```

## Tools & Standards Used

- **Documentation:** IEEE 830-1998 SRS Standards
- **Modeling:** UML 2.5 (Miro Board)
- **Version Control:** Git & GitHub
