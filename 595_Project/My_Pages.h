#include "LCD_Driver.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"

void Setup();
void Intro();
void DrawSelectionBoxCharging(int* charging);
void DrawSelectionBoxTemp(int* startAdjusting);
void DrawTempSlider(uint16_t* tempSlider);
void DrawBrightSlider(uint16_t* brightSlider);
void DrawScreen(char* page, int* startAdjusting, int* charging, uint16_t* tempSlider, uint16_t* brightSlider);
