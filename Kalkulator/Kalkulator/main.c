#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main()
{
	int menu = 0;
	float result[2] = { 0 };
	struct Stack* Top;
	Top = (struct Stack*)malloc(sizeof(struct Stack));
	if (Top==NULL)
	{
		printf("\ntop malloc error\n");
		system("pause");
		exit(-1);
	}

	Top->data[0] = -1;
	Top->data[1] = -1;
	Top->data[2] = -1;
	Top->previous = NULL;
	
	printf("1.Notacja infliksowa\n2.Odwrotna notacja Polska\n");
	scanf("%d", &menu);
	switch (menu)
	{
	case 1:
	{
		keyboardInput();
		Top = generateStack(Top);
		Top = inverseStack(Top);
		Top = calculate(Top, result);
		break;
	}
	case 2:
	{
		Top = enterStack(Top);
		Top = inverseStack(Top);
		Top = calculate(Top, result);
		break;
	}
	default:
		break;
	}

	

	printf("Wynik: %f", result[0]);
	if (result[1]>=0)
	{
		printf(" + ");
	}
	printf("%fi", result[1]);


	free(Top);
	printf("\n");
	system("pause");
	return 0;
}