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
float vA, vB, vC, vD = {0.00};
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
  
  // Display Adafruit logo
  display.display();
  delay(1500);
  
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
  display.clearDisplay(); // Clear display
}

//Funciones
float get_max_val(float PORT) {
    float max_val = 0;
    for (int i = 0; i < 100; i++) {
        float val = analogRead(PORT);
        if (val > max_val) {
            max_val = val;
        }
        delayMicroseconds(150); // Possible issue here
    }
    max_val =  ((((max_val * 5.0) / 1023.0) * 9.6) - 24);
    return max_val;
}

// Functions LEDs for precaution
void LED_Alarm(float vA, float vB, float vC, float vD, float MODE){
    if (MODE == THRESHOLD_AC) {
      if(vA > THRESHOLD_AC){
        digitalWrite(LED_A, HIGH);
      } else{
        digitalWrite(LED_A, LOW); 
      }

      if(vB > THRESHOLD_AC){
        digitalWrite(LED_B, HIGH);
      } else{
        digitalWrite(LED_B, LOW); 
      }

      if(vC > THRESHOLD_AC){
        digitalWrite(LED_C, HIGH);
      } else{
        digitalWrite(LED_C, LOW); 
      }

      if(vD > THRESHOLD_AC){
        digitalWrite(LED_D, HIGH);
      } else{
        digitalWrite(LED_D, LOW); 
      }
    } else{  // MODE THRESHOLD_DC
      if(vA > THRESHOLD_DC || vA < -THRESHOLD_DC){
        digitalWrite(LED_A, HIGH);
      } else{
        digitalWrite(LED_A, LOW); 
      }

      if(vB > THRESHOLD_DC || vB < -THRESHOLD_DC){
        digitalWrite(LED_B, HIGH);
      } else{
        digitalWrite(LED_B, LOW); 
      }

      if(vC > THRESHOLD_DC || vC < -THRESHOLD_DC){
        digitalWrite(LED_C, HIGH);
      } else{
        digitalWrite(LED_C, LOW); 
      }

      if(vD > THRESHOLD_DC || vD < -THRESHOLD_DC){
        digitalWrite(LED_D, HIGH);
      } else{
        digitalWrite(LED_D, LOW); 
      }
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
    vAC_A = vAC_A/sqrt(2); // RMS value 

    float vAC_B = get_max_val(A4);
    vAC_B = vAC_B/sqrt(2); // RMS value

    float vAC_C = get_max_val(A3);
    vAC_C = vAC_C/sqrt(2); // RMS value

    float vAC_D = get_max_val(A2);
    vAC_D = vAC_D/sqrt(2); // RMS value

    if(transmission){
      Serial.println("------------ AC/DC:  AC ------------");
      Serial.println("CHANNEL A:");
      Serial.println(vAC_A);
      Serial.println("CHANNEL B:");
      Serial.println(vAC_B);
      Serial.println("CHANNEL C:");
      Serial.println(vAC_C);
      Serial.println("CHANNEL D:");
      Serial.println(vAC_D);
    }

    // Message in the display:
    display.print("Voltímetro AC \n");
    display.print("vA:");display.print(vAC_A);
    display.print("\n");
    display.print("vB:"); display.print(vAC_B);
    display.print("\n");
    display.print("vC:"); display.print(vAC_C);
    display.print("\n");
    display.print("vD:"); display.print(vAC_D);
    display.print("\n");
    display.display();
    display.clearDisplay();

    //Call the function Led Alarm for AC
    LED_Alarm(vAC_A, vAC_B, vAC_C, vAC_D, THRESHOLD_AC);

  } else{  // DC CASE

    vDC_A = (((analogRead(A5) * 5.0) / 1023.0) * 9.6) - 24;
    vDC_B = (((analogRead(A4) * 5.0) / 1023.0) * 9.6) - 24;
    vDC_C = (((analogRead(A3) * 5.0) / 1023.0) * 9.6) - 24;
    vDC_D = (((analogRead(A2) * 5.0) / 1023.0) * 9.6) - 24;

    if(transmission){
      Serial.println("------------ AC/DC:  DC ------------");
      Serial.println("CHANNEL A:");
      Serial.println(vDC_A);
      Serial.println("CHANNEL B:");
      Serial.println(vDC_B);
      Serial.println("CHANNEL C:");
      Serial.println(vDC_C);
      Serial.println("CHANNEL D:");
      Serial.println(vDC_D);
    }

    // Message in the display:
    display.print("Voltímetro DC \n");
    display.print("vA:"); display.print(vDC_A); display.print("V");
    display.print("\n");
    display.print("vB:"); display.print(vDC_B); display.print("V");
    display.print("\n");
    display.print("vC:"); display.print(vDC_C); display.print("V");
    display.print("\n");
    display.print("vD:"); display.print(vDC_D); display.print("V");
    display.print("\n");
    display.display();
    display.clearDisplay();

    //Call the function Led Alarm for DC
    LED_Alarm(vDC_A, vDC_B, vDC_C, vDC_D, THRESHOLD_DC);
  }
  
  // Delay before restarting loop
  delay(100);
}
