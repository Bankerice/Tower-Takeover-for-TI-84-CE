#include "utils.h"

void swap(struct recommendation_t  * xp, struct recommendation_t  * yp) { 
    struct recommendation_t  temp = *xp; 
    *xp = *yp; 
    *yp = temp;
}

void recommendationSort(RECCOMENDATIONS arr[], uint8_t n) {
    uint8_t i, j, min_idx;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < n-1; i++) {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < n; j++)
          if (arr[j].delta < arr[min_idx].delta)
            min_idx = j;

         // Swap the found minimum element with the first element
        swap(&arr[min_idx], &arr[i]);
    }
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

uint8_t getInputNumber(void) {
		 if (kb_Data[4] & kb_2)	return 2;
	else if (kb_Data[5] & kb_3)	return 3;
	else if (kb_Data[3] & kb_4)	return 4;
	else if (kb_Data[4] & kb_5)	return 5;
	else if (kb_Data[5] & kb_6)	return 6;
	else if (kb_Data[3] & kb_7)	return 7;
	else if (kb_Data[4] & kb_8)	return 8;
	else if (kb_Data[5] & kb_9)	return 9;
    return 1;
}