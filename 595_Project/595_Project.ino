// Classes
#include "DEV_Config.h"
#include "LCD_Driver.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "fonts.h"
#include "My_Pages.h"

// ********** Design Notes **********
// Changes made to LCD_Touch.cpp         (added methods needed to check for touches)
// Changes made to DEV_Config.h and .cpp (added pins needed for project)
// Cannot draw black background, slows loading time and system shuts down spontaneously

// Variables
long timer = 0;              // Timer to activate Sleep Mode
int sleep = 0;               // Keeps track of sleep mode, 0 = off, 1 = dim, 2 = sleep
char page = '0';             // Tracks which screen you're on
int startAdjusting = 0;      // Sends signal to Thermoelectric Power Switch, 0 = LOW, 1 = HIGH
int charging = 0;            // Tracks charging method, 0 = Battery, 1 = Solar
uint16_t tempSlider = 260;   // Tracks temperature setting, initialized to room temp , 34F to 100F
uint16_t brightSlider = 450; // Tracks brightness of screen, initialized to 100%
float readTemp = 0;          // Reads data from Peltier Plate
uint16_t userTemp = 0;       // Actual temp that user sets via slider
long tempTimer = 0;          // Timer to pulse Peltier Plate
const int TC1_Ain = 0;       // Thermocouple1 Analog In pin
float volts;                 // converts rawValue to volts
int rawValue = 0;            // Reads temp sensor
/*
uint16_t band = 0;           
uint16_t band_high = 0;
uint16_t band_low = 0;
*/

void setup() {
  // Initialize System
  Setup();

  // Introductory Screens
//  Intro();

  // Transfer to Main Menu
  DrawScreen(&page, &startAdjusting, &charging, &tempSlider, &brightSlider);
}

void SleepTimer(int* sleep, long* timer, uint16_t* brightSlider) {
  if(*sleep != 2) { // off or dim
    ++(*timer);
    
    if(*timer > 1000000) { // dim
      if(*brightSlider > 50 && *sleep == 0) {
        PWM_SetValue(50);
      }
      *sleep = 1;
      
      if(*timer > 5000000) { // sleep
        PWM_SetValue(0);
        *sleep = 2;
      }
    }
  }
}

void convertSlider(uint16_t* tempSlider, uint16_t* userTemp) {
  int counter = 1;
  int compare = 11;

  while(counter < 37) {
    if(*tempSlider <= compare) { // If the slider pixel value is less than or equal to the compare pixel value
      *userTemp = (uint16_t)(counter + 1);
      return;
    }
    else {
      if(counter % 3 == 0) { // counter divisible by 3
        compare = compare + 12; // increase search by 12 pixels
      }
      else { // counter not divisible by 3
        compare = compare + 11; // increase search by 11 pixels
      }
    }
    ++counter;
  }
  *userTemp = (uint16_t)(counter + 1);
}

void TempControl(int* startAdjusting, uint16_t* tempSlider, float* readTemp, uint16_t* userTemp, float* volts, int* rawValue /*, uint16_t* band, uint16_t* band_high, uint16_t* band_low */) {
  // TPS_Dout 1 Controls Relay
  // Direction 2 Controls Peltier
  if(Direction == HIGH) { // Cooling
    if(*readTemp >= (*userTemp + 2)) { // Too Hot
      digitalWrite(TPS_Dout, HIGH);
      digitalWrite(Direction, HIGH);
    }
    else if(*readTemp < (*userTemp - 2)) { // Too Cold
      digitalWrite(TPS_Dout, LOW);
    }
  }
  else { // Heating
    if(*readTemp >= (*userTemp + 2)) { // Too Hot
      digitalWrite(TPS_Dout, LOW);
    }
    else if(*readTemp < (*userTemp - 2)) { // Too Cold
       digitalWrite(TPS_Dout, HIGH);
       digitalWrite(Direction, LOW);
    }
  }
}

void loop() {
  // Check to see if user pushes a button on-screen
  Cursor(&timer, &sleep, &page, &startAdjusting, &charging, &tempSlider, &brightSlider, &readTemp, &userTemp);

  // Sets appropriate screen-dimming based on value of timer
  SleepTimer(&sleep, &timer, &brightSlider);

  // Temperature Control Loop
  if(startAdjusting == 1) {
    TempControl(&startAdjusting, &tempSlider, &readTemp, &userTemp, &volts, &rawValue /*, &band, &band_high, &band_low */);
  }

  // Read value from temp sensor
  rawValue = analogRead(TC1_Ain);    
  volts = (float)rawValue * 5 / 1024;
  readTemp = ((volts/0.01)-32)*5/9;
  Serial.print("Temperature = ");  
  Serial.println(readTemp);  
  delay(1000);
}
