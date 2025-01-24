# Smart Door Lock System

![1](https://github.com/user-attachments/assets/fd3b26b9-5d78-48f8-937e-7de3fa7696b6)


## 📌 Project Overview
This project implements a **Smart Door Lock System** using an **ESP32 microcontroller**. The system enhances home security by integrating multiple components for secure and efficient operation:
- **4x4 Keypad** for PIN-based door unlocking.
- **16x2 LCD Display** for system status feedback.
- **PIR Motion Sensor** for detecting motion near the door.
- **ESP32 Microcontroller** for processing and control.

This system provides robust security features with potential for IoT integration in the future.

---

## 🔧 Features
- **Secure Access**: PIN-based authentication for door unlocking.
- **Real-time Feedback**: Displays status on the LCD screen.
- **Motion Detection**: Activates the system when motion is detected by the PIR sensor.
- **Fail-Safe Mechanism**: Locks the door automatically after incorrect PIN attempts.

---

## 🛠️ Hardware Components
1. **ESP32 Microcontroller**: The brain of the system.
2. **4x4 Keypad**: For entering the PIN.
3. **16x2 LCD Display**: Displays system messages like "Enter PIN" or "Access Denied."
4. **PIR Motion Sensor**: Detects motion and activates the system.
5. **Relay Module**: Controls the door lock mechanism.
6. **Power Supply**: Powers the ESP32 and connected components.
7. **Additional Components**: Jumper wires, resistors, breadboard, or PCB.

---

## 📜 Software Requirements
- **Arduino IDE** or **PlatformIO** for programming the ESP32.
- Required Libraries:
  - `Keypad.h` for keypad input handling.
  - `LiquidCrystal_I2C.h` for the LCD display interface.

---

## 🖥️ How It Works
1. The system remains in **standby mode** until the PIR motion sensor detects motion.
2. Upon detection, the LCD prompts the user to **enter a 4-digit PIN**.
3. **User Input**:
   - If the PIN is correct, the relay activates, unlocking the door.
   - If the PIN is incorrect, the system displays "Access Denied" and locks after multiple failed attempts.
4. The system resets after a timeout period, locking the door and returning to standby mode.

---

## ⚙️ Setup and Installation
### 1. Hardware Assembly
- Connect the **keypad** to ESP32 GPIO pins.
- Interface the **LCD display** with the ESP32 using I2C.
- Connect the **PIR sensor** and **relay module** to appropriate GPIO pins.
- Assemble all components on a breadboard or PCB.

### 2. Software Setup
- Install the required libraries in the Arduino IDE.
- Upload the provided code to the ESP32.
- Test the system with a pre-set PIN.

### 3. Customization
- Modify the `PIN` variable in the code to set a custom PIN.
- Adjust the PIR sensor's sensitivity if needed.

---

## 🚀 Future Enhancements
- IoT integration for remote monitoring and control.
- Smartphone app for managing the system and PINs.
- Biometric authentication (e.g., fingerprint scanner).
- Integration with smart home systems like Alexa or Google Home.

---




