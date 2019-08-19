#include "utils.h"

void swap(int8_t *xp, int8_t *yp) { 
    int8_t temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 

void selectionSort(int8_t arr[], uint8_t n) { 
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

int8_t indexOf(int8_t arr[], int8_t val, uint8_t indices) {
	uint8_t i;
	for (i = 0; i < indices; i++)
		if (arr[i] == val) {
			return i;
		}
	return -1;
}

int compare (void * a, void * b) {
    return (*(int *)a - *(int *)b);
}