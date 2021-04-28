//Liram Golibroda 316117423
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#pragma warning(disable : 4996)

/*          STRUCTS            */
typedef struct Three {
	int value;
	int i;
	int j;

}Three;

typedef struct List {
	Three item;
	struct List* next;

}List;

typedef struct Num {
	int value;
	struct Num* next;

}Num;

/*                                       */
unsigned int* powerArray(int n);
void Ex1();

/*                                      */
int** matrixMaxNeighbor(int** mat);
void neighborMaxMin(int** mat, int i, int j, int rows, int cols, int* max, int* min);
void Ex2();

/*                                      */
int createArrayAndList(Three** arr, List** head, int** mat, int rows, int cols);
Three createThree(int value, int i, int j);
List* createThreeList(Three* arr, int n);
Three* createThreeArr(int** mat, int rows, int cols, int* counter);
void freemat(int** mat, int rows);
void Ex3();

/*                                      */
void Delete(Num** head, Num* value);
void Insert(Num** head, Num to_insert);
Num* CreateList(Num** head, int flag);
void freelist(Num** list);
void PrintList(Num** list, int flag);
void Ex4();

/*                                      */
void createList2(Num** headLocation, Num** headDestenation, Num* value);
void Ex5();

/*                                      */
void Ex6();
void removeDupArrayLists(Num*** ArrList);

/*                                      */
Num* disassemblyList(Num** head, Num** SmallHead, Num** CapitalHead, Num** NumHead);
void Ex7();
void CreateNewList(Num** head, int flag);

