/*
* --------------------------------------
* Program Name : Tower Takeover Calculator for TI - 84 CE
* Author : Thomas Ji
* License : N / A
* Description : Takes input from the user, showing the best possible movesand the results of all possible actions in Tower Takeover, by Vex.
* --------------------------------------
*/

#include "graphics.h"
#include "debug.h"

#define FONT_HEIGHT 8

void initGUI(void) {
	/*
	 *  Draws all the framing, grids, and all of the +/-0 default values for the GUI
	 *  as well as all the permanent text and the static symbols
	 */
	uint8_t iter = 0;

	// Initialize the 8bit/pixel graphics
	gfx_SetTransparentColor(PALLETE_WHITE);
	gfx_SetPalette(symbols_gfx_pal, sizeof_symbols_gfx_pal, 0);
	gfx_FillScreen(PALLETE_WHITE);

	// Draws the grid box
	gfx_SetColor(PALLETE_BLACK);
	gfx_Rectangle_NoClip(0, 0, 165, 224);
	gfx_Rectangle_NoClip(1, 1, 163, 222);

	// Draw the horizontal grid lines
	for (iter = 0; iter < 16; iter++) {
		switch (iter) {
		case 0: case 3: case 6: case 7: case 10: case 13:
			gfx_HorizLine_NoClip(2, 14 + (iter * 13), 161);
			gfx_HorizLine_NoClip(2, 15 + (iter * 13), 161);
			break;
		default:
			gfx_HorizLine_NoClip(41, 14 + (iter * 13), 122);
			gfx_HorizLine_NoClip(41, 15 + (iter * 13), 122);
			break;
		}
	}

	// Draw the vertical grid lines
	gfx_VertLine_NoClip(39, 2, 220);
	gfx_VertLine_NoClip(40, 2, 220);
	gfx_VertLine_NoClip(86, 2, 51);
	gfx_VertLine_NoClip(87, 2, 51);
	gfx_VertLine_NoClip(86, 94, 128);
	gfx_VertLine_NoClip(87, 94, 128);
	gfx_VertLine_NoClip(133, 2, 220);
	gfx_VertLine_NoClip(134, 2, 220);

	// Delta box
	spriteCentered(deltaTextBox, 135, 2, 162, 13, deltaTextBox_width, deltaTextBox_height);

	// Draw the first 6 normal orange/green/purple boxes
	gfx_TransparentSprite_NoClip(orangeTextBox, 41, 16);
	gfx_TransparentSprite_NoClip(orangeTextBox, 88, 16);
	gfx_TransparentSprite_NoClip(greenTextBox, 41, 29);
	gfx_TransparentSprite_NoClip(greenTextBox, 88, 29);
	gfx_TransparentSprite_NoClip(purpleTextBox, 41, 42);
	gfx_TransparentSprite_NoClip(purpleTextBox, 88, 42);

	// Draw the three long orange/green/purple boxes
	gfx_TransparentSprite_NoClip(orangeTextBoxLong, 41, 55);
	gfx_TransparentSprite_NoClip(greenTextBoxLong, 41, 68);
	gfx_TransparentSprite_NoClip(purpleTextBoxLong, 41, 81);

	// Draw the red text boxes and the other 27 orange/green/purple boxes
	for (iter = 1; iter < 8; iter += 3) {
		gfx_TransparentSprite_NoClip(orangeTextBox,       41, 94 + (iter * 13));
		gfx_TransparentSprite_NoClip(orangeTextBox,       88, 94 + (iter * 13));
		gfx_TransparentSprite_NoClip(shortOrangeTextBox, 135, 94 + (iter * 13));
	}
	for (iter = 2; iter < 9; iter += 3) {
		gfx_TransparentSprite_NoClip(greenTextBox,       41, 94 + (iter * 13));
		gfx_TransparentSprite_NoClip(greenTextBox,       88, 94 + (iter * 13));
		gfx_TransparentSprite_NoClip(shortGreenTextBox, 135, 94 + (iter * 13));
	}
	for (iter = 3; iter < 10; iter += 3) {
		gfx_TransparentSprite_NoClip(purpleTextBox,       41, 94 + (iter * 13));
		gfx_TransparentSprite_NoClip(purpleTextBox,       88, 94 + (iter * 13));
		gfx_TransparentSprite_NoClip(shortPurpleTextBox, 135, 94 + (iter * 13));
	}
	gfx_TransparentSprite_NoClip(redTextBox,       41, 94);
	gfx_TransparentSprite_NoClip(redTextBox,       88, 94);
	gfx_TransparentSprite_NoClip(shortRedTextBox, 135, 94);
	
	// Draw the gray box in the delta-X column
	gfx_SetColor(PALLETE_GRAY);
	gfx_FillRectangle_NoClip(135, 16, 28, 76);

	// Draw the black header text and a sprite for the Delta-X
	gfx_SetTextFGColor(PALLETE_BLACK);
	printStringCentered("SCO",   2, 94,  38, 104, FONT_HEIGHT);
	printStringCentered("Team",   2, 2,  38,  13, FONT_HEIGHT);
	printStringCentered("Ally",  41, 2,  85,  13, FONT_HEIGHT);
	printStringCentered("Enemy", 88, 2, 132,  13, FONT_HEIGHT);
	gfx_TransparentSprite_NoClip(deltaXText, 141, 4);


	// Draw the symbols on the side of the grid
	gfx_TransparentSprite_NoClip(genericCube, 2, 16);
	gfx_TransparentSprite_NoClip(emptyTower, 2, 55);
	gfx_TransparentSprite_NoClip(stackedCube, 2, 107);
	gfx_TransparentSprite_NoClip(towerAdd, 2, 146);
	gfx_TransparentSprite_NoClip(towerRemove, 2, 185);

	// Draw the bottom panels
	for (iter = 0; iter < 5; iter++)
		gfx_TransparentSprite_NoClip(bottomPanel, 64 * iter, 224);
	printStringCentered("Reset", 194, 226, 253, 237, FONT_HEIGHT);
	gfx_PrintStringXY("Quit", 275, 228);
	gfx_SetColor(PALLETE_BLACK);
	gfx_FillRectangle_NoClip(13,228, 51-13, 236-228);

	// Draw the framing for the best action boxes
	for (iter = 0; iter < 3; iter++) {
		gfx_Rectangle_NoClip(175 + 47 * iter, 92, 41, 54);
		gfx_Rectangle_NoClip(176 + 47 * iter, 93, 39, 52);
		gfx_HorizLine_NoClip(177 + 47 * iter, 131, 37);
		gfx_HorizLine_NoClip(177 + 47 * iter, 132, 37);
	}

	// Best action box rectangles
	gfx_SetColor(PALLETE_GOLD  );   gfx_FillRectangle_NoClip(177, 94, 37, 37);
	gfx_SetColor(PALLETE_SILVER);   gfx_FillRectangle_NoClip(224, 94, 37, 37);
	gfx_SetColor(PALLETE_BRONZE);   gfx_FillRectangle_NoClip(271, 94, 37, 37);


	gfx_TransparentSprite_NoClip(greenAuton,178,20);
	gfx_SetColor(PALLETE_BLACK);
}

