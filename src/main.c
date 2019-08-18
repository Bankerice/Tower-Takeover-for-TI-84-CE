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
	uint8_t towers[3] = {0,0,0}
;	uint8_t allianceS[3] = {0,0,0}
;	uint8_t enemyS[3] = {0,0,0}
;	uint8_t i
;

	uint8_t future[2][3][3]; ///ally/enemy | color | actions

	bool toUpdate[4];
	uint8_t allianceScore = 0, enemyScore = 0;

	gfx_Begin();
	initGUI();

	kb_SetMode(MODE_3_CONTINUOUS);


	//int numKeysPressed = 0

	do {
		while (kb_AnyKey());
		while (!kb_AnyKey()); //Stops for a key press

		update(towers, allianceS, enemyS, &autonWinner, toUpdate, &teamCol);

		if (toUpdate[UPDATE_CALCULATIONS]) {
			allianceScore = calcScore(towers, allianceS, autonWinner, TEAM_ALLIANCE);
			enemyScore = calcScore(towers, enemyS, autonWinner, TEAM_ENEMY);
			calcFuture(future, towers, allianceS, enemyS, autonWinner);
		}
		
		draw(&autonWinner, &teamCol, towers, allianceS, enemyS, future, allianceScore, enemyScore, toUpdate);
	} while (kb_Data[1] != kb_Graph);

	gfx_End();

	return 0;
}


