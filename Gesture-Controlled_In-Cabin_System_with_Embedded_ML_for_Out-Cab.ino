
#include <Arduino_APDS9960.h> 
void setup() {
  Serial.begin(9600);
  //in-built LED
  pinMode(LED_BUILTIN, OUTPUT);
  //Red
  pinMode(LEDR, OUTPUT);
  //Green
  pinMode(LEDG, OUTPUT);
  //Blue
  pinMode(LEDB, OUTPUT);
  
  while (!Serial);
  if (!APDS.begin()) {
    Serial.println("Error initializing APDS9960 sensor!");
  }
  // for setGestureSensitivity(..) a value between 1 and 100 is required.
  // Higher values makes the gesture recognition more sensible but less accurate
  // (a wrong gesture may be detected). Lower values makes the gesture recognition
  // more accurate but less sensible (some gestures may be missed).
  // Default is 80
  //APDS.setGestureSensitivity(80);
  Serial.println("Detecting gestures ...");
  // Turining OFF the RGB LEDs
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, HIGH);
}

void loop() {
  if (APDS.gestureAvailable()) {
    // a gesture was detected, read and print to serial monitor
    int gesture = APDS.readGesture();
    switch (gesture) {
      case GESTURE_UP:
        Serial.println("Detected UP gesture");
        digitalWrite(LEDR, LOW);
        delay(1000);
        digitalWrite(LEDR, HIGH);
        break;
      case GESTURE_DOWN:
        Serial.println("Detected DOWN gesture");
        digitalWrite(LEDG, LOW);
        delay(1000);
        digitalWrite(LEDG, HIGH);
        break;
      case GESTURE_LEFT:
        Serial.println("Detected LEFT gesture");
        digitalWrite(LEDB, LOW);
        delay(1000);
        digitalWrite(LEDB, HIGH);
        break;
      case GESTURE_RIGHT:
        Serial.println("Detected RIGHT gesture");
        digitalWrite(LED_BUILTIN, HIGH);
        delay(1000);
        digitalWrite(LED_BUILTIN, LOW);
        break;
      default:
        break;
    }
  }
}

Shreya BVB, [16-01-2024 11:27 PM]
#include <Wire.h>
#include <Arduino_APDS9960.h>
#include <Arduino_HTS221.h>
#include <Servo.h>
#include <PDM.h>

#define BUZZER_PIN 8
#define motorA1 6  // Connect to IN1 on L298N
#define motorA2 7  // Connect to IN2 on L298N
#define motorEnableA 5  // Connect to ENA on L298N

Servo myservo;
int currentAngle = 0;
short sampleBuffer[256];
volatile int samplesRead;

void onPDMdata(); // Declare onPDMdata function
void readAndPrintTemperature();
void beep(int frequency, int duration);

void setup() {
  Serial.begin(9600);
  while (!Serial);
  PDM.onReceive(onPDMdata);
  if (!PDM.begin(1, 16000)) {
    Serial.println("Failed to start PDM!");
    if (!PDM.begin(1, 16000)) {
      Serial.println("Failed to start PDM!");
    }
  }
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorEnableA, OUTPUT);
  myservo.attach(9);
  analogWrite(motorEnableA, 0);
  if (!APDS.begin()) {
    Serial.println("Error initializing APDS9960 sensor!");
  }
  if (!HTS.begin()) {
    Serial.println("Error initializing HTS221 sensor!");
  }
  Serial.println("Detecting gestures and reading temperature...");
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDB, HIGH);
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  // Gesture Detection
  if (APDS.gestureAvailable()) {
    int gesture = APDS.readGesture();
    switch (gesture) {
      case GESTURE_UP:
        Serial.println("Detected UP gesture");
        digitalWrite(LEDR, LOW);
        delay(1000);
        digitalWrite(LEDR, HIGH);
        if (currentAngle != 180) {
          myservo.write(180);
          currentAngle = 180;
          Serial.println("Sunroof Open");
          delay(1000);
        } else if (currentAngle != 0) {
          myservo.write(0);
          currentAngle = 0;
          Serial.println("Sunroof Close");
          delay(500);
        }
        break;

      case GESTURE_DOWN:
        Serial.println("Detected DOWN gesture");
        digitalWrite(LEDG, LOW);
        delay(1000);
        digitalWrite(LEDG, HIGH);
        digitalWrite(motorA1, HIGH);
        digitalWrite(motorA2, LOW);
        Serial.println("AC ON");
        analogWrite(motorEnableA, 128);  // 128 is approximately half of the maximum PWM value (255)
        delay(2000);

        // Stop the motor for 1 second
        digitalWrite(motorA1, LOW);
        digitalWrite(motorA2, LOW);
        Serial.println("AC OFF");
        // Stop the motor by setting speed to 0
        analogWrite(motorEnableA, 0);
        delay(2000);
        readAndPrintTemperature();
        break;

      case GESTURE_LEFT:
        Serial.println("Detected LEFT gesture");
        digitalWrite(LEDB, LOW);
        delay(1000);
        digitalWrite(LEDB, HIGH);
        delay(1000);
        beep(5000, 2000);
        delay(1000);
        beep(2000, 300);
        delay(1000);
        break;

      case GESTURE_RIGHT:
        Serial.println("Detected RIGHT gesture");
        digitalWrite(LEDB, LOW);
        delay(1000);
        digitalWrite(LEDB, HIGH);
        if (samplesRead) {
          for (int i = 0; i < samplesRead; i++) {
            if (sampleBuffer[i] >= 500) {
              Serial.println("RIGHT INDICATOR ON");
              digitalWrite(LEDR, LOW);
            }
            if (sampleBuffer[i] >= 250 && sampleBuffer[i] < 500) {
              Serial.println("LEFT INDICATOR ON");
              digitalWrite(LEDB, LOW);
            }
            if (sampleBuffer[i] >= 0 && sampleBuffer[i] < 250) {
              Serial.println("HEADLIGHTS ON");
              digitalWrite(LEDG, LOW);
            }
          }
        }
        break;
    }
  }
  //delay(1000);  // Adjust delay as needed
}


void readAndPrintTemperature() {
  // Temperature Reading
  float temperature = HTS.readTemperature();
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
}

void onPDMdata() {
  // query the number of bytes available
  int bytesAvailable = PDM.available();

  // read into the sample buffer
  PDM.read(sampleBuffer, bytesAvailable);

  // 16-bit, 2 bytes per sample
  samplesRead = bytesAvailable / 2;
}

void beep(int frequency, int duration) {
  tone(BUZZER_PIN, frequency, duration);
  delay(duration + 50);  // Add a small delay to avoid overlapping tones
  noTone(BUZZER_PIN);
}
