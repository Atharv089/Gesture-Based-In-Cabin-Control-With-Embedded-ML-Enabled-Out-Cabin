# Gesture-Based In-Cabin Control with Embedded ML-Enabled Out-Cabin Monitoring (Mini Project)

## Overview
This project implements a **gesture-based control system** for in-cabin vehicle functions and an **embedded ML-powered airbag monitoring system** for enhanced safety. It leverages **Edge Impulse** for training ML models and an **Arduino Nano 33 BLE Sense** for real-time gesture recognition and motion sensing.

## Features
- **Gesture-Based In-Cabin Control**
  - Control infotainment, sunroof, and temperature settings using hand gestures.
  - Hands-free interaction to reduce driver distractions.
- **Embedded ML-Enabled Airbag Monitoring**
  - Uses motion sensing to detect potential collisions.
  - Enhances airbag deployment efficiency with real-time decision-making.
- **Edge Impulse Integration**
  - Data collection, training, and deployment of ML models.
  - Optimized model tuning using **EON Tuner**.

## Hardware Requirements
- **Arduino Nano 33 BLE Sense**
- **Gesture Sensor (APDS9960)**
- **Accelerometer (LSM9DS1)**
- **Edge Impulse ML Platform**
- **Buzzer and Servo Motors** (for in-cabin control)

## Software Requirements
- **Arduino IDE**
- **Edge Impulse Studio**
- **Python (for dataset processing, if needed)**

## System Architecture
### In-Cabin Gesture Recognition
- Detects hand gestures (`UP, DOWN, LEFT, RIGHT`) for specific controls.
- Processes sensor data using **TinyML**.
- Triggers corresponding actions (e.g., adjusting air conditioning, controlling sunroof).

### Airbag Monitoring System
- Collects real-time acceleration data.
- Uses **neural network classification** to detect crash-like events.
- Sends alerts for airbag deployment.

## Project Implementation
1. **Data Collection**
   - Captured motion data using **Edge Impulse**.
   - Labeled datasets (`left-right`, `idle`, `up-down`, `circular`).
2. **Model Training**
   - Trained a neural network for gesture recognition.
   - Achieved high accuracy using **EON Tuner**.
3. **Deployment**
   - Deployed the trained model on **Arduino Nano 33 BLE Sense**.
   - Integrated with in-cabin controls and airbag monitoring system.

## Basic Setup Instructions

### **1. Install Required Software**
- **Arduino IDE**: Download and install from [Arduino Official Website](https://www.arduino.cc/en/software).
- **Edge Impulse Studio**: Sign up and set up an account at [Edge Impulse](https://www.edgeimpulse.com/).
- **Required Arduino Libraries**: Install the following libraries in the Arduino IDE:
  - `Arduino_LSM9DS1`
  - `Arduino_APDS9960`
  - `Arduino_TensorFlowLite`

### **2. Hardware Setup**
1. **Connect the Arduino Nano 33 BLE Sense** to your computer via a USB cable.
2. **Connect Sensors & Components**:
   - **Gesture Sensor (APDS9960)** → Connect to Arduino using I2C pins.
   - **Accelerometer (LSM9DS1)** → Inbuilt in Arduino Nano 33 BLE Sense.
   - **Buzzer & Servo Motors** → Connect to the appropriate PWM pins on Arduino.

### **3. Load and Upload the Code**
1. Open **Arduino IDE**.
2. Open the file `Gesture-Controlled_In-Cabin_System_with_Embedded_ML_for_Out-Cab.ino`.
3. Select the correct **board**:  
   - Go to **Tools** → **Board** → Select **Arduino Nano 33 BLE Sense**.
4. Select the correct **port**:  
   - Go to **Tools** → **Port** → Select the **COM port** where Arduino is connected.
5. Click on the **Upload** button.

### **4. Deploy the Machine Learning Model**
1. **Collect Data**: Use **Edge Impulse** to record and label gestures (`Up, Down, Left, Right`).
2. **Train the Model**: Use Edge Impulse's **EON Tuner** for optimization.
3. **Deploy to Arduino**:
   - In Edge Impulse, generate the model as an **Arduino Library**.
   - Download and import it into the Arduino IDE.
   - Integrate the model with the provided Arduino code.
   - Upload the modified code to the Arduino board.

### **5. Testing the System**
1. **Run the program** and monitor the **serial output** in Arduino IDE.
2. **Perform gestures** to control:
   - Sunroof
   - Air Conditioning
   - Infotainment
   - Indicators
3. **Test Airbag Monitoring System** by simulating different motions.

### **6. Troubleshooting**
- If gestures don’t work, **recalibrate** the gesture sensor.
- If no serial output appears, **check the COM port and baud rate**.
- If ML model doesn’t work, **retrain with more data** in Edge Impulse.

## Results
- Achieved **100% accuracy** in gesture recognition due to well-trained data.
- Successfully controlled **infotainment, sunroof, and air conditioning**.
- Demonstrated **efficient airbag monitoring** using ML-based motion sensing.

## Future Scope
- Improve gesture recognition precision with additional training data.
- Expand the system to support **voice commands** alongside gestures.
- Integrate **wireless communication** for cloud-based safety alerts.
