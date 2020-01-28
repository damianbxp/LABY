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

	int currentSort = 0;//1-imine  2-nazwisko  3-grupa
	int menuV = -1;

	while (menuV!=48)
	{
		system("cls");
		printList(ActiveCell);
		printf("1.Sortuj imiennie\n2.Sortuj nazwiskami\n3.Sortuj kategori¹\n4.Wyszukaj\n5.Wyszukaj po grupie\n6.Dodaj kontakt\n7.Usuñ kontakt\n0.EXIT");
		menuV = getch();

		switch (menuV)
		{
		case 49:
		{
			sortName(ActiveCell);
			currentSort = 1;
			break;
		}
		case 50:
		{
			sortSurname(ActiveCell);
			currentSort = 2;
			break;
		}
		case 51:
		{
			sortCategory(ActiveCell);
			currentSort = 3;
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
			addContact(ActiveCell,currentSort);

			switch (currentSort)
			{
			case 1:
			{
				sortName(ActiveCell);
				break;
			}
			case 2:
			{
				sortSurname(ActiveCell);
				break;
			}
			case 3:
			{
				sortCategory(ActiveCell);
				break;
			}
			default:
				break;
			}
			break;
		}
		case 55:
		{
			deleteContact(ActiveCell);
			break;
		}
		default:
			break;
		}
	}


	//system("pause");
	return 0;
}