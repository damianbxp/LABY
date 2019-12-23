#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

void PUSH(struct Stack* Top, float *data)
{
	struct Stack* New;
	New = (struct Stack*)malloc(sizeof(struct Stack));
	if (New == NULL)
	{
		printf("\nnew malloc error\n");
		system("pause");
		exit(-1);
	}

	New->data[0] = data[0];
	New->data[1] = data[1];
	New->data[2] = data[2];
	New->previous = Top;
	Top = New;

	
}
void POP(struct Stack* Top)
{
	float data[3] = { 0 };
	
	data[0] = Top->data[0];
	data[1] = Top->data[1];
	data[2] = Top->data[2];

	struct Stack* Temp;
	Temp = (struct Stack*)malloc(sizeof(struct Stack));
	if (Temp == NULL)
	{
		printf("\nTemp malloc error\n");
		system("pause");
		exit(-1);
	}

	Temp = Top->previous;

	free(Top);

	Top = Temp;

	free(Temp);
}