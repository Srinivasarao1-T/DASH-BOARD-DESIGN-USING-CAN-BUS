# 🚗 Dashboard Design Using CAN Bus (LPC2129 + MCP2551)

A real-time digital dashboard project using the **LPC2129 ARM7 microcontroller** and **MCP2551 CAN transceiver** to read and display vehicle parameters like RTC, Indicator, temperature, and fuel level over a CAN bus network.

---

## 🧩 Features

- CAN bus communication using LPC2129's internal CAN controller
- Interface with MCP2551 for physical CAN signaling
- Real-time data display on LCD
- Supports standard 11-bit CAN messages
- Scalable to support additional vehicle data
- Efficient interrupt-driven CAN message handling

---

## 🔧 Hardware Overview

| Component      | Description                                  |
|---------------|----------------------------------------------|
| **LPC2129**    | ARM7TDMI-S MCU with built-in CAN controller |
| **MCP2551**    | CAN transceiver (handles differential CAN signaling) |
| **Display**    | LCD HDD44780
| **Power**      | 3.3V/5V regulated supply                     |
| **Termination**| 120Ω resistors at both ends of CAN network   |

--- 

# 🧠 Software Architecture

- Written in C (Keil  µVision/ Embedded C / Flash Magic)
- Initializes CAN controller on LPC2129
- Configures acceptance filters for desired CAN IDs
- Uses interrupts to handle incoming messages
- Extracts payload and updates display in real time

---

Key Components:
Main Node: Reads DS18B20 temperature sensor, shows RTC and fuel level on LCD, handles indicator signals.

Fuel Node: 
Reads fuel via ADC and sends data to Main Node.

Indicator Node:
Receives indicator status from Main Node and toggles LEDs. 

MAIN NODE:
Read the temperature information and display it on LCD along with RTC information (TIME, DATE & DAY). And based on the interrupt generated, need to send the indicator signal to the indicator node and display the indicators status also on LCD. And one more task of this main node is receiving the fuel node information and display it on LCD. 

INDICATOR NODE:
Continuously waiting for the data from the main NODE using CAN.  If any data is received from main NODE, based on that it is controlling the indicator signals connected to microcontroller. Refer the block diagram for how to give the indicator signals with the help of LED’S

FUEL NODE: 
Continuously reading the Fuel gauge sensor information with the help of on chip ADC and send that information to the main node.
