#include "My_Pages.h"
#include "LCD_Driver.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"

TP_DEV MyLCD; // LCD_Touch.h
LCD_DIS MyDisplay; // LCD_Driver.h

/*******************************************************************************
  function:
        Draws a home button in the upper left corner of the screen
*******************************************************************************/
void DrawHomeButton() {
	LCD_SetArealColor(0, 0, 480, 320, WHITE);
	GUI_DrawRectangle(20, 20, 60, 60, RED, DRAW_FULL, DOT_PIXEL_DFT);
	GUI_DisString_EN(25, 35, "Home", &Font12, RED, WHITE);
}

/*******************************************************************************
  function:
        Calls all initial setup functions
*******************************************************************************/
void Setup() {
	// Initialize System
  System_Init();
  LCD_SCAN_DIR Lcd_ScanDir = SCAN_DIR_DFT;
  LCD_Init(Lcd_ScanDir, 200);
  TP_Init(Lcd_ScanDir);
  TP_GetAdFac();
  LCD_Clear(LCD_BACKGROUND);
}

/*******************************************************************************
  function:
        Displays introductory screens
*******************************************************************************/
void Intro() {
  // Opening Screen
  GUI_DisString_EN(20, 40, "An EE595 Project By:", &Font20, LCD_BACKGROUND, BLUE);
  GUI_DisString_EN(20, 60, "Matt Klabunde (CE)", &Font16, LCD_BACKGROUND, BLUE);
  GUI_DisString_EN(20, 80, "Michael Maher (EE)", &Font16, LCD_BACKGROUND, BLUE);
  GUI_DisString_EN(20, 100, "Derrick Markowski (EE)", &Font16, LCD_BACKGROUND, BLUE);
  GUI_DisString_EN(20, 140, "Embedded Hardware Used:", &Font20, LCD_BACKGROUND, BLUE);
  GUI_DisString_EN(20, 160, "ATmega328/P Microcontroller (Atmel)", &Font16, LCD_BACKGROUND, BLUE);
  GUI_DisString_EN(20, 180, "4inch TFT Touch Shield (Waveshare)", &Font16, LCD_BACKGROUND, BLUE);
  GUI_DisString_EN(20, 220, "Software Libraries Provided By:", &Font20, LCD_BACKGROUND, BLUE);
  GUI_DisString_EN(20, 240, "Waveshare", &Font16, LCD_BACKGROUND, BLUE);
  delay(3000);
  LCD_Clear(LCD_BACKGROUND);
  
  // Title Screen
  GUI_DisString_EN(140, 160, "SuperTherm", &Font24, LCD_BACKGROUND, BLUE);
  delay(3000);
  LCD_Clear(LCD_BACKGROUND);
}

/*******************************************************************************
  function:
        Draws a green selection box around the selected box on page 2
  parameter:
        int* charging : sets charging method, 0 = Battery, 1 = Solar
*******************************************************************************/
void DrawSelectionBoxCharging(int* charging) {
  if(*charging == 0) { // Battery
    GUI_DrawRectangle(20, 180, 230, 300, GREEN, DRAW_EMPTY, DOT_PIXEL_DFT);  
    GUI_DrawRectangle(21, 181, 229, 299, GREEN, DRAW_EMPTY, DOT_PIXEL_DFT);
    GUI_DrawRectangle(22, 182, 228, 298, GREEN, DRAW_EMPTY, DOT_PIXEL_DFT);
    GUI_DrawRectangle(23, 183, 227, 297, GREEN, DRAW_EMPTY, DOT_PIXEL_DFT);
    GUI_DrawRectangle(250, 180, 460, 300, RED, DRAW_EMPTY, DOT_PIXEL_DFT);
    GUI_DrawRectangle(251, 181, 459, 299, RED, DRAW_EMPTY, DOT_PIXEL_DFT);
    GUI_DrawRectangle(252, 182, 458, 298, RED, DRAW_EMPTY, DOT_PIXEL_DFT);
    GUI_DrawRectangle(253, 183, 457, 297, RED, DRAW_EMPTY, DOT_PIXEL_DFT);
  }
  else { // Solar
    GUI_DrawRectangle(250, 180, 460, 300, GREEN, DRAW_EMPTY, DOT_PIXEL_DFT);
    GUI_DrawRectangle(251, 181, 459, 299, GREEN, DRAW_EMPTY, DOT_PIXEL_DFT);
    GUI_DrawRectangle(252, 182, 458, 298, GREEN, DRAW_EMPTY, DOT_PIXEL_DFT);
    GUI_DrawRectangle(253, 183, 457, 297, GREEN, DRAW_EMPTY, DOT_PIXEL_DFT);
    GUI_DrawRectangle(20, 180, 230, 300, RED, DRAW_EMPTY, DOT_PIXEL_DFT);  
    GUI_DrawRectangle(21, 181, 229, 299, RED, DRAW_EMPTY, DOT_PIXEL_DFT);
    GUI_DrawRectangle(22, 182, 228, 298, RED, DRAW_EMPTY, DOT_PIXEL_DFT);
    GUI_DrawRectangle(23, 183, 227, 297, RED, DRAW_EMPTY, DOT_PIXEL_DFT);
  }
}

