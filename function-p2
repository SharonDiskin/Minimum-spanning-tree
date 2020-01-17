#include "common.h"

/*This function receive the amount of computer in the computer networks.
The function makes sure the amount of computers is valid*/
void getAmountOfComputers(int *n)
{
	printf("Please enter number of computers: ");
	scanf("%d", n);
	amountValidationCheck(*n); //Validation check
}

/*This function recieve the name of the binary data file.
It is a standrt function for recieving a sring of unknown size*/
char* getFileName()
{
	char* str;
	int logSize = 0, phySize = 1;
	char c;

	str = (char*)malloc(sizeof(char)*phySize);

	printf("Please enter file name: ");

	fseek(stdin, 0, SEEK_END);
	c = getchar();

	while (c != '\n')
	{
		if (logSize == phySize)
		{
			phySize *= 2;
			str = (char*)realloc(str, sizeof(char)*phySize);
		}

		str[logSize] = c;
		logSize++;
		c = getchar();
	}

	str = (char*)realloc(str, sizeof(char)*(logSize + 1));
	str[logSize] = '\0';

	return str;
}

/*This funcation creates a new item for the list of connection each computer have*/
Item_l* createItem_l(int v, float price, Item_l* next)
{
	Item_l *node = (Item_l*)malloc(sizeof(Item_l));
	checkMalloc(node);
	node->neighbor = v;
	node->w = price;
	node->next = next;
	return node;
}

/*This funcation creates a new item. Each Item is the computer that adds to the PQ.
The PQ contains the priority of the computer*/
Item_t* createItem_t(int v, float min)
{
	Item_t *node = (Item_t*)malloc(sizeof(Item_t));
	checkMalloc(node);
	node->vertex = v;
	node->min = min;
	node->next = NULL;
	return node;
}

/*This function adds neighbors to a list of neighbors each computer has.
The function arrange the computers on the neighbors list by number */
void enterToAdjsort(Item_l **arr, int v, float price)
{
	Item_l* new_node = createItem_l(v, price, NULL);
	Item_l* node = *arr;

	if (!(*arr)) //If the list of neighbors is empty, we create the first neigbors
		*arr = new_node;
	else //We recieve new neighbors, and place same on the right order
	{
		while (node->next)
		{
			if (node->next->neighbor < new_node->neighbor)
				node = node->next;
			else
			{
				new_node->next = node->next;
				node->next = new_node;
				return;
			}
		}
		if (!node->next)
		{
			node->next = new_node;
			return;
		}
	}
}

/*This function a file name, opens the file and extracts the information about
the computers network. 
The function creates an array of all the computer in the network, 
and for each computer in the network the function creates a neighbors list*/

Item_l** getAdj(char* fname, int n)
{
	//Declaration of variables
	int a, b, eof, current;
	float price;

	//We open the binary data file that contains information about the computers network
	FILE *fp = fopen(fname, "rb");
	checkFile(fp);

	//We create the array of the computers
	Item_l **arr = (Item_l**)calloc((n + 1), sizeof(Item_l*)); 
	checkMalloc(arr);

	//We initialize current curser and the end of file 
	fseek(fp, 0, SEEK_END);
	eof = ftell(fp);
	rewind(fp);
	current = ftell(fp);

	while (current < eof) //While we didn't get to the end of the file
	{
		//We read information about the lines there are in the network
		fread(&a, sizeof(int), 1, fp); 
		fread(&b, sizeof(int), 1, fp);
		fread(&price, sizeof(float), 1, fp);
		//Validation checks
		computersValidationCheck(a, n);
		computersValidationCheck(b, n);
		priceValidationCheck(price);

		//We create neighbors lists
		enterToAdjsort(&(arr[a]), b, price);
		enterToAdjsort(&(arr[b]), a, price);
		current = ftell(fp); //We promote current
	}
	fclose(fp); //We close the file
	return arr;
}

