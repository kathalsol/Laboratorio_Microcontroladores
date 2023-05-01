#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// Define pins for LEDs and buttons
#define LED_A 8
#define LED_B 9
#define LED_C 10
#define LED_D 11
//#define BUTTON_ACDC A1
//#define BUTTON_SERIAL A0

// Define threshold voltages for LEDs
#define THRESHOLD_DC 20
#define THRESHOLD_AC 14.14 // Valor RMS maximo 20/sqrt(20)

// Define display pins
#define SCLK 7
#define DIN 6
#define DC 5
#define CS 4
#define RST 3

Adafruit_PCD8544 display = Adafruit_PCD8544(SCLK, DIN, DC, CS, RST);

//Variables globales
float vDC_A, vDC_B, vDC_C, vDC_D = {0.00};

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
  display.display();
  delay(1000);
  
  // Display title and start message
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(5,0);
  display.println("AC/DC Meter");
  display.setCursor(5,10);
  display.println("INICIO!!!");
  display.display();
  delay(2000);
  display.clearDisplay();
}

//Funciones
float get_max_val(float PORT) {
    float max_val = 0;
    for (int i = 0; i < 100; i++) {
        float val = (analogRead(PORT) * (((5.0 / 1023.0) * 9.6) - 24));
        if (val > max_val) {
            max_val = val;
        }
        delayMicroseconds(150); // Possible issue here
    }
    return max_val;
}

// Functions LEDs for precaution
void LED_Alarm(float vA, float vB, float vC, float vD, float MODE){
    if(vA > MODE){
      digitalWrite(LED_A, HIGH);
    } else{
      digitalWrite(LED_A, LOW); 
    }

    if(vB > MODE){
      digitalWrite(LED_B, HIGH);
    } else{
      digitalWrite(LED_B, LOW); 
    }

    if(vC > MODE){
      digitalWrite(LED_C, HIGH);
    } else{
      digitalWrite(LED_C, LOW); 
    }

    if(vD > MODE){
      digitalWrite(LED_D, HIGH);
    } else{
      digitalWrite(LED_D, LOW); 
    }
}

//main loop
void loop() {
  // Check if AC/DC button is pressed
  float mode = analogRead(A1);

  // Check if the Serial transmission button is pressed
  float transmission = analogRead(A0);

  if (mode){ // AC/DC button pressed => AC MODE

    float vAC_A = get_max_val(A5);
    vAC_A = vAC_A/sqrt(2); // RMS value for AC 

    float vAC_B = get_max_val(A4);
    vAC_B = vAC_B/sqrt(2); // RMS value for AC

    float vAC_C = get_max_val(A3);
    vAC_C = vAC_C/sqrt(2); // RMS value for AC

    float vAC_D = get_max_val(A2);
    vAC_D = vAC_D/sqrt(2); // RMS value for AC

    if(transmission){
      Serial.println("CHANNEL A:");
      Serial.println(vAC_A);
      Serial.println("CHANNEL B:");
      Serial.println(vAC_B);
      Serial.println("CHANNEL C:");
      Serial.println(vAC_C);
      Serial.println("CHANNEL D:");
      Serial.println(vAC_D);
      Serial.println("AC/DC:  AC");
    }

    // Message in the display:
    display.print("Voltímetro AC \n");
    display.print("vA:" + String(vAC_A) + "Vrms");
    display.print("vB:" + String(vAC_B) + "Vrms");
    display.print("vC:" + String(vAC_C) + "Vrms");
    display.print("vD:" + String(vAC_D) + "Vrms");
    display.clearDisplay();

    //Call the function Led Alarm for AC
    LED_Alarm(vAC_A, vAC_B, vAC_C, vAC_D, THRESHOLD_AC);

  } else{  // DC CASE

    vDC_A = analogRead(A5);
    vDC_B = analogRead(A5);
    vDC_C = analogRead(A5);
    vDC_D = analogRead(A5);

    if(transmission){
      Serial.println("CHANNEL A:");
      Serial.println(vDC_A);
      Serial.println("CHANNEL B:");
      Serial.println(vDC_B);
      Serial.println("CHANNEL C:");
      Serial.println(vDC_C);
      Serial.println("CHANNEL D:");
      Serial.println(vDC_D);
      Serial.println("AC/DC:  DC");
    }

    // Message in the display:
    display.print("Voltímetro DC \n");
    display.print("vA:" + String(vDC_A) + "Vrms");
    display.print("vB:" + String(vDC_B) + "Vrms");
    display.print("vC:" + String(vDC_C) + "Vrms");
    display.print("vD:" + String(vDC_D) + "Vrms");
    display.clearDisplay();

    //Call the function Led Alarm for DC
    LED_Alarm(vDC_A, vDC_B, vDC_C, vDC_D, THRESHOLD_DC);
  }
  
  // Delay before restarting loop
  delay(100);
}