/*******************************************************************************
  function:
        Draws a green selection box around the selected box on page 2
  parameter:
        int* startAdjusting : Sends signal to Thermoelectric Power Switch, 0 = LOW, 1 = HIGH
*******************************************************************************/
void DrawSelectionBoxTemp(int* startAdjusting) {
  if(*startAdjusting == 0) {
    GUI_DrawRectangle(380, 20, 460, 60, GREEN, DRAW_EMPTY, DOT_PIXEL_DFT);  
    GUI_DrawRectangle(381, 21, 459, 59, GREEN, DRAW_EMPTY, DOT_PIXEL_DFT);
    GUI_DrawRectangle(382, 22, 458, 58, GREEN, DRAW_EMPTY, DOT_PIXEL_DFT);
    GUI_DrawRectangle(383, 23, 457, 57, GREEN, DRAW_EMPTY, DOT_PIXEL_DFT);
    GUI_DrawRectangle(280, 20, 360, 60, RED, DRAW_EMPTY, DOT_PIXEL_DFT);
    GUI_DrawRectangle(281, 21, 359, 59, RED, DRAW_EMPTY, DOT_PIXEL_DFT);
    GUI_DrawRectangle(282, 22, 358, 58, RED, DRAW_EMPTY, DOT_PIXEL_DFT);
    GUI_DrawRectangle(283, 23, 357, 57, RED, DRAW_EMPTY, DOT_PIXEL_DFT);
  }
  else { 
    GUI_DrawRectangle(280, 20, 360, 60, GREEN, DRAW_EMPTY, DOT_PIXEL_DFT);
    GUI_DrawRectangle(281, 21, 359, 59, GREEN, DRAW_EMPTY, DOT_PIXEL_DFT);
    GUI_DrawRectangle(282, 22, 358, 58, GREEN, DRAW_EMPTY, DOT_PIXEL_DFT);
    GUI_DrawRectangle(283, 23, 357, 57, GREEN, DRAW_EMPTY, DOT_PIXEL_DFT);
    GUI_DrawRectangle(380, 20, 460, 60, RED, DRAW_EMPTY, DOT_PIXEL_DFT);  
    GUI_DrawRectangle(381, 21, 459, 59, RED, DRAW_EMPTY, DOT_PIXEL_DFT);
    GUI_DrawRectangle(382, 22, 458, 58, RED, DRAW_EMPTY, DOT_PIXEL_DFT);
    GUI_DrawRectangle(383, 23, 457, 57, RED, DRAW_EMPTY, DOT_PIXEL_DFT);
  }
}

/*******************************************************************************
  function:
        Makes a slider at the designated area
  parameter:
        uint16_t* tempSlider : stores position of slider on page 1
*******************************************************************************/
void DrawTempSlider(uint16_t* tempSlider) {
  GUI_DrawRectangle(30, 200, 450, 290, GREEN, DRAW_FULL, DOT_PIXEL_DFT);
  GUI_DrawRectangle(30, 200, *tempSlider, 290, RED, DRAW_FULL, DOT_PIXEL_DFT);
}

/*******************************************************************************
  function:
        Makes a slider at the designated area
  parameter:
        uint16_t* brightSlider : stores position of slider on page 3
*******************************************************************************/
void DrawBrightSlider(uint16_t* brightSlider) {
  GUI_DrawRectangle(30, 200, 450, 290, GREEN, DRAW_FULL, DOT_PIXEL_DFT);
  GUI_DrawRectangle(30, 200, *brightSlider, 290, RED, DRAW_FULL, DOT_PIXEL_DFT);
}

