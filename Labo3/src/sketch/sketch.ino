#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Define pins for LEDs and buttons
#define LED_A 8
#define LED_B 9
#define LED_C 10
#define LED_D 11
#define BUTTON_ACDC 6

// Define threshold voltages for LEDs
#define THRESHOLD_A 10
#define THRESHOLD_B 20
#define THRESHOLD_C 30
#define THRESHOLD_D 40

// Define display pins
#define SCLK 7
#define DIN 6
#define DC 5
#define CS 4
#define RST 3

Adafruit_PCD8544 display = Adafruit_PCD8544(SCLK, DIN, DC, CS, RST);

//Variables globales
float vA, vB, vC, vD = {0.00};

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Set LED pins as output
  pinMode(LED_A, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(LED_C, OUTPUT);
  pinMode(LED_D, OUTPUT);
  
  // Initialize display
  display.begin();
  display.setContrast(50);
  display.clearDisplay();
  
  // Display Adafruit logo
  display.drawBitmap(30, 0, Adafruit_Logo_bits, 64, 48, BLACK);
  display.display();
  delay(2000);
  
  // Display title and start message
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(5,0);
  display.println("VOLTIMETRO AC");
  display.setCursor(5,10);
  display.println("|INICIO|");
  display.display();
  delay(2000);
  display.clearDisplay();
}

//Funciones
float get_max_vA() {
    float max_val = 0;
    for (int i = 0; i < 100; i++) {
        float val = analogRead(A5) * (5.0 / 1023.0);
        if (val > max_val) {
            max_val = val;
        }
        delayMicroseconds(10); // Possible issue here
    }
    return max_val;
}

float get_max_vB() {
  float max_val = 0;
  for (int i = 0; i < 100; i++) {
        float val = analogRead(A4) * (5.0 / 1023.0);
        if (val > max_val) {
            max_val = val;
        }
        delayMicroseconds(10);
    }
    return max_val;
}

float get_max_vC() {
  float max_val = 0;
  for (int i = 0; i < 100; i++) {
        float val = analogRead(A3) * (5.0 / 1023.0);
        if (val > max_val) {
            max_val = val;
        }
        delayMicroseconds(10);
    }
    return max_val;
}

float get_max_vD() {
  float max_val = 0;
  for (int i = 0; i < 100; i++) {
        float val = analogRead(A2) * (5.0 / 1023.0);
        if (val > max_val) {
            max_val = val;
        }
        delayMicroseconds(10);
    }
    return max_val;
}

//main loop
void loop() {
  // Check if AC/DC button is pressed
  int mode = digitalRead(BUTTON_ACDC);
  
  switch(mode) {
    case HIGH:
      // AC mode
      vA = get_max_vA();
      vB = get_max_vB();
      vC = get_max_vC();
      vD = get_max_vD();
      if (vA > THRESHOLD_A) {
        digitalWrite(LED_A, HIGH);
      } else {
        digitalWrite(LED_A, LOW);
      }
      if (vB > THRESHOLD_B) {
        digitalWrite(LED_B, HIGH);
      } else {
        digitalWrite(LED_B, LOW);
      }
      if (vC > THRESHOLD_C) {
        digitalWrite(LED_C, HIGH);
      } else {
        digitalWrite(LED_C, LOW);
      }
      if (vD > THRESHOLD_D) {
        digitalWrite(LED_D, HIGH);
      } else {
        digitalWrite(LED_D, LOW);
      }
      break;
    case LOW:
      // DC mode
      // Code to be implemented
      break;
  }
  
  // Delay before restarting loop
  delay(100);
}
