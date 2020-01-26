#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include "functions.h"

#define functionMaxLenght 101

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

void keyboardInput() //generuje plik równania
{
	char inputTab[functionMaxLenght] = {"\n"};
	printf("WprowadŸ równanie (czêœæ zespolona powinna byæ w formacie ix):\n");
	gets_s(inputTab,100);

	//generowanie pliku
	FILE* fp;
	fp = fopen("functions.f", "w");
	fprintf(fp, "%s", inputTab);
	fclose(fp);
}

struct Stack* generateStack(struct Stack* Top)
{
	char inputTab[functionMaxLenght] = { "\0" };
	char temp = 'a';
	char charNumberRe[13] = { "\0" };
	char charNumberIm[13] = { "\0" };
	int tabCounter = 0;
	int afterDotCount = 0;
	float newData[3] = {0};

	struct Stack* TempStack;//tymczasowy stos
	TempStack = (struct Stack*)malloc(sizeof(struct Stack));
	TempStack->data[0] = -1;
	TempStack->data[1] = -1;
	TempStack->data[2] = -1;
	TempStack->previous = NULL;


	FILE* fp;
	fp = fopen("functions.f", "r");

	while((temp=fgetc(fp)) != EOF)//sprawdz znak po znaku czy jest znak bia³y
	{
		if (!(temp == ' ' || temp =='\t'))//usuwanie znaków bia³ych
		{
			inputTab[tabCounter] = temp;
			tabCounter++;
		}
	}
	fclose(fp);

	tabCounter = 0;
	//odszyfrowywanie
	while (inputTab[tabCounter] != '\0'	&& inputTab[tabCounter] != '\n')
	{
		for (int i = 0; i < 3; i++) newData[i] = 0;//zeruje new data
		for (int i = 0; i < 12; i++) charNumberRe[i] = '\0';//zeruje Char Re
		for (int i = 0; i < 12; i++) charNumberIm[i] = '\0';//zeruje Char Im
		

		//gdy argument
		if (0 != isdigit(inputTab[tabCounter]))
		{
			//czêœæ rzeczywista
			for (int i = 0; 0 != isdigit(inputTab[tabCounter])	||	inputTab[tabCounter]==','	|| inputTab[tabCounter] =='.'; i++) // prawda gdy liczba, "," lub "."
			{
				if (inputTab[tabCounter] == ',')//gdy przecinek to wstawia kropke
				{
					charNumberRe[i] = '.';
					afterDotCount = 1;
				}
				else
				{
					charNumberRe[i] = inputTab[tabCounter];
					if(afterDotCount>1) afterDotCount++;//do liczenia miejsc po przecinku
				}
				
				tabCounter++;
			}
			

			afterDotCount = 0;
			if ((inputTab[tabCounter]=='+'  ||   inputTab[tabCounter]=='-')	&&	inputTab[tabCounter+1]=='i')//gdy jest "+i" lun "-i" 
			{//czêœæ urojona
				tabCounter += 2;
				for (int i = 0; 0 != isdigit(inputTab[tabCounter]) || inputTab[tabCounter] == ',' || inputTab[tabCounter] == '.'; i++) // prawda gdy liczba, "," lub "."
				{
					if (inputTab[tabCounter] == ',') charNumberIm[i] = '.'; //gdy przecinek to wstawia kropke
					else
					{
						if (inputTab[tabCounter - 2] == '+')
						{
							charNumberIm[i] = inputTab[tabCounter];
						}
						else//gdy jest -i
						{
							charNumberIm[0] = '-';
							charNumberIm[i+1] = inputTab[tabCounter];
						}
						
					}

					tabCounter++;
				}
			}
			newData[1] = atof(charNumberRe);
			newData[2] = atof(charNumberIm);

			Top = PUSH(Top, newData);

		}
		
		//gdy "("
		else if(inputTab[tabCounter]=='(')
		{
			newData[0] = 5;
			TempStack = PUSH(TempStack, newData);
			tabCounter++;
		}
		//gdy ")"
		else if(inputTab[tabCounter]==')')
		{
			while (TempStack->data[0] != 5)//gdy na górze tymczasowego stosu nie le¿y "(" <--- data[0]=5
			{
				Top = PUSH(Top, TempStack->data);
				TempStack = POP(TempStack, newData);
			}
			TempStack = POP(TempStack, newData);//sci¹ga "(" ze stosu
			tabCounter++;
		}


		else if (inputTab[tabCounter] == '*' || inputTab[tabCounter] == '/')//gdy "*" lub "/" <-- maj¹ najwiêkszy priorytet
		{
			if(inputTab[tabCounter] == '*')newData[0] = 3;
			if(inputTab[tabCounter] == '/')newData[0] = 4;
			TempStack = PUSH(TempStack, newData);
			tabCounter++;
		}

		else if (inputTab[tabCounter] == '+' || inputTab[tabCounter] == '-')//gdy "+" lub "-"
		{
			if (TempStack->data[0] == 3 || TempStack->data[0] == 4)//je¿eli na tymczasowym stosie siedzi "*" lub "/"
			{
				Top = PUSH(Top, TempStack->data);
				TempStack = POP(TempStack, newData);
			}

			if (inputTab[tabCounter] == '+')newData[0] = 1;
			if (inputTab[tabCounter] == '-')newData[0] = 2;
			TempStack = PUSH(TempStack, newData);

			tabCounter++;
		}
		else
		{
			printf("\nNiespodziewane znaki w równaniu\n");
		}
	}

