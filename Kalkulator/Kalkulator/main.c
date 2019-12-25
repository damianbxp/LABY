#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main()
{
	float newData[3] = { 0 };
	float recivedData[3] = { 0 };
	struct Stack* Top;
	Top = (struct Stack*)malloc(sizeof(struct Stack));
	if (Top==NULL)
	{
		printf("\ntop malloc error\n");
		system("pause");
		exit(-1);
	}

	Top->data[0] = 0;
	Top->data[1] = 0;
	Top->data[2] = 0;
	Top->previous = NULL;
	
	newData[0] = 0;
	newData[1] = 1;
	newData[2] = 2;

	Top = PUSH(Top, newData);

	newData[0] = 10;
	newData[1] = 11;
	newData[2] = 12;

	

	Top = POP(Top, recivedData);

	keyboardInput(newData);

	free(Top);
	//system("pause");
	return 0;
}