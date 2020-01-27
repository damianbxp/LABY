#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "func.h"

int main()
{

	struct DataCell* Top;
	Top = (struct DataCell*)malloc(sizeof(struct DataCell));
	if (Top == NULL)
	{
		printf("\nTop malloc error\n");
		system("pause");
		exit(-1);
	}


	Top->previous = NULL;
	Top->next = NULL;
	Top->Contact = (struct Data*)malloc(sizeof(struct Data));
	if (Top->Contact==NULL)
	{
		printf("\nTop->Contact malloc error");
		system("pause");
		exit(1);
	}

	Top = loadFromCsv(Top);
	printList(Top);
	//system("pause");


	return 0;
}