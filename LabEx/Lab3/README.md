# Lab 3: UML Class Diagrams

## Overview

This folder contains the UML Class diagrams generated for Lab 3.

While Use Case diagrams (Lab 2) show _who_ uses the system, Class diagrams show _how_ the system is actually built under the hood. They map out the object-oriented architecture, detailing the exact classes, their attributes (variables), their operations (functions), and how they relate to one another through inheritance, composition, and aggregation.

## The Diagrams

### 1. ATM System

Models the backend architecture of a cash machine.

- **Key Architecture:** Uses an abstract `Transaction` class that branches into specific `Withdrawal` and `Deposit` classes. Demonstrates how the ATM hardware (Card Reader, Cash Dispenser) is composed into the main system.

### 2. Car Insurance System

Maps the business logic and database relations of an insurance provider.

- **Key Architecture:** Uses a central abstract `User` class to share common data (names, contact info) between `Customer` and `Agent` classes. Highlights composition (a `Claim` cannot exist without an `InsurancePolicy`).

### 3. Medical Clinic System

Details the data structures required to run a healthcare facility.

- **Key Architecture:** Shows the aggregation between a `Doctor` and the `Clinic` (a doctor can exist without the clinic), and the strict composition of `ConsultationEntry` logs residing inside a `MedicalRecord`.

### 4. ESP32 Climate Station

_This is the core architecture for the main project documented in the SRS._
It maps the C++ firmware structure running on the microcontroller.

- **Key Architecture:** Uses an abstract `HardwareDevice` class to standardize I2C peripherals. It strictly separates volatile network logic (`TelegramBot`) from non-volatile memory management (`DataLog`).
