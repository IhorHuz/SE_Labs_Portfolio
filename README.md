# Software Engineering Labs Portfolio

## Overview

Hello to one and all. This repository contains the cumulative coursework and documentation for the Software Engineering lab series. The primary focus of this portfolio is the complete systems analysis, requirements engineering, and UML architectural modeling for a basic ESP32 Room Climate Station.

## Project Context: ESP32 Climate Station

The core project modeled in this repository is a headless IoT environmental monitor. The system utilizes an ESP32 microcontroller and an I2C SHTC3 sensor to read ambient conditions, logs a rolling 24-hour data buffer to internal SPIFFS memory, and integrates with the Telegram Bot API for remote alerting and commands.

## Repository Structure

This portfolio is organized chronologically by lab assignments, moving from initial requirements gathering to dynamic behavioral modeling:

- **`/Lab1_Requirement_Analysis`**
  Contains the initial system scope and the final Software Requirements Specification (SRS) document outlining all functional and non-functional engineering requirements.
- **`/Lab2_UseCase_Diagrams`**
  Contains high-level behavioral models establishing system boundaries and actor interactions (including supplementary models for ATM, Clinic, and Insurance systems).
- **`/Lab3_Class_Diagrams`**
  Contains the static object-oriented architecture and database relationship models.
- **`/Lab4_Behavioral_Diagrams`**
  Contains dynamic system models, including Chronological Sequence diagrams, State lifecycles, and business logic Activity diagrams.
- **`/Lab5_GitHub_Deployment`**
  The final deployment of this version-controlled portfolio.

## Tools & Standards Used

- **Documentation:** IEEE 830-1998 SRS Standards
- **Modeling:** UML 2.5 (Miro Board)
- **Version Control:** Git & GitHub
