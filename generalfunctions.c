#include "common.h"

/*This function free the locations array*/
void freelocation(Item_t** locations, int n)
{
	int i;
	for (i = 1; i <= n; i++)
	{
		free(locations[i]);
	}
	free(locations);
}

/*This function free recursivly each of the adjoin lists*/
void freeAdjRec(Item_l *head)
{
	if (head == NULL)
		return;
	else
	{
		freeAdjRec(head->next);
		free(head);
	}
}

/*This funcation calls a function that free all of the adjoint lists we created*/
void freeAdj(Item_l **adj, int n)
{
	int i;
	for (i = 1; i <= n; i++)
	{
		freeAdjRec(adj[i]);
	}
	free(adj); 
}

/*This function free recursuvly each path*/
void freePathRec(Item_p *head)
{
	if (head == NULL)
		return;
	else
	{
		freePathRec(head->next);
		free(head);
	}
}

/*This function free the path array we dynamiclly allocated*/
void freePath(Path *arr, int n)
{
	int i;
	for (i = 1; i <= n; i++)
	{
		freePathRec(arr[i].head); //For each path we call a function that free the path recursivly
	}
	free(arr);
}

/*This function is the main free function of our program.
The function calls each of the free function that incharge of free the memmory we allocated*/
void freeAll(int n, char *name, int *prim, float *min, unsigned char *inT, 
	Item_t **locations, Item_l **adj, Path *PrimPath, COLOR *color, int *parent)
{
	free(name); 
	free(prim); 
	free(min);
	free(inT);
	freelocation(locations, n);
	freeAdj(adj, n);
	freePath(PrimPath, n);
	free(color);
	free(parent);
}


/*This function makes sure that each price we recieve is valid (hence, its a positive price)*/
void priceValidationCheck(float price)
{
	if (price <= 0)
	{
		printf("The price has to be a positive number\n");
		exit(ERROR);
	}
}

/*This function checks that the amount of computers the user enterd make sense logically.
There have to be a least 2 computer in order to have 1 communication line*/
void amountValidationCheck(int n)
{
	if (n <= 1)
	{
		printf("Computers network must contain at least 2 computers\n");
		exit(ERROR);
	}
}

/*This function validates that each of the computer entered as input are within the 
the numbers 1 to n (hence, they appear in the computer newtork)*/
void computersValidationCheck(int compNum, int n)
{
	if (compNum<1 || compNum > n)
	{
		printf("One of the computers you enterd does not appear on the computers network\n");
		exit(ERROR);
	}
}


/*This function validates that the memmory allocation was succsessful*/
void checkMalloc(void* p)
{
	if (!p)
	{
		printf("Memmory allocation error!");
		exit(ERROR);
	}
}

/*This function validate that the file open was succsessful*/
void checkFile(void* p)
{
	if (!p)
	{
		printf("File error!");
		exit(ERROR);
	}
}
