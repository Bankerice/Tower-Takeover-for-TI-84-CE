#ifndef H_UTILS
#define H_UTILS

#include "main.h"
#include "graphx.h"

void swap(struct recommendation_t  * xp, struct recommendation_t  * yp);
void recommendationSort(struct recommendation_t arr[], uint8_t n);
int compare(void * a, void * b);
int8_t indexOf(int8_t arr[], int8_t val, uint8_t indices);
void debugPrintPalette(void);

#endif