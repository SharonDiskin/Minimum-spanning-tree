#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct item_p
{
	int vertex;
	struct item_p *next;
} Item_p;

typedef struct path
{
	Item_p *head;
}Path;

//Define color type
typedef int COLOR;
#define BLACK 2
#define GRAY 1
#define WHITE 0

void getFirstLast(int *first, int *last, int n);
Path* createPrimPath(int *prim, int n);
void enterToPrimPath(Path *lst, int v);
Item_p* createItem_p(int data, Item_p *next);
COLOR* createColor(int n);
void findPath(COLOR *color, Path *primPath, int *parent, int first, int temp_first, int last);
void printPath(int *parent, int first, int last);
