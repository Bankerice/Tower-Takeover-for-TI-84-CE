/*
* --------------------------------------
* Program Name : Tower Takeover Calculator for TI - 84 CE
* Author : Thomas Ji
* License : N / A
* Description : Takes input from the user, showing the best possible movesand the results of all possible actions in Tower Takeover, by Vex.
* --------------------------------------
*/

#include "graphics.h"

#define FONT_HEIGHT 8

int8_t indexOf(int8_t arr[], int8_t val, uint8_t indices) {
	uint8_t i;
	for (i = 0; i < indices; i++)
		if (arr[i] == val) {
			//arr[i] = -127;
			return i;
		}
	return -1;	
}

void swap(int8_t *xp, int8_t *yp) 
{ 
    int8_t temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
  
void selectionSort(int8_t arr[], uint8_t n) 
{ 
    uint8_t i, j, min_idx; 
  
    // One by one move boundary of unsorted subarray 
    for (i = 0; i < n-1; i++) 
    { 
        // Find the minimum element in unsorted array 
        min_idx = i; 
        for (j = i+1; j < n; j++) 
          if (arr[j] < arr[min_idx]) 
            min_idx = j; 
  
        // Swap the found minimum element with the first element 
        swap(&arr[min_idx], &arr[i]); 
    } 
} 

void initGUI(void) {
	uint8_t i = 0;
	uint8_t j = 0;


 gfx_SetTransparentColor(WHITE);


	/* Initialize the 8bpp graphics */;
	gfx_SetPalette(symbols_gfx_pal, sizeof_symbols_gfx_pal, 0);

	//Fill the screen white
	gfx_FillScreen(WHITE);

	//DRAWINGS: Creates the box surrounding everything
	gfx_SetColor(BLACK);//Black
	gfx_Rectangle_NoClip(0, 0, 165, 224);
	gfx_Rectangle_NoClip(1, 1, 163, 222);
	for (i = 0; i < 16; i++) //Makes all horizontal lines
		switch (i)
		{
		case 0: case 3: case 6: case 7: case 10: case 13:
			gfx_HorizLine_NoClip(2, 14 + i * (13), 161);
			gfx_HorizLine_NoClip(2, 15 + i * (13), 161);
			break;
		default:
			gfx_HorizLine_NoClip(41, 14 + i * (13), 122);
			gfx_HorizLine_NoClip(41, 15 + i * (13), 122);
			break;
		}


	gfx_VertLine_NoClip(39, 2, 220);
	gfx_VertLine_NoClip(40, 2, 220);
	gfx_VertLine_NoClip(86, 2, 51);
	gfx_VertLine_NoClip(87, 2, 51);
	gfx_VertLine_NoClip(86, 94, 128);
	gfx_VertLine_NoClip(87, 94, 128);
	gfx_VertLine_NoClip(133, 2, 220);
	gfx_VertLine_NoClip(134, 2, 220);

	//Colored Text Boxes
	//Top boxes, team and delta box
	gfx_TransparentSprite_NoClip(neutralTeamBox, 41, 2);
	gfx_TransparentSprite_NoClip(neutralTeamBox, 88, 2);
	spriteCentered(deltaTextBox, 135, 2, 162, 13, deltaTextBox_width, deltaTextBox_height);
	//First 6 normal orange/green/purple boxes
	gfx_TransparentSprite_NoClip(orangeTextBox, 41, 16);
	gfx_TransparentSprite_NoClip(orangeTextBox, 88, 16);
	gfx_TransparentSprite_NoClip(greenTextBox, 41, 29);
	gfx_TransparentSprite_NoClip(greenTextBox, 88, 29);
	gfx_TransparentSprite_NoClip(purpleTextBox, 41, 42);
	gfx_TransparentSprite_NoClip(purpleTextBox, 88, 42);
	//The three long orange/green/purple boxes
	gfx_TransparentSprite_NoClip(orangeTextBoxLong, 41, 55);
	gfx_TransparentSprite_NoClip(greenTextBoxLong, 41, 68);
	gfx_TransparentSprite_NoClip(purpleTextBoxLong, 41, 81);
	//The red text boxes, along with the other 27 orange/green/purple boxes
	for (i = 0; i < 10; i++)
		switch (i)
		{
		case 1: case 4: case 7:
			gfx_TransparentSprite_NoClip(orangeTextBox, 41, 94 + i * 13);
			gfx_TransparentSprite_NoClip(orangeTextBox, 88, 94 + i * 13);
			gfx_TransparentSprite_NoClip(shortOrangeTextBox, 135, 94 + i * 13);
			break;
		case 2: case 5: case 8:
			gfx_TransparentSprite_NoClip(greenTextBox, 41, 94 + i * 13);
			gfx_TransparentSprite_NoClip(greenTextBox, 88, 94 + i * 13);
			gfx_TransparentSprite_NoClip(shortGreenTextBox, 135, 94 + i * 13);
			break;
		case 3: case 6: case 9:
			gfx_TransparentSprite_NoClip(purpleTextBox, 41, 94 + i * 13);
			gfx_TransparentSprite_NoClip(purpleTextBox, 88, 94 + i * 13);
			gfx_TransparentSprite_NoClip(shortPurpleTextBox, 135, 94 + i * 13);
			break;
		default:
			gfx_TransparentSprite_NoClip(redTextBox, 41, 94);
			gfx_TransparentSprite_NoClip(redTextBox, 88, 94);
			gfx_TransparentSprite_NoClip(shortRedTextBox, 135, 94);
			break;
		}
	
	//Gray box
	gfx_SetColor(gray);
	gfx_FillRectangle_NoClip(135, 16, 28, 76);

	//Black text, along with some of the sprited texts
	gfx_SetTextFGColor(BLACK);
	printStringCentered("SCO", 2, 94, 38, 104, gfx_GetStringWidth("SCO"), FONT_HEIGHT);
	printStringCentered("Team", 2, 2, 38, 13, gfx_GetStringWidth("Team"), FONT_HEIGHT);
	printStringCentered("Ally", 41, 2, 85, 13, gfx_GetStringWidth("Ally"), FONT_HEIGHT);
	printStringCentered("Enemy", 88, 2, 132, 13, gfx_GetStringWidth("Enemy"), FONT_HEIGHT);
	gfx_TransparentSprite_NoClip(deltaXText, 141, 4);
	for (i = 0; i < 2; i++)
		for (j = 0; j < 10; j++)
			printStringCentered("000", 41 + 47 * i, 94 + 13 * j, 85 + 47 * i, 104 + 13 * j, gfx_GetStringWidth("000"), FONT_HEIGHT);

	for (i = 0; i < 2; i++)
		for (j = 0; j < 3; j++)
			printStringCentered("00", 41 + 47 * i, 16 + 13 * j, 85 + 47 * i, 26 + 13 * j, gfx_GetStringWidth("00"), FONT_HEIGHT);

	for (i = 0; i < 3; i++)
		printStringCentered("0", 41, 55 + 13 * i, 132, 65 + 13 * i, gfx_GetStringWidth("0"), FONT_HEIGHT);

	for (i = 0; i < 10; i++)
		spriteCentered(plusMinusZero, 135, 94 + i * 13, 162, 104 + i * 13, plusMinusZero_width, plusMinusZero_height);

	//Side symbols
	gfx_TransparentSprite_NoClip(genericCube, 2, 16);
	gfx_TransparentSprite_NoClip(emptyTower, 2, 55);
	gfx_TransparentSprite_NoClip(stackedCube, 2, 107);
	gfx_TransparentSprite_NoClip(towerAdd, 2, 146);
	gfx_TransparentSprite_NoClip(towerRemove, 2, 185);

	//Bottom panels
	for (i = 0; i < 5; i++)
		gfx_TransparentSprite_NoClip(bottomPanel, 64 * i, 224);
	gfx_TransparentSprite_NoClip(genericTeamColor, 12, 227);
	printStringCentered("Reset", 194, 226, 253, 237, gfx_GetStringWidth("Reset"), FONT_HEIGHT);
	gfx_PrintStringXY("Quit", 275, 228); //This really should be "printStringCentered" but for some reason this had some issues

	//Auton Boxes
	gfx_SetColor(BLACK);//Black
	gfx_Rectangle_NoClip(168, 2, 14, 15);
	gfx_Rectangle_NoClip(169, 3, 12, 13);
	gfx_TransparentSprite_NoClip(genericAuton, 170, 4);
	gfx_TransparentSprite_NoClip(autonA, 172, 6);
	gfx_Rectangle_NoClip(183, 2, 14, 15);
	gfx_Rectangle_NoClip(184, 3, 12, 13);
	gfx_TransparentSprite_NoClip(genericAuton, 185, 4);
	gfx_TransparentSprite_NoClip(autonE, 187, 6);
	gfx_Rectangle_NoClip(176, 18, 14, 15);
	gfx_Rectangle_NoClip(177, 19, 12, 13);
	gfx_TransparentSprite_NoClip(greenAuton, 178, 20);
	gfx_TransparentSprite_NoClip(autonT, 180, 22);


	for (i = 0; i < 3; i++)
	{
		gfx_Rectangle_NoClip(175 + 47 * i, 92, 41, 54);
		gfx_Rectangle_NoClip(176 + 47 * i, 93, 39, 52);
		gfx_HorizLine_NoClip(177 + 47 * i, 131, 37);
		gfx_HorizLine_NoClip(177 + 47 * i, 132, 37);
		gfx_TransparentSprite_NoClip(recommendationScore, 177 + 47 * i, 133);
		gfx_TransparentSprite_NoClip(plusMinusZero, 184 + 47 * i, 135);//This really should be "printStringCentered" but for some reason this had some issues
	}
	gfx_SetColor(gold);     gfx_FillRectangle_NoClip(177, 94, 37, 37);
	gfx_SetColor(silver);   gfx_FillRectangle_NoClip(224, 94, 37, 37);
	gfx_SetColor(bronze);   gfx_FillRectangle_NoClip(271, 94, 37, 37);
}


void printStringCentered(const char* str, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t stringWidth, uint16_t stringHeight) {
	gfx_PrintStringXY(str, x1 + ((2 + x2 - x1) - stringWidth) / 2, y1 + ((2 + y2 - y1) - stringHeight) / 2);
}


void spriteCentered(gfx_sprite_t* sprite, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t spriteWidth, uint16_t spriteHeight) {
	gfx_TransparentSprite_NoClip(sprite, x1 + ((2 + x2 - x1) - spriteWidth) / 2, y1 + ((2 + y2 - y1) - spriteHeight) / 2);
}


void debugPrintPalette(void) {
	uint8_t i;
	uint8_t j;
	for (i = 0; i < 8; i++)
		for (j = 0; j < 32; j++)
		{
			gfx_SetColor(i * 32 + j);
			gfx_SetPixel(5 + j, 5 + i);
		}
}

void draw(auton *autonWinner, teamColor *col, uint8_t towers[], uint8_t allianceS[], uint8_t enemyS[], uint8_t future[2][3][3], uint8_t allianceScore, uint8_t enemyScore, bool updates[]) {
	uint8_t i, j, k;
	bool validPrints[2][3][3];
	int8_t futureDeltas[9];
	int8_t diffs[10];
	int8_t sortedDiffs[10];
	uint16_t x;

	char buffer[10];
	char emptyBuffer[10];

	//kinda lazy on these, whatever
	uint8_t empty3Array[3];
	uint8_t empty233Array[2][3][3];

	//Note: These have to be if and not else/if statements in order to function
	if (updates[UPDATE_TEAM_COLORS]){
		if (*col == TEAM_COLOR_BLUE)
		{
			gfx_TransparentSprite_NoClip(blueTeamTextBox, 41, 2);
			gfx_TransparentSprite_NoClip(redTeamTextBox, 88, 2);
			gfx_TransparentSprite_NoClip(blueAuton, 170, 4);
			gfx_TransparentSprite_NoClip(redAuton, 185, 4);
			gfx_SetColor(BLUE);
		}
		else {
			gfx_TransparentSprite_NoClip(redTeamTextBox, 41, 2);
			gfx_TransparentSprite_NoClip(blueTeamTextBox, 88, 2);
			gfx_TransparentSprite_NoClip(redAuton, 170, 4);
			gfx_TransparentSprite_NoClip(blueAuton, 185, 4);
			gfx_SetColor(RED);
		}
		printStringCentered("Ally", 41, 2, 85, 13, gfx_GetStringWidth("Ally"), FONT_HEIGHT);
		printStringCentered("Enemy", 88, 2, 132, 13, gfx_GetStringWidth("Enemy"), FONT_HEIGHT);
		gfx_FillRectangle_NoClip(15, 230, 34, 4);

		//TODO: Technically, this is inefficient because this is repeated in update auton, but doesn't work without this
		gfx_TransparentSprite_NoClip(autonA, 172, 6);
		gfx_TransparentSprite_NoClip(autonE, 187, 6);
	} 
	if (updates[UPDATE_RESET_BUTTON]) { //toUpdate, allianceScore, and enemyScore will reset on their own
		*autonWinner = AUTON_TIE;
		*col = TEAM_COLOR_RED;

		memcpy(towers, empty3Array, 3 * sizeof(uint8_t));
		memcpy(allianceS, empty3Array, 3 * sizeof(uint8_t));
		memcpy(enemyS, empty3Array, 3 * sizeof(uint8_t));
		memcpy(future, empty233Array, 12 * sizeof(uint8_t));

		initGUI();
	} 
	if (updates[UPDATE_CALCULATIONS]) {
		valid(validPrints, towers, allianceS, enemyS);
		//First 6 normal orange/green/purple boxes
		gfx_TransparentSprite_NoClip(orangeTextBox, 41, 16);
		gfx_TransparentSprite_NoClip(orangeTextBox, 88, 16);
		gfx_TransparentSprite_NoClip(greenTextBox, 41, 29);
		gfx_TransparentSprite_NoClip(greenTextBox, 88, 29);
		gfx_TransparentSprite_NoClip(purpleTextBox, 41, 42);
		gfx_TransparentSprite_NoClip(purpleTextBox, 88, 42);

		//Wide boxes
		gfx_TransparentSprite_NoClip(orangeTextBoxLong, 41, 55);
		gfx_TransparentSprite_NoClip(greenTextBoxLong, 41, 68);
		gfx_TransparentSprite_NoClip(purpleTextBoxLong, 41, 81);

		//The red text boxes, along with the other 27 orange/green/purple boxes
		for (i = 0; i < 10; i++)
			switch (i)
			{
			case 1: case 4: case 7:
				gfx_TransparentSprite_NoClip(orangeTextBox, 41, 94 + i * 13);
				gfx_TransparentSprite_NoClip(orangeTextBox, 88, 94 + i * 13);
				gfx_TransparentSprite_NoClip(shortOrangeTextBox, 135, 94 + i * 13);
				break;
			case 2: case 5: case 8:
				gfx_TransparentSprite_NoClip(greenTextBox, 41, 94 + i * 13);
				gfx_TransparentSprite_NoClip(greenTextBox, 88, 94 + i * 13);
				gfx_TransparentSprite_NoClip(shortGreenTextBox, 135, 94 + i * 13);
				break;
			case 3: case 6: case 9:
				gfx_TransparentSprite_NoClip(purpleTextBox, 41, 94 + i * 13);
				gfx_TransparentSprite_NoClip(purpleTextBox, 88, 94 + i * 13);
				gfx_TransparentSprite_NoClip(shortPurpleTextBox, 135, 94 + i * 13);
				break;
			default:
				gfx_TransparentSprite_NoClip(redTextBox, 41, 94);
				gfx_TransparentSprite_NoClip(redTextBox, 88, 94);
				gfx_TransparentSprite_NoClip(shortRedTextBox, 135, 94);
				break;
			}
			for (i = 0; i < 3; i++)
				gfx_TransparentSprite_NoClip(recommendationScore, 177 + 47 * i, 133);
	
			//Top 6 button texts
			for (i = 0; i < 3; i++) {
				sprintf(buffer, "%u", allianceS[i]);
				printStringCentered(buffer, 41, 16 + 13 * i, 85, 26 + 13 * i, gfx_GetStringWidth(buffer), FONT_HEIGHT); 
				memcpy(buffer, emptyBuffer, 10*sizeof(uint8_t));
			}

			for (i = 0; i < 3; i++) {
				sprintf(buffer, "%u", enemyS[i]);
				printStringCentered(buffer, 88, 16 + 13 * i, 132, 26 + 13 * i, gfx_GetStringWidth(buffer), FONT_HEIGHT); 
				memcpy(buffer, emptyBuffer, 10*sizeof(uint8_t));
			}

			//Wide button texts
			for (i = 0; i < 3; i++) {
				sprintf(buffer, "%u", towers[i]);
				printStringCentered(buffer, 41, 55 + 13 * i, 132, 65 + 13 * i, gfx_GetStringWidth(buffer), FONT_HEIGHT); 
				memcpy(buffer, emptyBuffer, 10*sizeof(uint8_t));
			}

			//Current Score texts
			sprintf(buffer, "%u", allianceScore);
			printStringCentered(buffer, 41, 94, 41 + redTextBox_width, 94 + redTextBox_height, gfx_GetStringWidth(buffer), FONT_HEIGHT); 
			memcpy(buffer, emptyBuffer, 10*sizeof(uint8_t));
			sprintf(buffer, "%u", enemyScore);
			printStringCentered(buffer, 88, 94, 88 + redTextBox_width, 94 + redTextBox_height, gfx_GetStringWidth(buffer), FONT_HEIGHT); 
			memcpy(buffer, emptyBuffer, 10*sizeof(uint8_t));

			gfx_SetColor(gold);     gfx_FillRectangle_NoClip(177, 94, 37, 37);
			gfx_SetColor(silver);   gfx_FillRectangle_NoClip(224, 94, 37, 37);
			gfx_SetColor(bronze);   gfx_FillRectangle_NoClip(271, 94, 37, 37);

		for (i = 0; i < 2; i++) //team
			for (j = 0; j < 3; j++) //color
				for(k = 0; k < 3; k++) { //action
				sprintf(buffer, "%u", future[i][j][k]);
				printStringCentered(validPrints[i][j][k] ? buffer : "---", 41+47*i, 107 + 13*(k*3 + j), 41 + 47*i + redTextBox_width, 107 + 13*(k*3 + j) + redTextBox_height, validPrints[i][j][k] ? gfx_GetStringWidth(buffer) : gfx_GetStringWidth("---"), FONT_HEIGHT);
				memcpy(buffer, emptyBuffer, 10*sizeof(uint8_t));
				}

		diffs[0] = ((int8_t)allianceScore)-((int8_t)enemyScore);
		for (j = 0; j < 3; j++) //color
			for(k = 0; k < 3; k++) //action
				diffs[1+k+j*3] = ((int8_t)future[TEAM_ALLIANCE-1][k][j]) - ((int8_t)future[TEAM_ENEMY-1][k][j]) - diffs[0]; //what?

		






		for (i = 0; i < 10; i++) {
			if(i == 0 || validPrints[0][(i-1)%3][(i-1)/3]) {
				if (diffs[i] > 0)
				{
					sprintf(buffer, "%c%i", '+', abs(diffs[i]));
				} else if (diffs[i] < 0) {
					sprintf(buffer, "%c%i", '-', abs(diffs[i]));
				} else {
					sprintf(buffer, "%c", '0');
				}
				
			} else {
				sprintf(buffer, "%s", "--");
			}
			printStringCentered(buffer, 135+(diffs[i]==0), 96+13*i, 162+(diffs[i]==0), 102+13*i, gfx_GetStringWidth(buffer), FONT_HEIGHT); //manual adjustment for 0
			memcpy(buffer, emptyBuffer, 10*sizeof(uint8_t));
		} 





		for (i = 0; i < 9; i++)
		{
			diffs[i+1] = validPrints[0][i%3][i/3]  ? diffs[i+1] : -127;
		}

		diffs[0] = -127;

		memcpy(sortedDiffs, diffs, 10*sizeof(int8_t));

		selectionSort(sortedDiffs, 10);

		for (i = 0; i < 3; i++)
		{
			j = sortedDiffs[9-i];
			x = 47*i;


			if (j > 0)
				{
					sprintf(buffer, "%c%i", '+', abs(j));
				} else if (j == 0) {
					sprintf(buffer, "%c", '0');
				} else {
					if(j == -127) {
						sprintf(buffer, "%s", "---");
					} else
					{
					sprintf(buffer, "%c%i", '-', abs(j));
					}
				}
			printStringCentered(buffer, 177+x, 135, 213+x, 141, gfx_GetStringWidth(buffer), FONT_HEIGHT);
			memcpy(buffer, emptyBuffer, 10*sizeof(uint8_t)); 
			

/*
		for (i = 0; i < 3; i++)
		{
			for (j = 0; j < 3; j++)
			{
				sprintf(buffer, "%i%c", diffs[i+j*3+1], ' ');
			}
			gfx_PrintStringXY(buffer, 220, 50*10+i);
			memcpy(buffer, emptyBuffer, sizeof(int8_t));


			for (j = 0; j < 3; j++) {
				sprintf(buffer, "%i%c", sortedDiffs[i+j*3+1], ' ');
			}
				gfx_PrintStringXY(buffer, 220, 150+10*i);
				memcpy(buffer, emptyBuffer, sizeof(int8_t));


		}
		
*/







			if(j != -127) {
				k = indexOf(diffs, j, 10);
				switch (k)
				{
				case 1:
					gfx_TransparentSprite_NoClip(orangeCube, 177+x, 94);
					break;
				case 2:
					gfx_TransparentSprite_NoClip(greenCube, 177+x, 94);
					break;
				case 3:
					gfx_TransparentSprite_NoClip(purpleCube, 177+x, 94);
					break;
				case 4:
					gfx_TransparentSprite_NoClip(towerAdd, 177+x, 94);
					gfx_TransparentSprite_NoClip(towerOrange, 177+x, 94);
					break;
				case 5:
					gfx_TransparentSprite_NoClip(towerAdd, 177+x, 94);
					gfx_TransparentSprite_NoClip(towerGreen, 177+x, 94);
					break;
				case 6:
					gfx_TransparentSprite_NoClip(towerAdd, 177+x, 94);
					gfx_TransparentSprite_NoClip(towerPurple, 177+x, 94);
					break;
				case 7:
					gfx_TransparentSprite_NoClip(towerRemove, 177+x, 94);
					gfx_TransparentSprite_NoClip(towerOrange, 177+x, 94);
					break;
				case 8:
					gfx_TransparentSprite_NoClip(towerRemove, 177+x, 94);
					gfx_TransparentSprite_NoClip(towerGreen, 177+x, 94);
					break;
				case 9:
					gfx_TransparentSprite_NoClip(towerRemove, 177+x, 94);
					gfx_TransparentSprite_NoClip(towerPurple, 177+x, 94);
					break;
				case -1:
					gfx_PrintStringXY("DEBUG",200,220);
					break;
				default: 
					sprintf(buffer, "%i", k);
					gfx_PrintStringXY(buffer,200,200);
					memcpy(buffer, emptyBuffer, sizeof(uint8_t) * 10);
					break;
				}
			}

		
		}
		
	}
	if (updates[UPDATE_AUTON]) {
		gfx_SetColor(BLACK);//Reset outer boxes
		gfx_Rectangle_NoClip(168, 2, 14, 15);
		gfx_Rectangle_NoClip(169, 3, 12, 13);
		gfx_Rectangle_NoClip(183, 2, 14, 15);
		gfx_Rectangle_NoClip(184, 3, 12, 13);
		gfx_Rectangle_NoClip(176, 18, 14, 15);
		gfx_Rectangle_NoClip(177, 19, 12, 13);
		
		gfx_SetTextFGColor(BLACK);

		gfx_TransparentSprite_NoClip(autonA, 172, 6);
		gfx_TransparentSprite_NoClip(autonE, 187, 6);
		gfx_TransparentSprite_NoClip(autonT, 180, 22);

		switch (*autonWinner)
		{
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
	uint8_t i;
	uint8_t j;
	uint8_t k;

	for (i = 0; i < 2; i++)
		for (j = 0; j < 3; j++)
		{
			validPrints[i][j][CUBE_STACK] = !(allianceS[j]+enemyS[j] == 22);
			validPrints[i][j][TOWER_ADD] = !(towers[0] + towers[1] + towers[2] == 7);
			validPrints[i][j][TOWER_REMOVE] = !(towers[j] == 0);
		}
} 