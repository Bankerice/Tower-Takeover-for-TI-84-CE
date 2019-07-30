/*
* --------------------------------------
* Program Name : Tower Takeover Calculator for TI - 84 CE
* Author : Thomas Ji
* License : N / A
* Description : Takes input from the user, showing the best possible movesand the results of all possible actions in Tower Takeover, by Vex.
* --------------------------------------
*/

/* Keep these headers */
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <tice.h>

/* Standard headers (recommended) */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <keypadc.h>

/* Put your function prototypes here */
void copy(uint8_t original[], uint8_t copy[], uint8_t indexes);
void update(uint8_t towers[], uint8_t allianceStack[], uint8_t enemyStack[], enum auton a);
uint8_t calcScore(uint8_t towers[], uint8_t stack[], enum auton a, enum team t);
void calcFuture(uint8_t future[2][3][3], uint8_t towers[], uint8_t stack[], enum auton a);
void draw();
void initializeGUI();

typedef enum auton{okay, good, bad} ;
typedef enum team{ alliance, enemy } ;



	//************************************************************************************************************************************
	int main() {
		//os_ClrHome();

		//Defaults the auton winner to a tie (that's okay)
		enum auton autonWinner = okay;

		//Index: 0 - Orange | 1 - Green | 2 - Purple
		uint8_t towers[3], allianceS[3], enemyS[3];
		//1: Index    0 - Orange | 1 - Green | 2 - Purple
		//2: Index    0 - Tower Add | 1 - Tower Remove | 2 - Tower Stack		
		uint8_t future[2][3][3];

		uint8_t allianceScore = 0, enemyScore = 0;

        initializeGUI();

		do {

			//update

			update(towers, allianceS, enemyS, autonWinner);

			//calculate | DONE
			allianceScore = calcScore(towers, allianceS, autonWinner, alliance);
			enemyScore = calcScore(towers, enemyS, autonWinner, enemy);
			calcFuture(future, towers, allianceS, autonWinner);

			//redraw
			draw();

		} while (kb_Data[1] != kb_Graph);
		return 0;
	}





void copy(uint8_t original[], uint8_t copy[], uint8_t indexes) {
	uint8_t i;
	for (i = 0; i < indexes; i++) {
		copy[i] = original[i];
	}
}

void update(uint8_t towers[], uint8_t allianceStack[], uint8_t enemyStack[], enum auton a) {
	uint8_t num = 1;


	kb_Scan();

	if (kb_Data[3] & kb_4) {
		num = 4;
	}
	else if (kb_Data[3] & kb_7) {
		num = 7;
	}
	else if (kb_Data[4] & kb_2) {
		num = 2;
	}
	else if (kb_Data[4] & kb_5) {
		num = 5;
	}
	else if (kb_Data[4] & kb_8) {
		num = 8;
	}
	else if (kb_Data[5] & kb_3) {
		num = 3;
	}
	else if (kb_Data[5] & kb_6) {
		num = 6;
	}
	else if (kb_Data[5] & kb_9) {
		num = 9;
	}

	if (kb_Data[1] & kb_2nd) {
		towers[0] += num;
	}
	else if (kb_Data[2] & kb_Alpha) {
		towers[0] -= num;
	}
	else if (kb_Data[1] & kb_Mode) {
		towers[1] += num;
	}
	else if (kb_Data[3] & kb_GraphVar) {
		towers[1] -= num;
	}
	else if (kb_Data[1] & kb_Del) {
		towers[2] += num;
	}
	else if (kb_Data[4] & kb_Stat) {
		towers[2] -= num;
	}
	else if (kb_Data[2] & kb_Math) {
		allianceStack[0] += num;
	}
	else if (kb_Data[2] & kb_Recip) {
		allianceStack[1] += num;
	}
	else if (kb_Data[2] & kb_Square) {
		allianceStack[2] += num;
	}
	else if (kb_Data[3] & kb_Apps) {
		allianceStack[0] -= num;
	}
	else if (kb_Data[3] & kb_Sin) {
		allianceStack[1] -= num;
	}
	else if (kb_Data[3] & kb_Comma) {
		allianceStack[2] -= num;
	}
	else if (kb_Data[5] & kb_Vars) {
		enemyStack[0] += num;
	}
	else if (kb_Data[5] & kb_Tan) {
		enemyStack[1] += num;
	}
	else if (kb_Data[5] & kb_RParen) {
		enemyStack[2] += num;
	}
	else if (kb_Data[6] & kb_Clear) {
		enemyStack[0] -= num;
	}
	else if (kb_Data[6] & kb_Power) {
		enemyStack[1] -= num;
	}
	else if (kb_Data[6] & kb_Div) {
		enemyStack[2] -= num;
	}

}


	uint8_t calcScore(uint8_t towers[], uint8_t stack[], enum auton a, enum team t) {
		uint8_t count = 0;
		uint8_t i;
		for (i = 0; i < 3; i++) {
			count += (towers[i] + 1) * stack[i];
		}


		count += (t == alliance ? 1 : -1) * (-4.5 * pow(a, 2) + 7.5 * a) + 3;


		return count;
	}

	void calcFuture(uint8_t future[2][3][3], uint8_t towers[], uint8_t stack[], enum auton a) {
		uint8_t tempTower[3], tempAllianceStack[3], tempEnemyStack[3];

		uint8_t i;
		uint8_t h;

		for ( h = 0; h < 2; h++) {
			for (i = 0; i < 3; i++) {
				copy(towers, tempTower, 3);
				copy(stack, tempAllianceStack, 3);

				
				tempTower[i] += 1;
				future[h][i][0] = calcScore(tempTower, tempAllianceStack, a, h);

				tempTower[i] -= 2;
				future[h][i][1] = calcScore(tempTower, tempAllianceStack, a, h);

				tempAllianceStack[i] += 1;
				future[h][i][2] = calcScore(tempTower, tempAllianceStack, a, h);
			}
		}

	}


void draw() {

}

void initializeGUI() {

}