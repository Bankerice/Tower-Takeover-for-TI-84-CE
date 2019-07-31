/*
* --------------------------------------
* Program Name : Tower Takeover Calculator for TI - 84 CE
* Author : Thomas Ji
* License : N / A
* Description : Takes input from the user, showing the best possible movesand the results of all possible actions in Tower Takeover, by Vex.
* --------------------------------------
*/

#include "main.h"


int main() {
	// Defaults the auton winner to a tie
	auton autonWinner = AUTON_TIE;

	uint8_t towers[3], allianceS[3], enemyS[3];
	uint8_t future[2][3][3];

	uint8_t allianceScore = 0, enemyScore = 0;

	kb_SetMode(MODE_3_CONTINUOUS);

	initializeGUI();

	do {
		update(towers, allianceS, enemyS, autonWinner);

		allianceScore = calcScore(towers, allianceS, autonWinner, TEAM_ALLIANCE);
		enemyScore = calcScore(towers, enemyS, autonWinner, TEAM_ENEMY);
		calcFuture(future, towers, allianceS, autonWinner);

		draw();
	} while (kb_Data[1] != kb_Graph);
	return 0;
}


void update(uint8_t towers[], uint8_t allianceStack[], uint8_t enemyStack[], auton a) {
	uint8_t num = 1;

	if (kb_Data[3] & kb_4)	num = 4;
	else if (kb_Data[3] & kb_7)	num = 7;
	else if (kb_Data[4] & kb_2)	num = 2;
	else if (kb_Data[4] & kb_5)	num = 5;
	else if (kb_Data[4] & kb_8)	num = 8;
	else if (kb_Data[5] & kb_3)	num = 3;
	else if (kb_Data[5] & kb_6)	num = 6;
	else if (kb_Data[5] & kb_9)	num = 9;

	if (kb_Data[1] & kb_2nd) towers[0] += num;
	else if (kb_Data[2] & kb_Alpha)	towers[0] -= num;
	else if (kb_Data[1] & kb_Mode)	towers[1] += num;
	else if (kb_Data[3] & kb_GraphVar)	towers[1] -= num;
	else if (kb_Data[1] & kb_Del) towers[2] += num;
	else if (kb_Data[4] & kb_Stat) towers[2] -= num;
	else if (kb_Data[2] & kb_Math) allianceStack[0] += num;
	else if (kb_Data[2] & kb_Recip) allianceStack[1] += num;
	else if (kb_Data[2] & kb_Square) allianceStack[2] += num;
	else if (kb_Data[3] & kb_Apps) allianceStack[0] -= num;
	else if (kb_Data[3] & kb_Sin) allianceStack[1] -= num;
	else if (kb_Data[3] & kb_Comma) allianceStack[2] -= num;
	else if (kb_Data[5] & kb_Vars) enemyStack[0] += num;
	else if (kb_Data[5] & kb_Tan) enemyStack[1] += num;
	else if (kb_Data[5] & kb_RParen) enemyStack[2] += num;
	else if (kb_Data[6] & kb_Clear) enemyStack[0] -= num;
	else if (kb_Data[6] & kb_Power) enemyStack[1] -= num;
	else if (kb_Data[6] & kb_Div) enemyStack[2] -= num;
}


uint8_t calcScore(uint8_t towers[], uint8_t stack[], auton a, team t) {
	uint8_t count = 0;

	for (uint8_t i = 0; i < 3; i++) {
		count += (towers[i] + 1) * stack[i];
	}

	count += (a == t ? 6 : a == AUTON_TIE ? 3 : 0);
	// count += (t == TEAM_ALLIANCE ? 1 : -1) * (-4.5 * pow(a, 2) + 7.5 * a) + 3;

	return count;
}

void calcFuture(uint8_t future[2][3][3], uint8_t towers[], uint8_t stack[], auton a) {
	uint8_t tempTower[3], tempAllianceStack[3];

	for (uint8_t x = 0; h < 2; x++) {
		for (uint8_t i = 0; i < 3; i++) {
			memcpy(tempTower, towers, 3 * sizeof(uint8_t));
			memcpy(tempAllianceStack, stack, 3 * sizeof(uint8_t));

			tempTower[i] += 1;
			future[x][i][0] = calcScore(tempTower, tempAllianceStack, a, x);

			tempTower[i] -= 2;
			future[x][i][1] = calcScore(tempTower, tempAllianceStack, a, x);

			tempAllianceStack[i] += 1;
			future[x][i][2] = calcScore(tempTower, tempAllianceStack, a, x);
		}
	}
}


void draw(void) {

}

void initializeGUI(void) {

}