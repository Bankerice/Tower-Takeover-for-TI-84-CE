/*
* --------------------------------------
* Program Name : Tower Takeover Calculator for TI - 84 CE
* Author : Thomas Ji
* License : N / A
* Description : Takes input from the user, showing the best possible movesand the results of all possible actions in Tower Takeover, by Vex.
* --------------------------------------
*/

#include "main.h"
#include "graphics.h"

#define TOWER_LIMIT 7
#define BLOCK_LIMIT 22


int main() {
	// Defaults the auton winner to a tie
	auton autonWinner = AUTON_TIE;

	teamColor teamCol = TEAM_COLOR_RED;
	uint8_t towers[3], allianceS[3], enemyS[3];
	uint8_t future[2][3][3]; ///ally/enemy | color | actions

	bool toUpdate[4];
	uint8_t allianceScore = 0, enemyScore = 0;

	gfx_Begin();
	initGUI();

	kb_SetMode(MODE_0_IDLE);


	do {

		while (kb_AnyKey()); //Stops for a button hold
		while (!kb_AnyKey()); //Stops for a key press

		kb_Scan();

		update(towers, allianceS, enemyS, &autonWinner, toUpdate, &teamCol);

		if (toUpdate[UPDATE_CALCULATIONS]) {
			allianceScore = calcScore(towers, allianceS, autonWinner, TEAM_ALLIANCE);
			enemyScore = calcScore(towers, enemyS, autonWinner, TEAM_ENEMY);
			calcFuture(future, towers, allianceS, autonWinner);
		}

		draw(&autonWinner, &teamCol, towers, allianceS, enemyS, future, toUpdate);
	} while (kb_Data[1] != kb_Graph);

	gfx_End();

	return 0;
}


