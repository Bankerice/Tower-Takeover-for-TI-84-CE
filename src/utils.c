#include "utils.h"

void swap(int8_t *xp, int8_t *yp) { 
    int8_t temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 

void selectionSort(int8_t arr[], uint8_t n) {
    uint8_t i, j, min_idx;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < n-1; i++) {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < n; j++)
          if (arr[j] < arr[min_idx])
            min_idx = j;

         // Swap the found minimum element with the first element
        swap(&arr[min_idx], &arr[i]);
    }
}

int8_t indexOf(int8_t arr[], int8_t val, uint8_t indices) {
	uint8_t i;
	for (i = 0; i < sizeof(arr) / sizeof(int8_t); i++)
		if (arr[i] == val)
			return i;
	return -1;
}

int compare (void * a, void * b) {
    return (*(int *)a - *(int *)b);
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