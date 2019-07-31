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
} color;

typedef enum {
    TOWER_ADD = 0,
    TOWER_REMOVE,
    CUBE_STACK
} actions;

void copy(uint8_t original[], uint8_t copy[], uint8_t indexes);
void update(uint8_t towers[], uint8_t allianceStack[], uint8_t enemyStack[], auton a);
uint8_t calcScore(uint8_t towers[], uint8_t stack[], auton a, team t);
void calcFuture(uint8_t future[2][3][3], uint8_t towers[], uint8_t stack[], auton a);
void draw(void);
void initializeGUI(void);