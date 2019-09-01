#ifndef H_UTILS
#define H_UTILS

#include "main.h"
#include "graphx.h"

void swap(int8_t *xp, int8_t *yp);
void selectionSort(int8_t arr[], uint8_t n);
int compare(void * a, void * b);
int8_t indexOf(int8_t arr[], int8_t val, uint8_t indices);
void debugPrintPalette(void);

#endif