void printStringCentered(const char * str, const uint16_t x1, const uint16_t y1, 
						 const uint16_t x2, const uint16_t y2, const uint16_t stringHeight) {
	/*
	 *  Calculates the XY coordinate values needed to keep a string centered in a box
	 *  and prints the string using the stdlib gfx_PrintStringXY function.
	 *  Used to center strings where the number of characters is variable.
	 *
	 *  Params:
	 *   const char * str: String that will be printed
	 *   uint16_t x1, y1, x2, y2: Coordinates in which the string will be centered
	 *   uint16_t stringHeight: Height in pixels of the text, will usually be FONT_HEIGHT
	 */

	uint16_t stringWidth = gfx_GetStringWidth(str);
	gfx_PrintStringXY(str, x1 + ((2 + x2 - x1) - stringWidth) / 2,   // Calculate X center
						   y1 + ((2 + y2 - y1) - stringHeight) / 2); // Calculate Y center
}


void spriteCentered(gfx_sprite_t * sprite, const uint16_t x1, const uint16_t y1,
										   const uint16_t x2, const uint16_t y2,
					const uint16_t spriteWidth, const uint16_t spriteHeight) {
	/*
	 *  Calculates the XY coordinate values needed to keep a sprite centered in a box
	 *  and prints the sprite using the stdlib gfx_TransparentSprite_NoClip function.
	 *  Used to center when the identity and therefore size of the sprite is variable.
	 *
	 *  Params:
	 *   gfx_sprite_t * sprite: Sprite to be drawn
	 *   uint16_t x1, y1, x2, y2: Coordinates in which the sprite will be centered
	 *   uint16_t spriteWidth: Width of sprite in pixels
	 *   uint16_t spriteHeight: Height of sprite in pixels
	 */

	gfx_TransparentSprite_NoClip(sprite, x1 + ((2 + x2 - x1) - spriteWidth ) / 2,  // X calcs
								         y1 + ((2 + y2 - y1) - spriteHeight) / 2); // Y calcs
}

