#pragma once

#include "question1.h"
#include "question2.h"

#define ERROR -1

void freeAdj(Item_l **adj, int n);
void freeAdjRec(Item_l *head);
void freelocation(Item_t** locations, int n);
void freePath(Path *arr, int n);
void freePathRec(Item_p *head);
void freeAll(int n, char *name, int *prim, float *min, unsigned char *inT,
	Item_t **locations, Item_l **adj, Path *PrimPath, COLOR *color, int *parent);


void priceValidationCheck(float price);
void amountValidationCheck(int n);
void computersValidationCheck(int compNum, int n);
void checkMalloc(void* p);
void checkFile(void* p);
