#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

struct Stack* PUSH(struct Stack* Top2, float *data)
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
	New->previous = Top2;
	return New;
}

struct Stack* POP(struct Stack* Top, float *data)
{	
	data[0] = Top->data[0];
	data[1] = Top->data[1];
	data[2] = Top->data[2];

	struct Stack* ToPass;

	ToPass = Top->previous;

	free(Top);
	return ToPass;
}

void keyboardInput(float* newData)
{
	char inputTab[101] = {"\n"};
	char functionInONP[101] = { "\n" };
	float tempData[3] = { 0 };
	float tempRe = 0;
	float tempIm = 0;
	char tempC = "";
	int a;
	struct Stack* Temp = (struct Stack*)malloc(sizeof(struct Stack));
	if (Temp == NULL)
	{
		printf("\ntemp malloc error\n");
		system("pause");
		exit(-1);
	}

	//gets_s(inputTab,100);

	FILE* fp;
	//fp = fopen("function.f","w");
	//fprintf(fp, "%s", inputTab);
	//fclose(fp);

	fp = fopen("function.f", "r");

	while (1)
	{
		tempData[0] = 0;
		tempData[1] = 0;
		tempData[2] = 0;
		a = fscanf(fp, "%f", &tempRe);
		if (0 == a)
		{//gdy znak
			tempC = fgetc(fp);
			switch (tempC)
			{
			case '+':
			{
				tempData[0] = 1;
			}
			default:
				break;
			}
			
		}
		else//gdy liczba Re
		{
			tempData[1] = tempRe;

			if (0 == fscanf(fp, "%f", &tempIm))
			{//gdy znak
				tempData[2] = 0;
			}
			else//gdy liczba Im
			{
				tempData[2] = tempIm;
			}
		}
	}

	fclose(fp);

	free(Temp);
}