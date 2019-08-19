#ifndef H_GRAPHICS
#define H_GRAPHICS

#include <graphx.h>

#include "gfx/symbols_gfx.h"
#include "main.h"

#define FONT_HEIGHT 8

void initGUI(void);
void drawNumberLayout();
void printStringCentered(const char* str, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t stringWidth, uint16_t stringHeight);
void spriteCentered(gfx_sprite_t* sprite, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t spriteWidth, uint16_t spriteHeight);
void debugPrintPalette();
void draw(auton autonWinner, teamColor col, uint8_t towers[], uint8_t allianceS[], uint8_t enemyS[], uint8_t future[2][3][3], uint8_t allianceScore, uint8_t enemyScore, bool updates[]);
void valid(bool validPrints[2][3][3], uint8_t towers[], uint8_t allianceS[], uint8_t enemyS[]);
void selectionSort(int8_t arr[], uint8_t n);
int compare(void * a, void * b);
int8_t indexOf(int8_t arr[], int8_t val, uint8_t indices);
#endif