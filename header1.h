#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct item_l
{
	int neighbor;
	float w;
	struct item_l *next;
} Item_l;

typedef struct item_t
{
	int vertex;
	float min;
	struct item_t *next;
} Item_t;

typedef struct pq
{
	Item_t *head;
}PQ;

//Define bool type
typedef int BOOL;
#define TRUE 1
#define FALSE 1

//Defining the size of a BYTE
#define BYTE 8

/*Function declaration*/

void getAmountOfComputers(int *n);
char* getFileName();

void createList(PQ* pq);
Item_l* createItem_l(int v, float price, Item_l* next);
Item_t* createItem_t(int v, float min);

int* createPrim(int n);
float* createMin(int n);
int inTSize(int n);
unsigned char *createinT(int n);

Item_t** createLocations(PQ* pq, int n);
void createPq(PQ* pq, int n);

void updateinT(int location, unsigned char* inT);
BOOL isInTree(int location, unsigned char* inT);
void enterToAdjsort(Item_l **arr, int v, float price);
Item_l** getAdj(char* fname, int n);


int deleteMin(PQ *pq);
void removeNodeFromPq(Item_t* node, PQ* pq);
void decreaseKey(Item_t *node, PQ *pq, float min);
void getRoot(int *v, int n);
void buildMinTree(int *prim, float *min, unsigned char *inT, PQ *pq, Item_l** adj, Item_t **location, int n);


float calcTotalCost(float* min, int n);
void printTree(int* prim, float* min, int n);