int main()
{
	int select = 0, i, all_Ex_in_loop = 0;
	printf("Run menu once or cyclically?\n(Once - enter 0, cyclically - enter other number) ");
	if (scanf("%d", &all_Ex_in_loop) == 1)
		do
		{
			for (i = 1; i <= 7; i++)
				printf("Ex%d--->%d\n", i, i);
			printf("EXIT-->0\n");
			do {
				select = 0;
				printf("please select 0-7 : ");
				scanf("%d", &select);
			} while ((select < 0) || (select > 7));
			switch (select)
			{
			case 1: Ex1(); break;
			case 2: Ex2(); break;
			case 3: Ex3(); break;
			case 4: Ex4(); break;
			case 5: Ex5(); break;
			case 6: Ex6(); break;
			case 7: Ex7(); break;
			}
		} while (all_Ex_in_loop && select);
		return 0;
}
/*                                      */
unsigned int* powerArray(int n)
{
	unsigned int* arr= (unsigned int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++)
	{
		arr[i] = (unsigned int)pow(2, i % 32);
	}
	unsigned int* p = arr;
	return p;
}
void Ex1()
{
	unsigned int* p;
	int n;
	printf("enter number:");
	scanf_s("%d", &n);
	p = powerArray(n);
	system("cls");
	printf("answer for qustion number 1: \n");
	for (int i = 0; i < n; i++)
	{
		printf("|  %u  ", p[i]);
	}
	printf("|\n");
	free(p);
}
/*                                      */
int** matrixMaxNeighbor(int** mat,int rows,int cols)
{
	int** matb = (int**)malloc(rows * sizeof(int));// creating the second matrix
	assert(matb);
	for (int i = 0; i < rows; i++)
	{
		matb[i] = (int*)malloc(cols* sizeof(int));
		assert(matb[i]);
	}
	int max,  min;
	for(int i=0;i<rows;i++)//checking the neighbors
		for (int j = 0; j < cols; j++)
		{
			neighborMaxMin(mat, i, j, rows, cols, &max, &min);
			matb[i][j] = max;
		}
	return matb;
}
void neighborMaxMin(int** mat, int i, int j,int rows,int cols,int* max,int* min)
{
	if (rows == 1)
	{
		if (j == 0)
		{
			*max = *min = mat[i][j+1];
			return;
		}	
		if (j == rows - 1)
		{
			*max = *min = mat[i][j - 1];
			return;
		}
		*max = *min = mat[i][j-1];
		if (mat[i][j+1] > * max)
			*max = mat[i][j+1];
		else *min = mat[i][j+1];
		return;
	}
	//top of the matrix
	if (i == 0)
	{
		if (j == 0)   //checking if the top left side
		{
			*max = mat[i][j + 1];
			*min = mat[i][j + 1];
			goto nexttop;
		}
		else
			if (j == cols - 1)// checking if the top right side
			{
				*max = mat[i][j - 1];
				*min = mat[i][j - 1];
				goto nexttop;
			}
		*max = mat[i][j - 1];
		*min = mat[i][j - 1];
		if (mat[i][j + 1] > * max)
			*max = mat[i][j + 1];
		else
			if (*min > mat[i][j+1])
				*min = mat[i][j+1];
	nexttop:
		if (mat[i + 1][j] > * max)
			*max = mat[i + 1][j];
		else
			if (*min > mat[i + 1][j])
				*min = mat[i + 1][j];
		return;
	}
	else //bottom of the matrix
		if (i == rows - 1)
		{
			if (j == 0)   //checking if the bottom left side
			{
				*max = mat[i][j + 1];
				*min = mat[i][j + 1];
				goto nextbot;
			}
			else
				if (j == cols - 1)// checking if the bottom right side
				{
					*max = mat[i][j - 1];
					*min = mat[i][j - 1];
					goto nextbot;
				}
			*max = mat[i][j - 1];
			*min = mat[i][j - 1];
			if (mat[i][j + 1] > * max)
				*max = mat[i][j - 1];
			else
				if (*min > mat[i][j-1])
					*min = mat[i][j-1];
		nextbot:
			if (mat[i - 1][j] > * max)
				*max = mat[i - 1][j];
			else
				if (*min > mat[i - 1][j])
					*min = mat[i - 1][j];
			return;
		}
		else//left side of the matrix
			if (j == 0)
			{
				*max = mat[i][j + 1];
				*min = mat[i][j + 1];
				if (mat[i+1][j] > * max)
					*max = mat[i+1][j];
				else
					if (*min > mat[i+1][j])
						*min = mat[i+1][j];
				if (mat[i - 1][j] > * max)
					*max = mat[i - 1][j + 1];
				else
					if (*min > mat[i - 1][j])
						*min = mat[i - 1][j];
				return;
			}
			else//right side of the matrix
				if (j == cols - 1)
				{
					*max = mat[i][j -1];
					*min = mat[i][j - 1];
					if (mat[i + 1][j] > * max)
						*max = mat[i + 1][j];
					else
						if (*min > mat[i + 1][j])
							*min = mat[i + 1][j];
					if (mat[i - 1][j] > * max)
						*max = mat[i - 1][j];
					else
						if (*min > mat[i - 1][j])
							*min = mat[i - 1][j];
					return;
				}
	            //the rest of the matrix 
				else
				{
					*max = mat[i][j - 1];
					*min = mat[i][j - 1];

					if (mat[i][j + 1] > * max)
						*max = mat[i][j + 1];
					else
						if (*min > mat[i][j+1])
							*min = mat[i][j+1];

					if (mat[i+1][j] > * max)
						*max = mat[i+1][j];
					else
						if (*min > mat[i+1][j])
							*min = mat[i+1][j];

					if (mat[i-1][j] > * max)
						*max = mat[i-1][j];
					else
						if (*min > mat[i-1][j])
							*min = mat[i-1][j];

					return;
				}
}
void Ex2()
{
	int rows, cols;
	printf("enter number of rows in matrix: ");
	scanf_s("%d", &rows);
	printf("\nenter number of coloms in matrix: ");
	scanf_s("%d", &cols);
	system("cls");
	int** mat = (int**)calloc(rows, sizeof(int*));
	assert(mat);
	for (int i = 0; i < rows; i++)
	{
		mat[i] = (int*)calloc(rows, sizeof(int));
		assert(mat[i]);
	}
	for(int i=0;i<rows;i++)
		for (int j = 0; j < cols; j++)
		{
			printf("enter number for location [%d , %d]: ", i, j);
			scanf_s("%d",&mat[i][j]);
			printf("\n");
		}
	system("cls");
	printf("BEFORE: \n");
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			printf("|  %d  ", mat[i][j]);
		}
		printf("|\n");
	}
	printf("AFTER: \n");
	mat = matrixMaxNeighbor(mat, rows, cols);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			printf("|  %d  ", mat[i][j]);
		}
		printf("|\n");
	}
	freemat(mat, rows);
}
/*                                      */
int createArrayAndList(Three** arr, List** head, int** mat,int rows, int cols)
{
	int counter;
	*arr= createThreeArr(mat, rows, cols, &counter);
	*head = createThreeList(*arr, counter);
	return counter;
}
Three createThree(int value, int i, int j)
{
	 Three a = { value, i, j };
	 return a;
}
List* createThreeList(Three* arr, int n)
{
	List* head;
	if (n == 0)
	{
		head = NULL;
		return head;
	}
	head = (List*)malloc(sizeof(List));
	assert(head);
	List* curr;
	curr = head;
	curr->item = arr[0];
	for (int i = 1; i < n; i++)
	{
		curr->next = (List*)malloc(sizeof(List));
		assert(curr->next);
		curr = curr->next;
		curr->item = arr[i];
	}
	curr->next = NULL;
	return head;
}
Three* createThreeArr(int** mat, int rows, int cols,int* counter)
{
	(*counter) = 0;
	int min, max,tmp=0;
	Three item;
	for(int i=0;i<rows;i++)//counting how many neighbors the matrix have
		for (int j = 0; j < cols; j++)
		{
			neighborMaxMin(mat, i, j, rows, cols, &max, &min);
			if (min >= mat[i][j])
				(*counter)++;
		}
	Three* brr;
	brr= (Three*)malloc((*counter) * sizeof(Three));
	assert(brr);
	tmp = 0;
	for (int i = 0; i < rows; i++)//running on the matrix and placing the minimum neighbors in the array
		for (int j = 0; j < cols; j++)
		{
			neighborMaxMin(mat, i, j, rows, cols, &max, &min);
			if (min >= mat[i][j])
			{
				item = createThree(mat[i][j], i, j);
				brr[tmp] = item;
				tmp++;
			}
		}
	return brr;
}
void Ex3()
{
	int rows, cols;
	int** mat;
	List* head;
	Three* arr;
	printf("enter number of rows in matrix: ");
	scanf_s("%d", &rows);
	printf("\nenter number of coloms in matrix: ");
	scanf_s("%d", &cols);
	system("cls");
	mat = (int**)calloc(rows, sizeof(int));
	assert(mat);
	for (int i = 0; i < rows; i++)
	{
		mat[i] = (int*)calloc(cols, sizeof(int));
		assert(mat[i]);
	}
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
		{
			printf("enter number for location [%d , %d]: ", i, j);
			scanf_s("%d", &mat[i][j]);
			printf("\n");
		}
	system("cls");
	int c = createArrayAndList(&arr, &head, mat, rows, cols);
	printf("answer: %d",c);
	printf("\nthe array is:[ ");
	for (int i = 0; i < c; i++)
		printf("%d, [ %d,%d ] |  ", arr[i].value,arr[i].i,arr[i].j);
	printf("]");
	List* cur=head;
	printf("\nthe list is: \n");
	while(head!=NULL)
	{
		printf("{%d, [ %d,%d ]} ==> ",head->item.value,head->item.i,head->item.j);
		head = head->next;
		free(cur);
		cur = head;
	}
	printf("NULL\n");
	free(arr);
	freemat(mat, rows);
}
/*                                      */
void Delete(Num** head, Num* value)
{
	if ((*head) == NULL)//if head is empty
		return;
	if ((*head)->next == NULL)//if the head is the only Num
	{
		free(head);
		return;
	}
	Num* cur = (*head)->next;
	Num* cur2 = (*head);
	if (value == (*head))//if you need to remove the head
	{
		(*head) = (*head)->next;
		free(cur2);
		return;
	}
	while (cur !=value)//running on matrix to find the Num to delete
	{
		cur2 = cur;
		cur = cur->next;
	}
	cur2->next = cur->next;
	free(cur);
}
void Insert(Num** head, int to_insert)
{
	if ((*head) == NULL)//if head is empty
	{
		(*head) = (Num*)malloc(sizeof(Num));
		(*head)->value =to_insert;
		(*head)->next = NULL;
		return;
	}
	Num* cur = (*head);
	//finding the last Node and inserting the element
	while (cur->next !=NULL)
	{
		cur = cur->next;
	}
	cur->next = (Num*)malloc(sizeof(Num));
	cur = cur->next;
	cur->value = to_insert;
	cur->next = NULL;

}
Num* CreateList(Num** head,int flag)
{
	Num* head2=NULL;
	if ((*head) == NULL)
		return head2 = NULL;
	if ((*head)->next == NULL)
	{
		Insert(&head2,(*head)->value);
		Delete(head,NULL);
	}
	Num* cur = (*head)->next;
	if ((*head)->value > cur->value)
	{
		if (flag == 0)//real
		{
			Insert(&head2, (*head)->value);
			Delete(head, *head);
		}
		else//fake 
		{
			createList2(head, &head2, cur);
		}
		
	}
	cur = (*head);
	Num* cur2 = (*head);
	while (cur->next->next!=NULL)
	{
		if (cur2->value < cur->value && cur->next->value < cur->value)
		{
			if (flag == 0)//real
			{
				Insert(&head2, cur->value);
				cur2 = cur;
				cur = cur->next;
				Delete(head, cur2);
				cur2 = cur;
			}
			else//fake
			{
				createList2(head, &head2, cur);
				cur2 = cur2->next;
				cur = cur2->next;
			}
			
		}
		else
		{
			cur2 = cur;
			cur = cur->next;
		}
	}
	if (cur2->value < cur->value && cur->next->value < cur->value)
		{
		if (flag == 0)//real
		{
			Insert(&head2, cur->value);
			cur2 = cur;
			cur = cur->next;
			Delete(head, cur2);
			cur2 = cur;
		}
		else//fake
		{
			createList2(head, &head2, cur);
			cur2 = cur;
			cur = cur->next;
		}
		}
	else
	{
		cur2 = cur;
		cur = cur->next;
	}
	if (cur != NULL&&cur2->value < cur->value)
	{
		if (flag == 0)
		{
			Insert(&head2, cur->value);
			cur2 = cur;
			cur = cur->next;
			Delete(head, cur2);
		}
		else//fake
		{
			createList2(head, &head2, cur);
			cur2 = cur;
			cur = cur->next;
		}
		
	}
	return head2;
}
void Ex4()
{
	printf("enter numbers to insert into list: to finish enter a negative number: \n");
	Num* cur;
	Num* head;
	CreateNewList(&head,0);
	system("cls");
	cur = head;
	printf("original list: ");
	PrintList(&head,0);
	Num* newhead = CreateList(&head,0);
	printf("\nList #1: ");
	PrintList(&head,0);
	printf("List #2: ");
	PrintList(&newhead,0);
	freelist(&head);
	freelist(&newhead);
}
/*                                      */
void createList2(Num** headLocation,Num**headDestenation, Num* value)
{
	Num* cur = (*headLocation);
	if((*headLocation)!=value)
		if ((*headLocation)->next != NULL)
			while (cur->next != value)
				cur = cur->next;
	if ((*headDestenation) == NULL)
	{
		(*headDestenation) = value;
		if (value != (*headLocation))
			cur->next = cur->next->next;
		else
			(*headLocation) = (*headLocation)->next;
		(*headDestenation)->next = NULL;
		return;
	}
	Num* curdes = (*headDestenation);
	while (curdes->next != NULL)
		curdes = curdes->next;
	if ((*headLocation) == value)
	{
		curdes->next = cur;
		(*headLocation) = (*headLocation)->next;
	}
	else
	{
		curdes->next = cur->next;
		cur->next = cur->next->next;
	}
	curdes = curdes->next;
	curdes->next = NULL;
	
}
void Ex5()
{
	printf("enter numbers to insert into list: to finish enter a negative number: \n");
	Num* cur;
	Num* head;
	CreateNewList(&head,0);
	system("cls");
	cur = head;
	printf("original list: ");
	PrintList(&head,0);
	Num* newhead = CreateList(&head,1 );
	printf("\nList #1: ");
	PrintList(&head,0);
	printf("List #2: ");
	PrintList(&newhead,0);
	freelist(&head);
	freelist(&newhead);
}
/*                                      */
void removeDupArrayLists(Num** ArrList,int n)
{
	Num* cur, * run,*lastloc;
	for (int i = 0; i < n; i++)// run on all array's cells
	{
		cur = ArrList[i];
		while (cur!=NULL && cur->next != NULL)
		{
			run = cur->next;
			while (run != NULL)
			{
				if (cur->value == run->value)
				{
					lastloc = run->next;
					Delete(&ArrList[i], run);
					run = lastloc;
				}
				else
				   run = run->next;
			}
			if (cur->next != NULL && cur->next->next != NULL)
			{
				cur = cur->next;
				run = cur->next;
			}
			else
				cur = NULL;
		}
	}
}
void Ex6()
{
	printf("enter how many lists you want to create: ");
	int n;
	scanf_s("%d", &n);
	char tmp;
	Num* cur;
	Num** ArrList = (Num**)malloc(n * sizeof(Num*));
	for (int i = 0; i < n; i++)//creating the lists for each cell of the array
	{
		ArrList[i] = NULL;
		printf("\nenter chars for list #%d, enter ! to finish: \n",i+1);
		CreateNewList(&ArrList[i], 1);
	}
	system("cls");
	printf("original array: \n");
	for (int i = 0; i < n; i++)
	{
		printf("arr[%d] = ", i);
		PrintList(&ArrList[i], 1);
	}
	removeDupArrayLists(ArrList, n);
	printf("Changed array: \n");
	for (int i = 0; i < n; i++)
	{
		printf("arr[%d] = ", i);
		PrintList(&ArrList[i], 1);
	}
	for (int i = 0; i < n; i++)
	{
		freelist(&ArrList[i]);
	}
	free(ArrList);
}
/*                                      */
Num* disassemblyList(Num** head,Num** SmallHead,Num** CapitalHead,Num** NumHead)
{
	Num* CharHead = NULL;
	if ((*head) == NULL)
		return CharHead;
	while ((*head) != NULL)
	{
		if((*head)->value>='0'&& (*head)->value<='9')//in case of numbers
			createList2(head, NumHead, (*head));
		else
			if((*head)->value>='a'&& (*head)->value<='z')//in case of small letters
				createList2(head, SmallHead, (*head));
			else 
				if((*head)->value>='A'&& (*head)->value<='Z')//in case of capital letters
					createList2(head, CapitalHead, (*head));
				else//in case of chars
					createList2(head, &CharHead, (*head));
	}
	return CharHead;
}
void Ex7()
{
	Num* head, * cur;
	printf("enter evey char you want, insert ! to finish\n");
	CreateNewList(&head,1);
	system("cls");
	printf("original list: \n");
	PrintList(&head,1);
	Num* smallhead=NULL, * capitalhead=NULL, * charhead=NULL, * numhead=NULL;
	charhead = disassemblyList(&head, &smallhead, &capitalhead, &numhead);
	printf("\nsmall letters list : \n\n");
	PrintList(&smallhead, 1);
	printf("\ncapital letters list : \n\n");
	PrintList(&capitalhead, 1);
	printf("\nnumber list : \n\n");
	PrintList(&numhead, 1);
	printf("\nchar list : \n\n");
	PrintList(&charhead, 1);
	printf("\n");
	freelist(&smallhead);
	freelist(&capitalhead);
	freelist(&numhead);
	freelist(&charhead);
}

//extra functions
void freemat(int** mat,int rows)
{
	for (int i = 0; i < rows; i++)
		free(mat[i]);
	free(mat);
}
void freelist(Num** list)
{
	Num* cur = (*list); 
	if (cur == NULL)
		return;
	Num* cur2 = (*list)->next;
	while (cur2 != NULL)
	{
		free(cur);
		cur = cur2;
		cur2 = cur2->next;
	}
}
void PrintList(Num** head,int flag)
{
	Num* cur = (*head);
	while (cur != NULL)
	{
		if(flag==0)
			printf("{ %d }==>", cur->value);
		else
			printf("{ %c }==>", cur->value);
		cur = cur->next;
	}
	printf("NULL\n");
}
void CreateNewList(Num** head,int flag)
{
	(*head) = NULL;
	int tmp;
	char c;
	Num* cur;
	if(flag==1)
	   scanf_s(" %c", &c);
	else
		scanf_s(" %d", &tmp);
	if(flag==1)	 
		while (c != '!')
		{
			Insert(head, c);
			scanf_s(" %c", &c);
	    }
	else
		while (tmp >0)
		{
			Insert(head, tmp);
			scanf_s(" %d", &tmp);
		}
}