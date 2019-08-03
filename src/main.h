#ifndef H_MAIN
#define H_MAIN

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <keypadc.h>


typedef enum { // auton
	AUTON_TIE = 0,
	AUTON_WIN,
	AUTON_LOSS
} auton;

typedef enum { // auton
	TEAM_ALLIANCE = 1,
	TEAM_ENEMY
} team;

typedef enum {
    CUBE_ORANGE = 0,
    CUBE_GREEN,
    CUBE_PURPLE
} cubeColor;

typedef enum {
    TOWER_ADD = 0,
    TOWER_REMOVE,
    CUBE_STACK
} actions;

typedef enum {
    UPDATE_TEAM_COLORS = 0,
    UPDATE_RESET_BUTTON,
    UPDATE_CALCULATIONS,
    UPDATE_AUTON
} thingsToUpdate;

typedef enum {
    TEAM_COLOR_RED = 0,
    TEAM_COLOR_BLUE
} teamColor;

void copy(uint8_t original[], uint8_t copy[], uint8_t indexes);
void update(uint8_t towers[], uint8_t allianceStack[], uint8_t enemyStack[], auton *a, bool updates[], teamColor *col);
uint8_t calcScore(uint8_t towers[], uint8_t stack[], auton a, team t);
void calcFuture(uint8_t future[2][3][3], uint8_t towers[], uint8_t stack[], auton a);

#endif