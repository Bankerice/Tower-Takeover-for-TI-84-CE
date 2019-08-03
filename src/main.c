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


int main() {
	// Defaults the auton winner to a tie
	auton autonWinner = AUTON_TIE;

	teamColor teamCol = TEAM_COLOR_RED;

	uint8_t towers[3], allianceS[3], enemyS[3];
	uint8_t future[2][3][3];

	bool toUpdate[4];

	uint8_t allianceScore = 0, enemyScore = 0;

	kb_SetMode(MODE_3_CONTINUOUS);

	gfx_Begin();
	initGUI();
	do {
		update(towers, allianceS, enemyS, &autonWinner, toUpdate, &teamCol);

		allianceScore = calcScore(towers, allianceS, autonWinner, TEAM_ALLIANCE);
		enemyScore = calcScore(towers, enemyS, autonWinner, TEAM_ENEMY);
		calcFuture(future, towers, allianceS, autonWinner);

		draw(teamCol, toUpdate);
	} while (kb_Data[1] != kb_Graph);
	gfx_End();
	return 0;
}

void assignKeyBind(updateKeyBind * kb, kb_lkey_t key, int8_t mult, uint8_t * ptr) {
	kb->key = key;
	kb->multiplier = mult;
	kb->ptr = ptr;
}

void update(uint8_t towers[], uint8_t allianceStack[], uint8_t enemyStack[],
			auton *a, bool updates[], teamColor *col) {
	uint8_t inc = 1;
	uint8_t oldTowers[3], oldAllianceStack[3], oldEnemyStack[3];

	uint8_t iter;

	uint16_t incrementors[10] = {
						   0, 0,
						   kb_Key2,	// 2
						   kb_Key3,	// 3
						   kb_Key4,	// 4
						   kb_Key5,	// 5
						   kb_Key6,	// 6
						   kb_Key7,	// 7
						   kb_Key8,	// 8
						   kb_Key9	// 9
						   };

	updateKeyBind keys[18];
	assignKeyBind( keys, 	   kb_Key2nd, 		 1,  towers);				// 2nd
	assignKeyBind((keys + 1),  kb_KeyAlpha, 	-1,  towers);				// Alpha
	assignKeyBind((keys + 2),  kb_KeyMode,	 	 1, (towers + 1));			// Mode
	assignKeyBind((keys + 3),  kb_KeyGraphVar,  -1, (towers + 1));			// X, T, Ѳ, n
	assignKeyBind((keys + 4),  kb_KeyDel,		 1, (towers + 2));			// Del
	assignKeyBind((keys + 5),  kb_KeyStat,		-1, (towers + 2));			// Stat
	assignKeyBind((keys + 6),  kb_KeyMath,		 1,  allianceStack);		// Math
	assignKeyBind((keys + 7),  kb_KeyRecip,	 	 1, (allianceStack + 1));	// Reciprocal
	assignKeyBind((keys + 8),  kb_KeySquare,	 1, (allianceStack + 2));	// Square
	assignKeyBind((keys + 9),  kb_KeyApps,		-1,  allianceStack);		// Apps
	assignKeyBind((keys + 10), kb_KeySin,		-1, (allianceStack + 1));	// Sin
	assignKeyBind((keys + 11), kb_KeyComma,		-1, (allianceStack + 2));	// Comma
	assignKeyBind((keys + 12), kb_KeyVars,		 1,  enemyStack);			// Vars
	assignKeyBind((keys + 13), kb_KeyTan,		 1, (enemyStack + 1));		// Tan
	assignKeyBind((keys + 14), kb_KeyRParen,	 1, (enemyStack + 2));		// RParen
	assignKeyBind((keys + 15), kb_KeyClear,		-1,  enemyStack);			// Clear
	assignKeyBind((keys + 16), kb_KeyPower,		-1, (enemyStack + 1));		// Power
	assignKeyBind((keys + 17), kb_KeyDiv,		-1, (enemyStack + 2));		// Divide
	

	for (iter = 2; iter <= 10; iter++) {
		if (kb_IsDown(incrementors[iter])) {
			inc = iter;
			break;
		}
	}
	
	memcpy(oldTowers, towers, 24);
	memcpy(oldAllianceStack, allianceStack, 24);
	memcpy(oldEnemyStack, enemyStack, 24);
	
	if(kb_Data[1] & kb_Yequ) {
		updates[0] = true;
		*col = *col == TEAM_COLOR_BLUE ? TEAM_COLOR_RED : TEAM_COLOR_BLUE;
	} else if(kb_Data[1] & kb_Trace)
		updates[1] = true;

	for (iter = 0; iter <=18; iter++) {
		if (kb_IsDown(keys[iter].key)) {
			*keys[iter].ptr = *keys[iter].ptr + (inc * keys[iter].multiplier);
		}
	}
	
	for (iter = 0; iter < 3; iter++) {
		if (towers[iter] == oldTowers[iter] ||
			allianceStack[iter] == oldAllianceStack[iter] ||
			enemyStack[iter] == oldEnemyStack[iter]) 
			{
				updates[2] = true;
			}
	}

	switch (kb_Data[2]) {
	case kb_Log:
		*a = AUTON_WIN;
		updates[3] = true;
		break;
	case kb_Ln:
		*a = AUTON_LOSS;
		updates[3] = true;
		break;
	case kb_Sto:
		*a = AUTON_TIE;
		updates[3] = true;
		break;
	}
}


uint8_t calcScore(uint8_t towers[], uint8_t stack[], auton a, team t) {
	uint8_t count = 0;

	uint8_t i = 0;
	for (i = 0; i < 3; i++) {
		count += (towers[i] + 1) * stack[i];
	}

	count += (a == t ? 6 : a == AUTON_TIE ? 3 : 0);
	// count += (t == TEAM_ALLIANCE ? 1 : -1) * (-4.5 * pow(a, 2) + 7.5 * a) + 3;

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
			future[x][i][0] = calcScore(tempTower, tempAllianceStack, a, x);

			tempTower[i] -= 2;
			future[x][i][1] = calcScore(tempTower, tempAllianceStack, a, x);

			tempAllianceStack[i] += 1;
			future[x][i][2] = calcScore(tempTower, tempAllianceStack, a, x);
		}
	}
}