void printIntCentered(const int num, const uint16_t x1, const uint16_t y1, 
					  const uint16_t x2, const uint16_t y2, const uint16_t fontHeight) {
		char buffer[10];
		sprintf(buffer, "%d", num);
		printStringCentered(buffer, x1, y1, x2, y2, fontHeight);
	}

void draw(auton autonWinner, teamColor col, uint8_t towers[], uint8_t allianceS[],
		  uint8_t enemyS[], uint8_t future[2][3][3], uint16_t allianceScore,
		  uint16_t enemyScore, bool updates[]) {

	uint8_t i;
	uint8_t teamIter, colorIter, actionIter;
	
	bool validPrints[2][3][3];
	int8_t futureDeltas[9];
	int8_t diffs[10];
	struct recommendation_t sortedDiffs[10];
	uint8_t interval, x, y;
	uint8_t delta;

	char buffer[10];

	/* Handles changing the colors depending on what team color you are.
	 * Colors change in the top headers, the Auton buttons, the rectangle
	 * at the bottom (representing the color changing button), and the text
	 * changes in the header as well to keep Ally on the right.
	 */
	if (updates[UPDATE_TEAM_COLORS]){

		// Draws in the header boxes and auton boxes with the right color,
		// changes pallete color for the rectangle at the bottom.
		if (col == TEAM_COLOR_BLUE) { // Blue
			gfx_TransparentSprite_NoClip(blueTeamTextBox, 41, 2);
			gfx_TransparentSprite_NoClip(redTeamTextBox, 88, 2);
			gfx_TransparentSprite_NoClip(blueAuton, 170, 4);
			gfx_TransparentSprite_NoClip(redAuton, 185, 4);
			gfx_SetColor(PALLETE_BLUE);
		} else { // Red
			gfx_TransparentSprite_NoClip(redTeamTextBox, 41, 2);
			gfx_TransparentSprite_NoClip(blueTeamTextBox, 88, 2);
			gfx_TransparentSprite_NoClip(redAuton, 170, 4);
			gfx_TransparentSprite_NoClip(blueAuton, 185, 4);
			gfx_SetColor(PALLETE_RED);
		}
		gfx_FillRectangle_NoClip(15, 230, 34, 4); // Bottom left color rectangle

		printStringCentered("Ally", 41, 2, 85, 13, FONT_HEIGHT);
		printStringCentered("Enemy", 88, 2, 132, 13, FONT_HEIGHT);

	}

	/* Handles redrawing all the scores, futures, deltas, and recommendation boxes
	 * for the entire program. Redraws all the empty boxes first to cover up the old
	 * scores, then fills in the numbers	, leaving dashes instead of numbers for all
	 * actions where completing them would either exceed the tower or cube limit or
	 * it would have less than 0 of something (this is valid() and validPrints[2][3][3]).
	 * Also covers up the old recommendation boxes then finds the best actions to take 
	 * delta-wise using a sorted copy of diffs[10] (the deltas), sortedDiffs[10] and
	 * draws in the corresponding sprite(s) and deltas.
	 */
	if (updates[UPDATE_CALCULATIONS]) {
		valid(validPrints, towers, allianceS, enemyS);
		// Draw the stacked cube counter boxes
		gfx_TransparentSprite_NoClip(orangeTextBox, 41, 16);
		gfx_TransparentSprite_NoClip(orangeTextBox, 88, 16);
		gfx_TransparentSprite_NoClip(greenTextBox, 41, 29);
		gfx_TransparentSprite_NoClip(greenTextBox, 88, 29);
		gfx_TransparentSprite_NoClip(purpleTextBox, 41, 42);
		gfx_TransparentSprite_NoClip(purpleTextBox, 88, 42);

		// Draw the tower cube counter boxes
		gfx_TransparentSprite_NoClip(orangeTextBoxLong, 41, 55);
		gfx_TransparentSprite_NoClip(greenTextBoxLong, 41, 68);
		gfx_TransparentSprite_NoClip(purpleTextBoxLong, 41, 81);

		
		// Draw the red text boxes and the other 27 orange/green/purple boxes
		for (i = 1; i < 8; i += 3) {
			interval = i * 13;
			gfx_TransparentSprite_NoClip(orangeTextBox,       41, 94 + interval);
			gfx_TransparentSprite_NoClip(orangeTextBox,       88, 94 + interval);
			gfx_TransparentSprite_NoClip(shortOrangeTextBox, 135, 94 + interval);
		}
		for (i = 2; i < 9; i += 3) {
			interval = i * 13;
			gfx_TransparentSprite_NoClip(greenTextBox,       41, 94 + interval);
			gfx_TransparentSprite_NoClip(greenTextBox,       88, 94 + interval);
			gfx_TransparentSprite_NoClip(shortGreenTextBox, 135, 94 + interval);
		}
		for (i = 3; i < 10; i += 3) {
			interval = i * 13;
			gfx_TransparentSprite_NoClip(purpleTextBox,       41, 94 + interval);
			gfx_TransparentSprite_NoClip(purpleTextBox,       88, 94 + interval);
			gfx_TransparentSprite_NoClip(shortPurpleTextBox, 135, 94 + interval);
		}
		gfx_TransparentSprite_NoClip(redTextBox, 41, 94);
		gfx_TransparentSprite_NoClip(redTextBox, 88, 94);
		gfx_TransparentSprite_NoClip(shortRedTextBox, 135, 94);


		// Draw text boxes for the recommended action score deltas
		for (i = 0; i < 3; i++)
			gfx_TransparentSprite_NoClip(recommendationScore, 177 + (i * 47), 133);

		// Draw stacked cube counters
		for (i = 0; i < 3; i++) {
			interval = i * 13;
			printIntCentered(allianceS[i], 41, 16 + interval, 85, 26 + interval, FONT_HEIGHT);
		}
		for (i = 0; i < 3; i++) {
			interval = i * 13;
			printIntCentered(enemyS[i], 88, 16 + interval, 132, 26 + interval, FONT_HEIGHT);
		}

		// Draw the tower cube counters
		for (i = 0; i < 3; i++) {
			interval = i * 13;
			printIntCentered(towers[i], 41, 55 + interval, 132, 65 + interval, FONT_HEIGHT);
		}

		// Draw the current score text
		printIntCentered(allianceScore, 41, 94, 41 + redTextBox_width,
						 94 + redTextBox_height, FONT_HEIGHT);
		printIntCentered(enemyScore, 88, 94, 88 + redTextBox_width,
						 94 + redTextBox_height, FONT_HEIGHT);

		// Draw the recommended action boxes
		gfx_SetColor( PALLETE_GOLD );   gfx_FillRectangle_NoClip(177, 94, 37, 37);
		gfx_SetColor(PALLETE_SILVER);   gfx_FillRectangle_NoClip(224, 94, 37, 37);
		gfx_SetColor(PALLETE_BRONZE);   gfx_FillRectangle_NoClip(271, 94, 37, 37);

		// Print all the future action scores
		for (teamIter = 0; teamIter < 2; teamIter++) {
			for (colorIter = 0; colorIter < 3; colorIter++) {
				for(actionIter = 0; actionIter < 3; actionIter++) {
					sprintf(buffer, "%u", future[teamIter][colorIter][actionIter]);
					printStringCentered(
						validPrints[teamIter][colorIter][actionIter] ? buffer : "---", // str
						(x = 41 + (47 * teamIter)), // x1
						(y = 107 + (13 * ((actionIter * 3) + colorIter))), // y1
						x + redTextBox_width, // x2
						y + redTextBox_height, // y2
						FONT_HEIGHT // stringHeight
						);
					memset(buffer, 0, 10 * sizeof(uint8_t));
				}
			}
		}

		// Assigns all the deltas to the place in the diffs array
		diffs[0] = allianceScore - enemyScore;
		for (colorIter = 0; colorIter < 3; colorIter++)
			for (actionIter = 0; actionIter < 3; actionIter++) {
				diffs[actionIter + (3 * colorIter) + 1] =
						  future[TEAM_ALLIANCE - 1][actionIter][colorIter]
						- future[TEAM_ENEMY    - 1][actionIter][colorIter]
						- diffs[0];
			}
		

		// Draws the deltas
		for (i = 0; i < 10; i++) {
			/* 
			 * Checking if the delta is valid to print.
			 * 0 is score, which is always valid, and validPrints is a bool array of whether
			 * the action at the index (organized using the team, color and actions enums) is
			 * possible, considering the cube/tower limits.
			 * 
			 * The indices for validPrints are 0 to always use your alliance, (i-1) % 3 for the color
			 * to go 012012012, and floor((i - 1) / 3) for the action to go 000111222, as diffs is 
			 * organized (happens right above this)
			 */
			if (i == 0 || validPrints[0][(i - 1) % 3][(int)(floor((i - 1) / 3))]) {
				if (diffs[i] > 0)
					sprintf(buffer, "%c%i", '+', abs(diffs[i]));
				else if (diffs[i] < 0)
					sprintf(buffer, "%c%i", '-', abs(diffs[i]));
				else
					sprintf(buffer, "0");
			} else
				sprintf(buffer, "%s", "--");

			// The ternary expressions here move the text over if the
			// delta is 0 to account for the missing +/-
			printStringCentered(buffer, 	    diffs[i] == 0 ? 136 : 135,
								 96 + (13 * i), diffs[i] == 0 ? 163 : 162,
								102 + (13 * i), FONT_HEIGHT);

			memset(buffer, 0, 10*sizeof(uint8_t));
		}
		
		/* Finding and drawing the recommendation actions:
		 * First, creates a new array called sortedDiffs that contains the deltas but the actions
		 * that are impossible because of cube/tower limits are set to -127 and it's
		 * sorted from lowest to highest point delta.  Then it goes through the top three
		 * and draws the sprite and the delta in the box unless the delta is -127 in which
		 * case there aren't 3 moves you can do, so it only fills in as many boxes as there
		 * are available moves.
		 */
		
		for (i = 0; i < 9; i++){
			 /* validPrints is a bool array containing if the action is possible, if it's not 
			  * it gets set to -127, the minimum value for int8_t. The indices validPrints are
			  * 0 to always use your alliance, i % 3 for the color to go 012012012, and 
			  * floor(i / 3) for the action to go 000111222, which corresponds with how diffs
			  * is organized.
			  */
			sortedDiffs[i + 1].delta = validPrints[0][i % 3][(int)(floor(i / 3))] ? diffs[i + 1] : -127;
			sortedDiffs[i + 1].spriteId = i + 1;
		}

		// Score delta can't be considered as a valid action
		sortedDiffs[0].delta = -127;

		recommendationSort(sortedDiffs, 10);

		// Finds and draws the recommended actions
		for (i = 0; i < 3; i++) {
			// The current delta, 
			delta = sortedDiffs[9-i].delta;
			interval = 47 * i;

			// Loading the buffer with a +/- and the delta or 
			// dashes for an invalid action
			if (delta > 0)
				sprintf(buffer, "%c%i", '+', abs(delta));
			else if (delta == 0)
				sprintf(buffer, "0");
			else {
				if (delta == -127)
					sprintf(buffer, "%s", "---");
				else
					sprintf(buffer, "%c%i", '-', abs(delta));
			}

			// Prints the current delta in the text box under the recommendation box
			printStringCentered(buffer, 177 + interval, 135, 213 + interval, 141, FONT_HEIGHT);


			memset(buffer, 0, 10 * sizeof(uint8_t)); 
			if(delta != -127) {
				switch (sortedDiffs[9-i].spriteId) {
					case 1:
						gfx_TransparentSprite_NoClip(orangeCube,  177 + interval, 94);
						break;
					case 2:
						gfx_TransparentSprite_NoClip(greenCube,   177 + interval, 94);
						break;
					case 3:
						gfx_TransparentSprite_NoClip(purpleCube,  177 + interval, 94);
						break;
					case 4:
						gfx_TransparentSprite_NoClip(towerAdd,    177 + interval, 94);
						gfx_TransparentSprite_NoClip(towerOrange, 177 + interval, 94);
						break;
					case 5:
						gfx_TransparentSprite_NoClip(towerAdd,    177 + interval, 94);
						gfx_TransparentSprite_NoClip(towerGreen,  177 + interval, 94);
						break;
					case 6:
						gfx_TransparentSprite_NoClip(towerAdd,    177 + interval, 94);
						gfx_TransparentSprite_NoClip(towerPurple, 177 + interval, 94);
						break;
					case 7:
						gfx_TransparentSprite_NoClip(towerRemove, 177 + interval, 94);
						gfx_TransparentSprite_NoClip(towerOrange, 177 + interval, 94);
						break;
					case 8:
						gfx_TransparentSprite_NoClip(towerRemove, 177 + interval, 94);
						gfx_TransparentSprite_NoClip(towerGreen,  177 + interval, 94);
						break;
					case 9:
						gfx_TransparentSprite_NoClip(towerRemove, 177 + interval, 94);
						gfx_TransparentSprite_NoClip(towerPurple, 177 + interval, 94);
						break;
					default:
						break;
				}
			}

		}
	}

	// Handles changing the auton winner, changes the text colors in the auton boxes
	// and the outline color
	if (updates[UPDATE_AUTON]) {
		gfx_SetColor(PALLETE_BLACK);//Reset outer boxes
		gfx_Rectangle_NoClip(168, 2, 14, 15);
		gfx_Rectangle_NoClip(169, 3, 12, 13);
		gfx_Rectangle_NoClip(183, 2, 14, 15);
		gfx_Rectangle_NoClip(184, 3, 12, 13);
		gfx_Rectangle_NoClip(176, 18, 14, 15);
		gfx_Rectangle_NoClip(177, 19, 12, 13);
		
		gfx_SetTextFGColor(PALLETE_BLACK);

		gfx_TransparentSprite_NoClip(autonA, 172, 6);
		gfx_TransparentSprite_NoClip(autonE, 187, 6);
		gfx_TransparentSprite_NoClip(autonT, 180, 22);

		switch (autonWinner) {
			case AUTON_TIE:
				gfx_Rectangle_NoClip(176, 18, 14, 15);
				gfx_Rectangle_NoClip(177, 19, 12, 13);
				gfx_TransparentSprite_NoClip(autonTSelected, 180, 22);
				break;
			case AUTON_WIN:
				gfx_Rectangle_NoClip(168, 2, 14, 15);
				gfx_Rectangle_NoClip(169, 3, 12, 13);
				gfx_TransparentSprite_NoClip(autonASelected, 172, 6);
				break;
			case AUTON_LOSS:
				gfx_Rectangle_NoClip(183, 2, 14, 15);
				gfx_Rectangle_NoClip(184, 3, 12, 13);
				gfx_TransparentSprite_NoClip(autonESelected, 187, 6);
				break;	
		}
	}
}


//Team, color, action
void valid(bool validPrints[2][3][3], uint8_t towers[], uint8_t allianceS[], uint8_t enemyS[]) {
	/* Fills in a bool array, validPrints, on if an action would be possible, considering if it
	 * would exceed the cube or tower limit or if it would require there being less than 0 of
	 * an item.
	 */
	uint8_t teamIter, colorIter;

	for (teamIter = 0; teamIter < 2; teamIter++) {
		for (colorIter = 0; colorIter < 3; colorIter++) {
			validPrints[teamIter][colorIter][CUBE_STACK] =
						!(allianceS[colorIter] + enemyS[colorIter] + towers[colorIter] >= 22);

			validPrints[teamIter][colorIter][TOWER_ADD] =
						!(towers[0] + towers[1] + towers[2] >= 7);

			validPrints[teamIter][colorIter][TOWER_REMOVE] =
						!(towers[colorIter] < 0);
		}
	}
}
