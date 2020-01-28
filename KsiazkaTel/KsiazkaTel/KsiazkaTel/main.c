#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<locale.h>
#include "func.h"

int main()
{
	setlocale(LC_CTYPE, "Polish");
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
	//Top->Contact = (struct Data*)malloc(sizeof(struct Data));
	if (Top->Contact==NULL)
	{
		printf("\nTop->Contact malloc error");
		system("pause");
		exit(1);
	}

	struct DataCell* ActiveCell;



	Top = loadFromCsv(Top);
	ActiveCell = Top;

	int menuV = -1;

	while (menuV!=48)
	{
		system("cls");
		printList(ActiveCell);
		printf("1.Sortuj imiennie\n2.Sortuj nazwiskami\n3.Sortuj kategori¹\n4.Wyszukaj\n5.Wyszukaj po grupie6.Dodaj kontakt\n7.Usuñ kontakt\n0.EXIT");
		menuV = getch();

		switch (menuV)
		{
		case 49:
		{
			sortName(ActiveCell);
			break;
		}
		case 50:
		{
			sortSurname(ActiveCell);
			break;
		}
		case 51:
		{
			sortCategory(ActiveCell);
			break;
		}
		case 52:
		{
			search(ActiveCell);
			break;
		}
		case 53:
		{
			searchCategory(ActiveCell);
			break;
		}
		case 54:
		{

			break;
		}
		case 55:
		{

			break;
		}
		default:
			break;
		}
	}


	//system("pause");
	return 0;
}