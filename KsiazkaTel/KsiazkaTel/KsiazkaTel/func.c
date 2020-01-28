#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "func.h"


struct DataCell* loadFromCsv(struct DataCell* TopDataCell)
{
	char name[30] = "\0";
	char surname[30] = "\0";
	int phoneNumber = 0;
	char tempRow[100] = "\0";
	char tempPhoneNumber[20] = "\0";
	char tempCategory[20] = "\0";
	FILE* fp = fopen("phoneBook.csv", "r");
	while (fgets(tempRow, 100, fp) != NULL)
	{
		resetString(tempCategory);
		resetString(name);
		resetString(surname);
		resetString(tempPhoneNumber);

		sscanf(tempRow, "%[^;];%[^;];%[^;];%s", name, surname, tempPhoneNumber, tempCategory);

		phoneNumber = atoi(tempPhoneNumber);


		TopDataCell = addDataCell(TopDataCell, name, surname, phoneNumber, tempCategory);
	}

	fclose(fp);
	return TopDataCell;
}

struct DataCell* addDataCell(struct DataCell* TopDataCell, char *name, char* surname, int phoneNumber, char* category)
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
	strcpy(New->Contact->category, category);

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

void printList(struct DataCell* Source)
{
	while (Source->next != NULL) Source = Source->next;//przewija do pocz¹tku
	while (Source->previous!=NULL)
	{
		printf("%10s %10s %10d %10s\n", Source->Contact->name, Source->Contact->surname, Source->Contact->phoneNumber, Source->Contact->category);
		Source = Source->previous;
	}
}

struct DataCell* inverseStack(struct DataCell* Top)
{
	struct DataCell* NewStack;

	NewStack = Top;
	while (Top->previous!=NULL)
	{
		NewStack->next = Top->previous;

	}
	
	return NewStack;
}

struct DataCell* moveDown(struct DataCell* Source)
{

	if (Source->previous->previous != NULL)//zabezpieczenie przed przenoszeniem ostatniego
	{

		if (Source->next != NULL) Source->next->previous = Source->previous;//zabezpieczenie w razie przenoszenia pierwzsego
		Source->previous->next = Source->next;

		Source->next = Source->previous;
		Source->previous = Source->next->previous;

		Source->next->previous = Source;
		Source->previous->next = Source;

	}

	return Source;
}

struct DataCell* sortName(struct DataCell* Source)
{
	while (Source->previous != NULL) Source = Source->previous;//przewija do pocz¹tku

	if (0<strcoll(Source->Contact->name,Source->next->Contact->name))
	{

	}


	return Source;
}