void update(uint8_t towers[], uint8_t allianceStack[], uint8_t enemyStack[],
	auton* a, bool updates[], teamColor* col) {
	uint8_t inc = 1;
	uint8_t oldTowers[3], oldAllianceStack[3], oldEnemyStack[3];
	uint8_t towerTotal = 0, allianceTotal = 0, enemyTotal = 0;
	uint8_t i;

	for (i = 0; i < 4; i++)
		updates[i] = 0;

		 if (kb_Data[4] & kb_2)	inc = 2;
	else if (kb_Data[5] & kb_3)	inc = 3;
	else if (kb_Data[3] & kb_4)	inc = 4;
	else if (kb_Data[4] & kb_5)	inc = 5;
	else if (kb_Data[5] & kb_6)	inc = 6;
	else if (kb_Data[3] & kb_7)	inc = 7;
	else if (kb_Data[4] & kb_8)	inc = 8;
	else if (kb_Data[5] & kb_9)	inc = 9;


	memcpy(oldTowers, towers, 3 * sizeof(uint8_t));
	memcpy(oldAllianceStack, allianceStack, 3 * sizeof(uint8_t));
	memcpy(oldEnemyStack, enemyStack, 3 * sizeof(uint8_t));

	if (kb_Data[1] & kb_Yequ) {
		updates[UPDATE_TEAM_COLORS] = true;
		*col = !*col;
	}
	else if (kb_Data[1] & kb_Trace)
		updates[UPDATE_RESET_BUTTON] = true;
	//NOTE: The quit button is incorporated in the main loop

	for (i = 0; i < 3; i++)
	{
		towerTotal += towers[i];
		allianceTotal += allianceStack[i];
		enemyTotal += enemyStack[i];
	}

		 if (kb_Data[1] & kb_2nd)		towers[0] = (towerTotal + inc) > TOWER_LIMIT ? towerTotal - towers[1] + towers[2] : inc + towers[0];
	else if (kb_Data[1] & kb_Mode)		towers[1] = towerTotal + inc > TOWER_LIMIT ? towerTotal - (towers[0] + towers[2]) : inc + towers[2];
	else if (kb_Data[1] & kb_Del) 		towers[2] = towerTotal + inc > TOWER_LIMIT ? towerTotal - (towers[0] + towers[1]) : inc + towers[1];
	else if (kb_Data[2] & kb_Alpha)		towers[0] = towers[0] - inc < 0 ? 0 : towers[0] - inc;
	else if (kb_Data[3] & kb_GraphVar)	towers[1] = towers[1] - inc < 0 ? 0 : towers[1] - inc;
	else if (kb_Data[4] & kb_Stat) 		towers[2] = towers[2] - inc < 0 ? 0 : towers[2] - inc;
	else if (kb_Data[2] & kb_Math) 		allianceStack[0] = allianceTotal + enemyTotal + inc > BLOCK_LIMIT ? BLOCK_LIMIT - (enemyTotal + allianceStack[1] + allianceStack[2]) : inc + allianceStack[0];
	else if (kb_Data[2] & kb_Recip) 	allianceStack[1] = allianceTotal + enemyTotal + inc > BLOCK_LIMIT ? BLOCK_LIMIT - (enemyTotal + allianceStack[0] + allianceStack[2]) : inc + allianceStack[1];
	else if (kb_Data[2] & kb_Square) 	allianceStack[2] = allianceTotal + enemyTotal + inc > BLOCK_LIMIT ? BLOCK_LIMIT - (enemyTotal + allianceStack[0] + allianceStack[1]) : inc + allianceStack[2];
	else if (kb_Data[3] & kb_Apps) 		allianceStack[0] = allianceStack[0] - inc < 0 ? 0 : allianceStack[0] - inc;
	else if (kb_Data[3] & kb_Sin) 		allianceStack[1] = allianceStack[1] - inc < 0 ? 0 : allianceStack[1] - inc;
	else if (kb_Data[3] & kb_Comma) 	allianceStack[2] = allianceStack[2] - inc < 0 ? 0 : allianceStack[2] - inc;
	else if (kb_Data[5] & kb_Vars) 		enemyStack[0] = allianceTotal + enemyTotal + inc > BLOCK_LIMIT ? BLOCK_LIMIT - (allianceTotal + enemyStack[1] + enemyStack[2]) : inc + enemyStack[0];
	else if (kb_Data[5] & kb_Tan) 		enemyStack[1] = allianceTotal + enemyTotal + inc > BLOCK_LIMIT ? BLOCK_LIMIT - (allianceTotal + enemyStack[0] + enemyStack[2]) : inc + enemyStack[1];
	else if (kb_Data[5] & kb_RParen) 	enemyStack[2] = allianceTotal + enemyTotal + inc > BLOCK_LIMIT ? BLOCK_LIMIT - (allianceTotal + enemyStack[0] + enemyStack[1]) : inc + enemyStack[2];
	else if (kb_Data[6] & kb_Clear) 	enemyStack[0] = enemyStack[0] - inc < 0 ? 0 : enemyStack[0] - inc;
	else if (kb_Data[6] & kb_Power) 	enemyStack[1] = enemyStack[1] - inc < 0 ? 0 : enemyStack[1] - inc;
	else if (kb_Data[6] & kb_Div) 		enemyStack[2] = enemyStack[2] - inc < 0 ? 0 : enemyStack[1] - inc;

	if (memcmp(towers, oldTowers, sizeof(towers)) ||
		memcmp(allianceStack, oldAllianceStack, sizeof(allianceStack)) ||
		memcmp(enemyStack, oldEnemyStack, sizeof(enemyStack)))
			updates[UPDATE_CALCULATIONS] = true;

	switch (kb_Data[2])
	{
	case kb_Log:
		*a = AUTON_WIN;
		updates[UPDATE_AUTON] = true;
		break;
	case kb_Ln:
		*a = AUTON_LOSS;
		updates[UPDATE_AUTON] = true;
		break;
	case kb_Sto:
		*a = AUTON_TIE;
		updates[UPDATE_AUTON] = true;
		break;
	}
}


uint8_t calcScore(uint8_t towers[], uint8_t stack[], auton a, team t) {
	uint8_t count = 0;

	uint8_t i;
	for (i = 0; i < 3; i++)
		count += (towers[i] + 1) * stack[i];

	count += (a == t ? 6 : a == AUTON_TIE ? 3 : 0);
	return count;
}

void calcFuture(uint8_t future[2][3][3], uint8_t towers[], uint8_t stack[], auton a) {
	uint8_t tempTower[3], tempAllianceStack[3];

	uint8_t x, i;
	for (x = 0; x < 2; x++) {
		for (i = 0; i < 3; i++) {
			memcpy(tempTower, towers, 3 * sizeof(uint8_t));
			memcpy(tempAllianceStack, stack, 3 * sizeof(uint8_t));

			tempTower[i] += 1;
			future[x][i][TOWER_ADD] = calcScore(tempTower, tempAllianceStack, a, x);

			tempTower[i] -= 2;
			future[x][i][TOWER_REMOVE] = calcScore(tempTower, tempAllianceStack, a, x);

			tempAllianceStack[i] += 1;
			future[x][i][CUBE_STACK] = calcScore(tempTower, tempAllianceStack, a, x);
		}
	}
}