	while (TempStack->previous!=NULL)//zbiera reszte z tymczasowego stosu
	{
		Top = PUSH(Top, TempStack->data);
		TempStack = POP(TempStack, newData);
	}

	free(TempStack);
	return Top;
}

struct Stack* inverseStack(struct Stack* Top)
{
	struct Stack* TempStack;//tymczasowy stos
	TempStack = (struct Stack*)malloc(sizeof(struct Stack));
	TempStack->data[0] = -1;
	TempStack->data[1] = -1;
	TempStack->data[2] = -1;
	TempStack->previous = NULL;

	float garbage[3] = { 0 };

	while (Top->previous != NULL)
	{
		TempStack = PUSH(TempStack, Top->data);
		Top = POP(Top, garbage);
	}

	free(Top);
	return TempStack;
}

struct Stack* calculate(struct Stack* Source, float *result)
{
	struct Stack* TempStack;//tymczasowy stos
	TempStack = (struct Stack*)malloc(sizeof(struct Stack));
	TempStack->data[0] = -1;
	TempStack->data[1] = -1;
	TempStack->data[2] = -1;
	TempStack->previous = NULL;

	float data[3] = { 0 };
	float argData[3] = { 0 };//do prze¿ucenia na zmienne arg_a i arg_b
	float arg_a[2] = { 0 }; //[Re][Im]
	float arg_b[2] = { 0 };

	while (Source->previous != NULL)
	{
		Source = POP(Source, data);
		if (data[0] == 0)//gdy argument
		{
			TempStack = PUSH(TempStack, data);
		}
		else//gdy operator
		{
			TempStack = POP(TempStack, argData);
			arg_b[0] = argData[1];
			arg_b[1] = argData[2];

			TempStack = POP(TempStack, argData);
			arg_a[0] = argData[1];
			arg_a[1] = argData[2];

			

			switch ((int)data[0])
			{
			case 1://+
			{
				argData[1] = arg_a[0] + arg_b[0];
				argData[2] = arg_a[1] + arg_b[1];
				TempStack = PUSH(TempStack,argData);
				break;
			}
			case 2://-
			{
				argData[1] = arg_a[0] - arg_b[0];
				argData[2] = arg_a[1] - arg_b[1];
				TempStack = PUSH(TempStack, argData);
				break;
			}
			case 3://*
			{
				argData[1] = arg_a[0] * arg_b[0] - arg_a[1] * arg_b[1];
				argData[2] = arg_a[1] * arg_b[0] + arg_a[0] * arg_b[1];
				break;
			}
			case 4:// /
			{
				argData[1] = arg_a[0] * arg_b[0] + arg_a[1] * arg_b[1];
				argData[1] /= powf(arg_b[0],2) + powf(arg_b[1],2);

				argData[2] = arg_a[1] * arg_b[0] - arg_a[0] * arg_b[1];
				argData[2] /= powf(arg_b[0], 2) + powf(arg_b[1], 2);
				break;
			}
			default:
			{
				printf("\n Nieznany operator\n");
				break;
			}
			}
		}
	}

	result[0] = argData[1];
	result[1] = argData[2];
	free(Source);
	return TempStack;
}

struct Stack* enterStack(struct Stack* Source)
{
	char enterString[20] = "\0";
	do
	{
		scanf("%s", enterString);
	} while (1);
	return Source;
}