/*This function create an array of parents*/
int* createPrim(int n)
{
	int *prim = (int*)calloc(n + 1, sizeof(int));
	checkMalloc(prim);
	prim[0] = -1; //For convenience of indexing we refer to the first index as dummy cell, and we ignore it
	return prim;
}

/*This funcation create an array of prices of each line*/
float* createMin(int n)
{
	int i;
	float *min = (float*)malloc(sizeof(float)*(n + 1));
	checkMalloc(min);

	min[0] = -1; //For convenience of indexing we refer to the first index as dummy cell, and we ignore it

	for (i = 1; i <= n; i++) //We initialize each cell to be INT_MAX
		min[i] = INT_MAX;
	return min;
}

/*This function get the amount of computers and calculate the how many cells the inT array 
reprsentd by unsigned char needs to have*/
int inTSize(int n)
{
	if (n % BYTE == 0) //If n divides by 8 (size of a byte) with no carrier than return the result of the division
		return (n / BYTE);
	else
		return (n/ BYTE) + 1; //Else add one to the result of the division
}

/*This function create an inT array*/
unsigned char *createinT(int n)
{
	int arrSize = inTSize(n);

	unsigned char *inT = (unsigned char*)calloc(arrSize, sizeof(unsigned char));
	checkMalloc(inT);

	return inT;
}

/*This function updates the inT array
It changes the values of the array from 0 to 1*/

void updateinT(int location, unsigned char* inT)
{
	location--; //We take 1 off the location beacuse the location given to us is the number of the computer, but the array starts at 0
	int shift = (location % BYTE); //The shift should be between 0 to 7, but the location might be bigger than that
	unsigned char mask = 1 << shift; //We define a mask
	int index = location / BYTE; //The index of the computer located in the location we got is the product of the division by a size of byte
	inT[index] |= mask; //We "turn on" the bit in the right locations
}

/*This function check the bit in a given location
and returns True if the bit is turned on*/
BOOL isInTree(int location, unsigned char* inT)
{
	location--; //We take 1 off the location beacuse the location given to us is the number of the computer, but the array starts at 0
	int shift = (location % BYTE); //The shift should be between 0 to 7, but the location might be bigger than that
	unsigned char mask = 1 << shift; //We define a mask
	int index = location / BYTE; //The index of the computer located in the location we got is the product of the division by a size of byte
	return inT[index] & mask; //If the bit is turned on using the operator
	                         // & on that bit with the mask we created will return True, else the function will return false
}

/*This function creates array of pointes to each computer on the PQ*/
Item_t** createLocations(PQ* pq, int n)
{
	int i = 1;
	Item_t** locations = (Item_t**)malloc(sizeof(Item_t)*(n + 1));
	checkMalloc(locations);

	locations[0] = NULL; // For convenience of indexing we refer to the first index as dummy cell, and we ignore it

	Item_t* head = pq->head;
	while (head != NULL)
	{
		locations[i++] = head;
		head = head->next;
	}
	return locations;
}

/*This function create a new list*/
void createList(PQ* pq)
{
	pq->head = NULL;
}

/*This function create a PQ list*/
void createPq(PQ* pq, int n)
{
	int i = 1;
	createList(pq); //We create a new list

	Item_t* head;
	Item_t* temp;

	temp = createItem_t(i, INT_MAX); //We create head element
	pq->head = temp;
	head = pq->head;

	for (i = 2; i <= n; i++) //We create the rest of the element
	{
		temp = createItem_t(i, INT_MAX);
		head->next = temp;
		head = head->next;
	}
}

/*This function delete from the PQ the the computer that in the top priority (the first computer) in 
the PQ list, and returns the computer's number */
int deleteMin(PQ *pq)
{
	int v = pq->head->vertex;
	pq->head = pq->head->next;
	return v;
}

