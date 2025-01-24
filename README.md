Smart Door Lock System

![1](https://github.com/user-attachments/assets/6c43274e-280b-47af-ab5a-d89b171d040a)


📌 Project Overview
This project implements a Smart Door Lock System using an ESP32 microcontroller. The system enhances home security by integrating multiple components for secure and efficient operation:

4x4 Keypad for PIN-based door unlocking.
16x2 LCD Display for system status feedback.
PIR Motion Sensor for detecting motion near the door.
ESP32 Microcontroller for processing and control.
This system provides robust security features with potential for IoT integration in the future.

🔧 Features
Secure PIN-based access control.
Real-time motion detection to activate the system.
LCD feedback to guide users (e.g., "Enter PIN", "Access Granted", "Access Denied").
Automatic lock reset after incorrect attempts.
Modular design for easy upgrades (e.g., IoT control, smartphone integration).
🛠️ Hardware Components
ESP32 Microcontroller: Main processing unit.
4x4 Keypad: For entering the PIN.
16x2 LCD Display: Displays system messages.
PIR Motion Sensor: Detects motion and activates the system.
Relay Module: Controls the door lock mechanism.
Power Supply: Powers the ESP32 and components.
Additional Components: Jumper wires, resistors, breadboard or PCB.
📜 Software Requirements
Arduino IDE or PlatformIO for programming the ESP32.
Required Libraries:
Keypad.h: To handle keypad input.
LiquidCrystal_I2C.h: For the LCD display interface.
🖥️ How It Works
The system remains in standby mode until the PIR motion sensor detects motion.
Upon detection, the LCD prompts the user to enter a 4-digit PIN.
User Input:
If the entered PIN is correct, the system activates the relay, unlocking the door.
If the PIN is incorrect, it displays "Access Denied" and resets after a few failed attempts.
The system locks the door automatically after a timeout.
⚙️ Setup and Installation
1. Hardware Assembly
Connect the keypad to ESP32 GPIO pins.
Interface the LCD display with the ESP32 using I2C.
Connect the PIR sensor and relay module to appropriate GPIO pins.
Assemble all components on a breadboard or PCB.
2. Software Setup
Install the required libraries in the Arduino IDE.
Upload the provided code to the ESP32.
Test the system with a pre-set PIN.
3. Customization
Modify the PIN in the code (PIN variable).
Adjust the PIR sensor's sensitivity if needed.
🚀 Future Enhancements
IoT integration for remote door monitoring and control.
Smartphone app for managing the system and PINs.
Biometric authentication (e.g., fingerprint scanner).
Integration with smart home ecosystems like Alexa or Google Home.
