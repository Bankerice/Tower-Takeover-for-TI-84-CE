/*
* --------------------------------------
* Program Name : Tower Takeover Calculator for TI - 84 CE
* Author : Thomas Ji, Leo Riesenbach, Justina Lam
* License : N / A
* Description : Takes input from the user, showing the best possible movesand the results of all possible actions in Tower Takeover, by Vex.
* --------------------------------------
*/

#include "main.h"
#include "graphics.h"
#include "debug.h"

int main(void) {
	auton autonWinner = AUTON_TIE;
	teamColor teamCol = TEAM_COLOR_RED;

	uint8_t towers[3]    = {0, 0, 0},
			allianceS[3] = {0, 0, 0},
			enemyS[3]    = {0, 0, 0};

	uint16_t allianceScore = 0,
			 enemyScore = 0;

	uint8_t future[2][3][3]; // ally/enemy | color | actions

	bool toUpdate[4] = {true, true, true, true}; // All true but reset for initial draw

	kb_SetMode(MODE_3_CONTINUOUS);
	
	gfx_Begin();
	initGUI();

	calcFuture(future, towers, allianceS, enemyS, autonWinner);
	
	draw(autonWinner, teamCol, towers, allianceS, enemyS,
		 future, allianceScore, enemyScore, toUpdate);

	while (kb_Data[1] != kb_Graph) {
		/* While a key is held down that's not a number key 
		 * 
		 * You need it to keep looping while the number key is held down because otherwise
		 * you have to release and re-press the number key between action keys, and while that's
		 * not a huge deal, it's not expected behavior, and this can mitigate that issue.
		 */
		while (kb_AnyKey());
		// While no keys are pressed 
		while (!kb_AnyKey());

		update(towers, allianceS, enemyS, &autonWinner, toUpdate, &teamCol, future);

		if (toUpdate[UPDATE_RESET_BUTTON]) {
			autonWinner = AUTON_TIE;
			teamCol = TEAM_COLOR_RED;
			memset(towers, 0, 3 * sizeof(uint8_t));
			memset(allianceS, 0, 3 * sizeof(uint8_t));
			memset(enemyS, 0, 3 * sizeof(uint8_t));
			memset(future, 0, 12 * sizeof(uint8_t));
			allianceScore = 0;
			enemyScore = 0;
			toUpdate[UPDATE_CALCULATIONS] = true;
			toUpdate[UPDATE_TEAM_COLORS] = true;
			toUpdate[UPDATE_AUTON] = true;
			initGUI();
		};

		if (toUpdate[UPDATE_CALCULATIONS]) {
			allianceScore = calcScore(towers, allianceS, autonWinner, TEAM_ALLIANCE);
			enemyScore = calcScore(towers, enemyS, autonWinner, TEAM_ENEMY);
			calcFuture(future, towers, allianceS, enemyS, autonWinner);
		}
		
		draw(autonWinner, teamCol, towers, allianceS, enemyS,
			 future, allianceScore, enemyScore, toUpdate);

	}

	gfx_End();

	return 0;
}