void update(uint8_t towers[], uint8_t allianceStack[], uint8_t enemyStack[],
	auton* a, bool updates[], teamColor* col) {
	uint8_t inc = 1;
	uint8_t oldTowers[3], oldAllianceStack[3], oldEnemyStack[3];
	uint8_t towerTotal = 0, teamBlockTotal[3];
	uint8_t i;
		char emptyBuffer[10];
	//char * incString = malloc(3*sizeof(char));

	for (i = 0; i < 4; i++)
		updates[i] = 0;
	kb_Scan(); //DEBUG

		 if (kb_Data[4] & kb_2)	inc = 2;
	else if (kb_Data[5] & kb_3)	inc = 3;
	else if (kb_Data[3] & kb_4)	inc = 4;
	else if (kb_Data[4] & kb_5)	inc = 5;
	else if (kb_Data[5] & kb_6)	inc = 6;
	else if (kb_Data[3] & kb_7)	inc = 7;
	else if (kb_Data[4] & kb_8)	inc = 8;
	else if (kb_Data[5] & kb_9)	inc = 9;

	if (inc != 1) {
		while (kb_AnyKey());

		do {
			kb_Scan();
		} while (!(kb_AnyKey() && !(kb_Data[3] & 7 << 4 || kb_Data[4] & 7 << 4 || kb_Data[5] & 7 << 4))); 


	}

	memcpy(oldTowers, towers, 3 * sizeof(uint8_t));
	memcpy(oldAllianceStack, allianceStack, 3 * sizeof(uint8_t));
	memcpy(oldEnemyStack, enemyStack, 3 * sizeof(uint8_t));

	if (kb_Data[1] & kb_Yequ) {
		updates[UPDATE_TEAM_COLORS] = true;
		updates[UPDATE_AUTON] = true;
		*col = !*col;
	}
	else if (kb_Data[1] & kb_Trace)
		updates[UPDATE_RESET_BUTTON] = true;
	//NOTE: The quit button is incorporated in the main loop

	for (i = 0; i < 3; i++)
	{
		towerTotal += towers[i];
		teamBlockTotal[i] = allianceStack[i] + enemyStack[i];
	}


		 if (kb_Data[1] & kb_2nd)		towers[0] = (towerTotal + inc) > TOWER_LIMIT ? TOWER_LIMIT - (towerTotal - towers[0]) : inc + towers[0];
	else if (kb_Data[1] & kb_Mode)		towers[1] = (towerTotal + inc) > TOWER_LIMIT ? TOWER_LIMIT - (towerTotal - towers[1]) : inc + towers[1];
	else if (kb_Data[1] & kb_Del) 		towers[2] = (towerTotal + inc) > TOWER_LIMIT ? TOWER_LIMIT - (towerTotal - towers[2]) : inc + towers[2];
	else if (kb_Data[2] & kb_Alpha)		towers[0] = (towers[0] - inc) < 0 ? 0 : towers[0] - inc;
	else if (kb_Data[3] & kb_GraphVar)	towers[1] = (towers[1] - inc) < 0 ? 0 : towers[1] - inc;
	else if (kb_Data[4] & kb_Stat) 		towers[2] = (towers[2] - inc) < 0 ? 0 : towers[2] - inc;
	else if (kb_Data[2] & kb_Math) 		allianceStack[0] = (teamBlockTotal[0] + inc) > BLOCK_LIMIT ? BLOCK_LIMIT - enemyStack[0] : inc + allianceStack[0];
	else if (kb_Data[2] & kb_Recip) 	allianceStack[1] = (teamBlockTotal[1] + inc) > BLOCK_LIMIT ? BLOCK_LIMIT - enemyStack[1] : inc + allianceStack[1];
	else if (kb_Data[2] & kb_Square) 	allianceStack[2] = (teamBlockTotal[2] + inc) > BLOCK_LIMIT ? BLOCK_LIMIT - enemyStack[2] : inc + allianceStack[2];
	else if (kb_Data[3] & kb_Apps) 		allianceStack[0] = allianceStack[0] - inc < 0 ? 0 : allianceStack[0] - inc;
	else if (kb_Data[3] & kb_Sin) 		allianceStack[1] = allianceStack[1] - inc < 0 ? 0 : allianceStack[1] - inc;
	else if (kb_Data[3] & kb_Comma) 	allianceStack[2] = allianceStack[2] - inc < 0 ? 0 : allianceStack[2] - inc;
	else if (kb_Data[5] & kb_Vars) 		enemyStack[0] = teamBlockTotal[0] + inc > BLOCK_LIMIT ? BLOCK_LIMIT - allianceStack[0] : inc + enemyStack[0];
	else if (kb_Data[5] & kb_Tan) 		enemyStack[1] = teamBlockTotal[1] + inc > BLOCK_LIMIT ? BLOCK_LIMIT - allianceStack[1] : inc + enemyStack[1];
	else if (kb_Data[5] & kb_RParen) 	enemyStack[2] = teamBlockTotal[2] + inc > BLOCK_LIMIT ? BLOCK_LIMIT - allianceStack[2] : inc + enemyStack[2];
	else if (kb_Data[6] & kb_Clear) 	enemyStack[0] = enemyStack[0] - inc < 0 ? 0 : enemyStack[0] - inc;
	else if (kb_Data[6] & kb_Power) 	enemyStack[1] = enemyStack[1] - inc < 0 ? 0 : enemyStack[1] - inc;
	else if (kb_Data[6] & kb_Div) 		enemyStack[2] = enemyStack[2] - inc < 0 ? 0 : enemyStack[2] - inc;

	if (memcmp(towers, oldTowers, sizeof(towers)) ||
		memcmp(allianceStack, oldAllianceStack, sizeof(allianceStack)) ||
		memcmp(enemyStack, oldEnemyStack, sizeof(enemyStack)))
			updates[UPDATE_CALCULATIONS] = true;

	switch (kb_Data[2])
	{
	case kb_Log:
		*a = AUTON_WIN;
		updates[UPDATE_AUTON] = true;
		updates[UPDATE_CALCULATIONS] = true;
		break;
	case kb_Ln:
		*a = AUTON_LOSS;
		updates[UPDATE_AUTON] = true;
		updates[UPDATE_CALCULATIONS] = true;
		break;
	case kb_Sto:
		*a = AUTON_TIE;
		updates[UPDATE_AUTON] = true;
		updates[UPDATE_CALCULATIONS] = true;
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

void calcFuture(uint8_t future[2][3][3], uint8_t towers[3], uint8_t allianceStack[3], uint8_t enemyStack[3], auton a) {
	uint8_t tempTower[3];
	uint8_t teamStacks[2][3];
	uint8_t x, i;


	for (x = 0; x < 2; x++) { //for each team
		for (i = 0; i < 3; i++) { //for each color
			memcpy(teamStacks[0], allianceStack, 3*sizeof(uint8_t));
			memcpy(teamStacks[1], enemyStack, 3*sizeof(uint8_t));
			memcpy(tempTower, towers, 3*sizeof(uint8_t));

			teamStacks[x][i]++;
			future[x][i][CUBE_STACK] = x == 1 ? calcScore(towers, enemyStack, a, x+1) : calcScore(towers, teamStacks[x], a, x+1);
			teamStacks[x][i]--;

			tempTower[i]++;
			future[x][i][TOWER_ADD] = calcScore(tempTower, teamStacks[x], a, x+1);

			tempTower[i] -= 2;
			future[x][i][TOWER_REMOVE] = calcScore(tempTower, teamStacks[x], a, x+1);
		}
	}
}