/*******************************************************************************
  function:
        Checks to see where on the screen the user touched on a given page
  parameter:
        char* page             : stores which page the user is on
        int* charging          : sets charging method, 0 = Battery, 1 = Solar
        uint16_t* tempSlider   : stores position of slider on page 1
        uint16_t* brightSlider : stores position of slider on page 3
*******************************************************************************/
void DrawScreen(char* page, int* startAdjusting, int* charging, uint16_t* tempSlider, uint16_t* brightSlider) {
	if(*page == '0'){ // Home
		LCD_SetArealColor(0, 0, 480, 320, WHITE);
		GUI_DisString_EN(120, 40, "Choose An Option", &Font20, WHITE, RED);
		LCD_SetArealColor(20, 100, 220, 180, BLACK);
		GUI_DisString_EN(55, 140, "Adjust Temp", &Font16, BLACK, WHITE); // 1
		LCD_SetArealColor(260, 100, 460, 180, BLACK); 
		GUI_DisString_EN(280, 140, "Charging Method", &Font16, BLACK, WHITE); // 2
		LCD_SetArealColor(20, 220, 220, 300, BLACK); 
		GUI_DisString_EN(25, 260, "Adjust Brightness", &Font16, BLACK, WHITE); // 3
		LCD_SetArealColor(260, 220, 460, 300, BLACK); 
		GUI_DisString_EN(300, 260, "System Info", &Font16, BLACK, WHITE); // 4
	}
	else if(*page == '1'){ // Adjust Temperature
		DrawHomeButton();
   
    GUI_DrawRectangle(280, 20, 360, 60, RED, DRAW_FULL, DOT_PIXEL_DFT);
    GUI_DisString_EN(290, 30, "Begin", &Font16, RED, WHITE);
    GUI_DrawRectangle(380, 20, 460, 60, RED, DRAW_FULL, DOT_PIXEL_DFT);
    GUI_DisString_EN(400, 30, "Stop", &Font16, RED, WHITE);
    
		GUI_DisString_EN(60, 120, "Current Temp: ", &Font20, WHITE, RED);
    DrawTempSlider(tempSlider);

    // Selection Box
    DrawSelectionBoxTemp(startAdjusting);
	}
	else if(*page == '2'){ // Charging Method
		DrawHomeButton();
   
		GUI_DisString_EN(80, 120, "Choose Charging Method", &Font20, WHITE, RED);
		
		// Battery 
		GUI_DrawRectangle(20, 180, 230, 300, RED, DRAW_FULL, DOT_PIXEL_DFT);
		GUI_DisString_EN(60, 240, "Battery", &Font20, RED, WHITE);
		
		// Solar
		GUI_DrawRectangle(250, 180, 460, 300, RED, DRAW_FULL, DOT_PIXEL_DFT);
		GUI_DisString_EN(300, 240, "Solar", &Font20, RED, WHITE);

    // Selection Box
    DrawSelectionBoxCharging(charging);
	}
	else if(*page == '3'){ // Adjust Screen Brightness
		DrawHomeButton();
   
		GUI_DisString_EN(60, 120, "Set Brightness: ", &Font20, WHITE, RED);
    DrawBrightSlider(brightSlider);
	}
	else if(*page == '4'){ // System Info
		DrawHomeButton();
    GUI_DisString_EN(120, 40, "System Information", &Font24, WHITE, RED);
    GUI_DisString_EN(20, 120, "Microcontroller: ATmega328P/U", &Font16, WHITE, BLACK);
    GUI_DisString_EN(20, 140, "Prototype Board: Elegoo Uno", &Font16, WHITE, BLACK);
    GUI_DisString_EN(20, 160, "Screen: Waveshare 4inch TFT Touch Shield", &Font16, WHITE, BLACK);
    GUI_DisString_EN(20, 180, "Touch Controller: XPT2046", &Font16, WHITE, BLACK);
    GUI_DisString_EN(20, 200, "LCD Controller: ILI9486", &Font16, WHITE, BLACK);
	}
	else { // error
	
	}
}
