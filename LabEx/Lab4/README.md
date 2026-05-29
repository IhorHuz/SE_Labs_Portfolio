# Lab 4: UML Dynamic Diagrams (Sequence, State, Activity)

## Overview

This folder contains the dynamic UML diagrams generated for Lab 4.

Previous labs focused on static architecture (what the system _is_). This lab focuses entirely on dynamic behavior (what the system _does_ over time). It utilizes Sequence diagrams for chronological object interaction, State diagrams for object lifecycles, and Activity diagrams for complex business logic flows.

## The Diagrams

### 1. ATM System (Sequence Diagram)

- **Type:** Sequence Diagram
- **Focus:** Maps the exact chronological messages passed between the Customer, the ATM hardware, and the Bank Server.
- **Logic Highlight:** Uses `alt` (alternative) logic fragments to demonstrate how the system handles points of failure (invalid PINs, insufficient funds) in real-time.

### 2. Medical Clinic System (State Diagram)

- **Type:** State Diagram
- **Focus:** Tracks the complete lifecycle of a single `Appointment` object from creation to destruction.
- **Logic Highlight:** Features composite states (sub-states for Examination, Diagnosis, and Treatment) and handles alternative pathways like patient no-shows or rescheduling.

### 3. Car Insurance System (Activity Diagram)

- **Type:** Activity Diagram
- **Focus:** Maps the step-by-step business process of filing and processing an insurance claim.
- **Logic Highlight:** Utilizes `fork` and `join` nodes to demonstrate parallel processing (e.g., assessing vehicle damage at the exact same time as reviewing the police report).

### 4. ESP32 Climate Station (Sequence, State, & Activity)

_These diagrams provide the dynamic behavioral modeling for the main project's Software Requirements Specification (SRS)._

- **Telegram Bot API (Sequence):** Details the chronological polling loop the ESP32 uses to fetch remote commands and transmit data back to the user.
- **Firmware Lifecycle (State):** Models the boot sequence, handling of Wi-Fi network drops, and transitions into OTA update modes.
- **SPIFFS Data Logging (Activity):** Maps the internal logic of the rolling 24-hour memory buffer, specifically how the system deletes old records to prevent flash memory overflow.