/*This function removes a node from the PQ list,
the function connects the previous node of node we removed with the next one */
void removeNodeFromPq(Item_t* node, PQ* pq)
{
	Item_t* head = pq->head;

	if (head == node)
	{
		pq->head = node->next;
		return;
	}

	while (head->next != NULL)
	{
		if (head->next == node)
		{
			head->next = node->next;
			return;
		}
		head = head->next;
	}
}

/*This recieves a node and place it in the right order on the PQ list*/
void placeInPq(Item_t *node, PQ *pq)
{
	float min = node->min;
	Item_t* head = pq->head;
	if (head == NULL)
	{
		pq->head = node;
		return;
	}
	if (head->min > min)
	{
		pq->head = node;
		node->next = head;
		return;
	}
	while (head->next != NULL)
	{
		if (head->next->min > min)
		{
			node->next = head->next;
			head->next = node;
			return;
		}
		head = head->next;
	}
	//Else the list is over, the node should be placed at the end
	head->next = node;
}

/*This funcation recieve a node, the pq list and it's min value
removes the node from the PQ list
updates the min value of the node
and than place it in the new place it should be in*/
void decreaseKey(Item_t *node, PQ *pq, float min)
{
	removeNodeFromPq(node, pq);
	node->min = min;
	node->next = NULL;
	placeInPq(node, pq);
}

/*This function gets the root of the lines from the computer.
It makes sure the value the user enterd is valid*/
void getRoot(int *v, int n)
{
	printf("Please choose the root computer of the network: ");
	scanf("%d", v);
	computersValidationCheck(*v, n);
}

/*This function is the main function of question A.
This function build the Minimum spanning tree 
of the lines our client should buy (Goog)*/
void buildMinTree(int *prim, float *min, unsigned char *inT, PQ *pq, Item_l** adj, Item_t **location,int n)
{
	int v;
	
	getRoot(&v, n); //We get the input from user - where to start in the newtowrk

	//We intialize all the data of the v element (his parent, his cost..)
	prim[v] = 0;
	min[v] = 0;
	location[v]->min = 0;

	removeNodeFromPq(location[v], pq); //We remove the v from the PQ
	placeInPq(location[v], pq); //We place it back at the top of the PQ

	while (pq->head) //While the PQ didn't get to it's end
	{
		v = deleteMin(pq); //We delete the element on the top of the PQ and return it's value
		if (min[v] == INT_MAX) //This test is designed to ensure that all vertices are connected to the network. It check that the specific vertic is connected
		{
			printf("Error in the computer network\n");
			exit(ERROR);
		}
		else //Else the vertic is connected 
		{
			Item_l *head;
			head = adj[v]; //We define our head to be the top of v's neighbors list
			updateinT(v, inT); //We turn the vertic's bit on the bits array

			while (head) //While there are still neighbors
			{
				if (head->w < min[head->neighbor] && !isInTree(head->neighbor, inT)) //We check for each neighbor if 
				{
					min[head->neighbor] = head->w;
					prim[head->neighbor] = v;
					decreaseKey(location[head->neighbor], pq, min[head->neighbor]);
				}
				head = head->next;
			}
		}
	}
	printTree(prim, min, n); //We print the Minimum spanning tree we found
}

/*This function calculate the total cost of the lines goog should purchase*/
float calcTotalCost(float* min, int n)
{
	int i;
	float counter = 0;
	for (i = 1; i <= n; i++)
	{
		counter += min[i];
	}
	return counter;
}

/*This function prints the lines that goog should purcahse and their total cost*/
void printTree(int* prim, float* min, int n)
{
	int i;
	float totalPrice;
	printf("The lines which Goog should purchase are: \n");
	for (i = 1; i <= n; i++) //We print each line
	{
		if (prim[i] != 0)
		{
			printf("(%d,%d,%f)", prim[i], i, min[i]);
			printf("\n");
		}
	}
	totalPrice = calcTotalCost(min, n); //We calculate the total cost of all the lines
	printf("Total cost: %f \n", totalPrice); //We print the final result
}
