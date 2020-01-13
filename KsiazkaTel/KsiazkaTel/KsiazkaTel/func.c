#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "func.h"


struct DataCell* loadFromCsv(struct DataCell* TopDataCell)
{
	char name[30] = "\0";
	char surname[30] = "\0";
	int phoneNumber = 0;
	int category = 0;
	char tempRow[100] = "\0";
	char tempPhoneNumber[20] = "\0";
	char tempCategory[20] = "\0";
	int tempCounter = 0;
	int tempDelta = 0;
	FILE* fp = fopen("phoneBook.csv", "r");
	
	while (fgets(tempRow,100,fp)!=NULL)
	{
		resetString(tempCategory);
		resetString(name);
		resetString(surname);
		resetString(tempPhoneNumber);
		tempCounter = 0;
		tempDelta = 0;
		while (tempRow[tempCounter]!=';')//name
		{
			name[tempCounter] = tempRow[tempCounter];
			tempCounter++;
		}
		tempCounter++;
		tempDelta = tempCounter;

		while (tempRow[tempCounter] != ';')//surname
		{
			surname[tempCounter-tempDelta] = tempRow[tempCounter];
			tempCounter++;
		}
		tempCounter++;
		tempDelta = tempCounter;

		while (tempRow[tempCounter] != ';')//phone number
		{
			tempPhoneNumber[tempCounter - tempDelta] = tempRow[tempCounter];
			tempCounter++;
		}
		tempCounter++;
		tempDelta = tempCounter;
		while (tempRow[tempCounter] != ';')//category
		{
			if (tempRow[tempCounter] == '\n') break;
			tempCategory[tempCounter - tempDelta] = tempRow[tempCounter];
			tempCounter++;
		}

		phoneNumber = atoi(tempPhoneNumber);
		
		if (0 == strcmp(tempCategory,"rodzina"))
		{
			category = 1;
		}
		else if (0 == strcmp(tempCategory, "praca"))
		{
			category = 2;
		}
		else if (0 == strcmp(tempCategory, "znajomi"))
		{
			category = 3;
		}
		else
		{
			category = 0;
		}

		TopDataCell = addDataCell(TopDataCell, name, surname, phoneNumber, category);
	}

	fclose(fp);
	return TopDataCell;
}

struct DataCell* addDataCell(struct DataCell* TopDataCell, char *name, char* surname, int phoneNumber, int category)
{
	struct DataCell* New;
	New = (struct Data*)malloc(sizeof(struct Data));
	if (New == NULL)
	{
		printf("\nNew malloc error\n");
		system("pause");
		exit(-1);
	}

	TopDataCell->next = New;

	New->previous = TopDataCell;
	New->next = NULL;
	New->Contact= (struct Data*)malloc(sizeof(struct Data));
	if (New->Contact == NULL)
	{
		printf("\nNew->Contact malloc error");
		system("pause");
		exit(1);
	}

	strcpy(New->Contact->name, name);
	strcpy(New->Contact->surname, surname);
	New->Contact->phoneNumber = phoneNumber;
	New->Contact->category = category;

	return New;
}

void resetString(char* string)
{
	int i = 0;
	while (string[i]!='\0')
	{
		string[i] = '\0';
		i++;
	}
}