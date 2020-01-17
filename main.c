#include "common.h"

//main
int main()
{
	//Declaration of all the arrays, lists and varaibles the program uses
	int n;
	char *name;
	int *prim;
	float *min;
	unsigned char *inT;
	Item_t** locations;
	Item_l** adj;
	PQ pq;

	int first, last;
	int *parent;
	Path *PrimPath;
	COLOR *color;

	/*Part A*/

	//We get amount of computers in the computers network
	getAmountOfComputers(&n);

	//We create all the arrays and lists the program uses in part A
	name = getFileName(); 
	adj = getAdj(name, n); 
	createPq(&pq, n);
	prim = createPrim(n);
	min = createMin(n);
	inT = createinT(n);
	locations = createLocations(&pq, n);

	//We call the main funcation of Part A which build the Minimum spanning tree
	buildMinTree(prim, min, inT, &pq, adj, locations, n);

	/*Part B*/

	//We ceate all the arrays and lists the program need for part B
	PrimPath = createPrimPath(prim, n);
	color = createColor(n);
	parent = createPrim(n);

	//We get the first and last computers for the requested path
	getFirstLast(&first, &last, n);

	//We find the path the user requested
	findPath(color, PrimPath, parent, first, first, last);

	//This function calls all function that free all the memmory we allocated
	freeAll(n, name, prim, min, inT, locations, adj, PrimPath, color, parent);

	return(0);
}
