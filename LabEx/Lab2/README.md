# Lab 2: UML Use Case Diagrams

## Overview

This folder contains the UML Use Case diagrams generated for Lab 2.

Use Case diagrams provide a high-level behavioral view of a system. They don't show _how_ the code works behind the scenes; instead, they map out **who** is interacting with the system (Actors) and **what** they are trying to achieve (Use Cases), along with the mandatory (`<<include>>`) and optional (`<<extend>>`) steps along the way.

## The Diagrams

### 1. ATM System

Maps the standard interactions between a **Customer**, the **ATM**, and the central **Bank** server.

- **Core Actions:** Withdrawing cash, depositing funds, transferring money, and paying bills.
- **Logic Highlight:** Demonstrates how every major financial action strictly requires the `Authenticate PIN` use case to proceed.

### 2. Car Insurance System

Visualizes the relationship between a **Customer**, an **Insurance Agent**, and an external **Payment Gateway**.

- **Core Actions:** Purchasing, updating, and canceling policies, as well as filing claims.
- **Logic Highlight:** Shows how purchasing a policy or filing a claim optionally extends into `Request Road Assistance`, while mandatory validation checks happen in the background.

### 3. Medical Clinic System

Outlines the daily operations of a healthcare clinic, involving the **Patient**, **Doctor**, **Receptionist**, and an external **Insurance System**.

- **Core Actions:** Booking appointments, conducting consultations, prescribing medication, and generating bills.
- **Logic Highlight:** Captures the real-world workflow where a Receptionist handles the billing and insurance claims, while the Doctor focuses on consultations and optionally extending them to `Do the Tests`.

### 4. ESP32 Climate Station

_This is the core architecture for the main project documented in the SRS._
It models how human and non-human actors interact with the IoT hardware.

- **Actors:** The **Home User**, an internal **System Timer**, and the external **Telegram API**.
- **Core Actions:** Monitoring the local climate, executing remote commands, accessing the web dashboard, and performing Over-The-Air (OTA) updates.
- **Logic Highlight:** Shows how the autonomous System Timer triggers the hardware to read the sensor data and transmit a message to the Telegram API without user intervention.