void update(uint8_t towers[], uint8_t allianceStack[], uint8_t enemyStack[],
			auton* a, bool updates[], teamColor* col, uint8_t future[2][3][3]) {

	uint8_t inc = 1;
	uint8_t oldTowers[3], oldAllianceStack[3], oldEnemyStack[3];
	uint8_t towerTotal = 0, teamBlockTotal[3];
	uint16_t i;
	char emptyBuffer[10];

	bool gap = false;

	memset(updates, 0, 4 * sizeof(bool));

	inc = getInputNumber();

  		if (inc != 1) 
    		while (!(kb_ScanGroup(1) || kb_ScanGroup(2) || kb_ScanGroup(6) || kb_ScanGroup(7) || (kb_Data[3] & 240) || (kb_Data[4] & 240) || (kb_Data[5] & 240))) {
      		kb_Scan();
      		if (i = (getInputNumber()) == 1) {
        		while(kb_AnyKey()) kb_Scan();
        		while(!kb_AnyKey()) kb_Scan();
        		if(inc != i && i != 1)
          		inc = i;
      		}
    	}

	memcpy(oldTowers,		 towers, 		3 * sizeof(uint8_t));
	memcpy(oldAllianceStack, allianceStack, 3 * sizeof(uint8_t));
	memcpy(oldEnemyStack,	 enemyStack, 	3 * sizeof(uint8_t));

	if (kb_Data[1] & kb_Yequ) {
		updates[UPDATE_TEAM_COLORS] = true;
		updates[UPDATE_AUTON] = true;
		*col = !*col;
		return;
	}

	if (kb_Data[1] & kb_Trace){
		updates[UPDATE_RESET_BUTTON] = true;
		return;
	}

	for (i = 0; i < 3; i++) {
		towerTotal += towers[i];
		teamBlockTotal[i] = allianceStack[i] + enemyStack[i];
	}

	if (kb_Data[1] & kb_2nd) { 			// Orange Tower
		towers[CUBE_ORANGE] += inc;
		if (towers[0] + teamBlockTotal[0] + inc > CUBE_LIMIT)
			towers[CUBE_ORANGE] = CUBE_LIMIT - teamBlockTotal[0];
		if (towerTotal + inc > TOWER_LIMIT)
			towers[CUBE_ORANGE] = TOWER_LIMIT - (towerTotal - oldTowers[0]);
	} else if (kb_Data[1] & kb_Mode) { 	// Green Tower
		towers[CUBE_GREEN] += inc;
		if (towers[CUBE_GREEN] + teamBlockTotal[1] + inc > CUBE_LIMIT)
			towers[CUBE_GREEN] = CUBE_LIMIT - teamBlockTotal[1];
		if (towerTotal + inc > TOWER_LIMIT)
			towers[CUBE_GREEN] = TOWER_LIMIT - (towerTotal - oldTowers[1]);
	} else if (kb_Data[1] & kb_Del) {	// Purple Tower
		towers[CUBE_PURPLE] += inc;
		if (towers[2] + teamBlockTotal[2] + inc > CUBE_LIMIT)
			towers[CUBE_PURPLE] = CUBE_LIMIT - teamBlockTotal[2];
		if (towerTotal + inc > TOWER_LIMIT)
			towers[CUBE_PURPLE] = TOWER_LIMIT - (towerTotal - oldTowers[2]);
	} else if (kb_Data[2] & kb_Alpha) 	// Orange Detower
			   towers[CUBE_ORANGE] = (int8_t)(i = towers[0] - inc) < 0 ?
			   				0 : i;
	  else if (kb_Data[3] & kb_GraphVar) 	// Green Detower
	  		   towers[CUBE_GREEN] = (int8_t)(i = towers[1] - inc) < 0 ?
			     			0 : i;
	  else if (kb_Data[4] & kb_Stat) 	// Purple Detower
	  		   towers[CUBE_PURPLE] = (int8_t)(i = towers[2] - inc) < 0 ?
		  					0 : i;
	  else if (kb_Data[2] & kb_Math) 	// Orange Alliance Stack
	  	allianceStack[CUBE_ORANGE] = towers[0] + teamBlockTotal[0] + inc > CUBE_LIMIT ?
		  				   CUBE_LIMIT - enemyStack[0] - towers[0] : inc + allianceStack[0];
	  else if (kb_Data[2] & kb_Recip) 	// Green Alliance Stack
	  	allianceStack[CUBE_GREEN] = towers[1] + teamBlockTotal[1] + inc > CUBE_LIMIT ?
						   CUBE_LIMIT - enemyStack[1] - towers[1] : inc + allianceStack[1];
	  else if (kb_Data[2] & kb_Square) 	// Purple Alliance Stack
	  	allianceStack[CUBE_PURPLE] = towers[2] + teamBlockTotal[2] + inc > CUBE_LIMIT ?
						   CUBE_LIMIT - enemyStack[2] - towers[2] : inc + allianceStack[2];
	  else if (kb_Data[3] & kb_Apps) 	// Orange Alliance Destack
	  	allianceStack[CUBE_ORANGE] = (int8_t)(i = allianceStack[0] - inc) < 0 ?
		  					0 : i;
	  else if (kb_Data[3] & kb_Sin) 	// Green Alliance Destack
	  	allianceStack[CUBE_GREEN] = (int8_t)(i = allianceStack[1] - inc) < 0 ?
		  					0 : i;
	  else if (kb_Data[3] & kb_Comma) 	// Purple Alliance Destack
	  	allianceStack[CUBE_PURPLE] = (int8_t)(i = allianceStack[2] - inc) < 0 ?
		  					0 : i;
	  else if (kb_Data[5] & kb_Vars) 	// Orange Enemy Stack
	  	enemyStack[CUBE_ORANGE] = towers[0] + teamBlockTotal[0] + inc >CUBE_LIMIT ?
		  				CUBE_LIMIT - allianceStack[0] - towers[0] : inc + enemyStack[0];
	  else if (kb_Data[5] & kb_Tan) 	// Green Enemy Stack
	  	enemyStack[CUBE_GREEN] = towers[1] + teamBlockTotal[1] + inc > CUBE_LIMIT ?
		  				CUBE_LIMIT - allianceStack[1] - towers[1] : inc + enemyStack[1];
	  else if (kb_Data[5] & kb_RParen) 	// Purple Enemy Stack
	  	enemyStack[CUBE_PURPLE] = towers[2] + teamBlockTotal[2] + inc > CUBE_LIMIT ?
		  				CUBE_LIMIT - allianceStack[2] - towers[2] : inc + enemyStack[2];
	  else if (kb_Data[6] & kb_Clear) 	// Orange Enemy Destack
	  	enemyStack[CUBE_ORANGE] = (int8_t)(i = enemyStack[0] - inc) < 0 ?
		  				 0 : i;
	  else if (kb_Data[6] & kb_Power) 	// Green Enemy Destack
	  	enemyStack[CUBE_GREEN] = (int8_t)(i = enemyStack[1] - inc) < 0 ?
		  				 0 : i;
	  else if (kb_Data[6] & kb_Div) 	// Purple Enemy Destack
	  	enemyStack[CUBE_PURPLE] = (int8_t)(i = enemyStack[2] - inc) < 0 ?
		  				 0 : i;

	if (memcmp(towers, oldTowers, sizeof(towers)) ||
		memcmp(allianceStack, oldAllianceStack, sizeof(allianceStack)) ||
		memcmp(enemyStack, oldEnemyStack, sizeof(enemyStack)))
			updates[UPDATE_CALCULATIONS] = true;

	switch (kb_Data[2])	{
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


uint8_t calcScore(uint8_t towers[], uint8_t stack[], auton autonWinner, team teamToCalc) {
	uint8_t count = 0;
	uint8_t i;

	for (i = 0; i < 3; i++)
		count += (towers[i] + 1) * stack[i];

	// Add the autonomous bonus
	count += autonWinner == teamToCalc ? 6 : autonWinner == AUTON_TIE ? 3 : 0;
	return count;
}


void calcFuture(uint8_t future[2][3][3], uint8_t towers[3], uint8_t allianceStack[3],
				uint8_t enemyStack[3], auton autonWinner) {

	uint8_t tempTower[3];
	uint8_t teamStacks[2][3];
	uint8_t teamIter, colorIter;

	for (teamIter = 0; teamIter < 2; teamIter++) {
		for (colorIter = 0; colorIter < 3; colorIter++) {
			memcpy(teamStacks[0], allianceStack, 3 * sizeof(uint8_t));
			memcpy(teamStacks[1], enemyStack,	 3 * sizeof(uint8_t));
			memcpy(tempTower,	  towers,		 3 * sizeof(uint8_t));

			teamStacks[teamIter][colorIter]++;

			future[teamIter][colorIter][CUBE_STACK] = 
					calcScore(towers, (teamIter == 1 ? enemyStack : teamStacks[teamIter]),
							  autonWinner, teamIter + 1);

			teamStacks[teamIter][colorIter]--;

			tempTower[colorIter]++;
			future[teamIter][colorIter][TOWER_ADD] =
					calcScore(tempTower, teamStacks[teamIter], autonWinner, teamIter+1);

			tempTower[colorIter] -= 2;
			future[teamIter][colorIter][TOWER_REMOVE] =
					calcScore(tempTower, teamStacks[teamIter], autonWinner, teamIter+1);
		}
	 }
}
