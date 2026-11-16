# Smart Door Lock Access Control System

## Project Overview

This project implements a **Smart Door Lock Access Control System** using **ESP32, RFID technology, and Arduino IDE**.

The system uses two RFID card readers to manage door entry and exit. Only authorized RFID cards are allowed to access the door. When a valid card is scanned, the solenoid lock is activated, and the access information is displayed on an LCD screen.

The system also connects to Wi-Fi and stores entry and exit records in **Google Sheets** for monitoring and attendance tracking.

This project is ideal for **home automation, office security, access control, and educational purposes**.

> **Note:** This project includes component images and circuit diagrams. Please follow the `Project_Presentation.pdf` for detailed project documentation.  
> All media files are organized inside the `images/` and `videos/` folders.  
> **To watch the project video, download it first because GitHub does not directly play video files in the repository.**

## Features

- Dual RFID card-based authentication (Entry & Exit)
- Authorized RFID card verification
- ESP32-based access control system
- Solenoid/electric door lock control using a relay module
- 16×2 I2C LCD display for access status
- Buzzer notification for valid and invalid card scans
- Wi-Fi connectivity
- Automatic entry and exit logging to Google Sheets
- User information management (Name, ID, and Batch)
- Modular and expandable design

## Hardware Requirements

The following components are used in this project:

- ESP32 Development Board
- 2 × MFRC522 RFID Reader Modules
- 16×2 LCD Display with I2C Module
- Relay Module
- Solenoid Door Lock
- Buzzer
- DC-DC Buck Converter
- Battery / Power Supply
- RFID Cards / Tags
- Jumper Wires

## Circuit Diagram

The circuit diagram illustrates the connections between the ESP32, two RFID readers, LCD display, relay module, buzzer, and power supply.

See the `images/` folder for the complete circuit diagram.

## Pin Configuration (ESP32)

The following GPIO pin configuration is used in this project.

### 1. RFID Reader 1 – Entry (MFRC522)

| RFID Pin | ESP32 GPIO |
|---|---|
| SDA / SS | GPIO 4 |
| SCK | GPIO 18 |
| MOSI | GPIO 23 |
| MISO | GPIO 19 |
| RST | GPIO 16 |
| IRQ | Not Connected |
| 3.3V | 3.3V |
| GND | GND |

### 2. RFID Reader 2 – Exit (MFRC522)

| RFID Pin | ESP32 GPIO |
|---|---|
| SDA / SS | GPIO 2 |
| SCK | GPIO 18 |
| MOSI | GPIO 23 |
| MISO | GPIO 19 |
| RST | GPIO 15 |
| IRQ | Not Connected |
| 3.3V | 3.3V |
| GND | GND |

**Note:** Both RFID readers share the same SPI communication pins (SCK, MOSI, and MISO). However, each reader uses separate SDA/SS and RST pins.

### 3. LCD Display (16×2 I2C)

| LCD Pin | ESP32 GPIO |
|---|---|
| SDA | GPIO 21 |
| SCL | GPIO 22 |
| VCC | 5V (VIN) |
| GND | GND |

- I2C Address: `0x27`

### 4. Relay Module and Solenoid Lock

| Component Pin | ESP32 GPIO |
|---|---|
| Relay IN | GPIO 25 |
| Relay VCC | 5V |
| Relay GND | GND |

The relay module controls the solenoid door lock.

### 5. Buzzer

| Buzzer Pin | ESP32 GPIO |
|---|---|
| Positive (+) | GPIO 26 |
| Negative (-) | GND |

### 6. SPI Communication Pins

Both RFID readers use the following shared SPI pins:

| SPI Signal | ESP32 GPIO |
|---|---|
| SCK | GPIO 18 |
| MISO | GPIO 19 |
| MOSI | GPIO 23 |

## Software Requirements

To work with this project, you need:

- **Arduino IDE** – To edit and upload code to the ESP32 board.
  - Download: https://www.arduino.cc/en/software
- **MFRC522 Library** – For RFID communication.
- **LiquidCrystal_I2C Library** – For LCD display control.
- **ESP32 Board Package** – For ESP32 development.
- **Google Apps Script** – For sending access records to Google Sheets.

## Project Folder Structure

```text
Smart-Door-Lock-Access-Control-System/
│
├── images/
│   ├── components/
│   ├── circuit-diagram.png
│   └── project-images/
│
├── videos/
│   └── project-demo.mp4
│
├── Project_Presentation.pdf
├── Smart_Door_Lock.ino
└── README.md
```

## Author

**Md. Jakirul Islam**

University Project – DSD Course

## License

This project is open for educational purposes.
