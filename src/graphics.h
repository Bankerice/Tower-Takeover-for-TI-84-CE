#ifndef H_GRAPHICS
#define H_GRAPHICS

#include <graphx.h>

#include "gfx/symbols_gfx.h"
#include "main.h"

#define FONT_HEIGHT 8

void initGUI(void);
void drawNumberLayout();
void printStringCentered(const char *str, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t stringWidth, uint8_t stringHeight);
void spriteCentered(gfx_sprite_t *sprite, uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t spriteWidth, uint8_t spriteHeight);
void debugPrintPalette();
void draw(auton *autonWinner, teamColor *col, uint8_t towers[], uint8_t allianceS[], uint8_t enemyS[], uint8_t future[2][3][3], bool updates[]);

#endif