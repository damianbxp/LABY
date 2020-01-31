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
	FILE* fp = fopen("phoneBook2.csv", "r");
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

	TopDataCell->previous = New;

	New->next = TopDataCell;
	New->previous = NULL;
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
	printf("%25s %25s %25s %25s\n\n","Imiê","Nazwisko","Nr Tel","Grupa");
	while (Source->previous != NULL) Source = Source->previous;//przewija do pocz¹tku
	while (Source->next!=NULL)
	{
		printf("%25s %25s %25d %25s\n", Source->Contact->name, Source->Contact->surname, Source->Contact->phoneNumber, Source->Contact->category);
		Source = Source->next;
	}
	printf("\n\n");
}

struct DataCell* moveDown(struct DataCell* Source)
{

	if (Source->next->next != NULL)//zabezpieczenie przed przenoszeniem ostatniego
	{

		if (Source->previous != NULL) Source->previous->next = Source->next;//zabezpieczenie w razie przenoszenia pierwzsego
		Source->next->previous = Source->previous;

		Source->previous = Source->next;
		Source->next = Source->previous->next;

		Source->previous->next = Source;
		Source->next->previous = Source;

	}

	return Source;
}

void sortName(struct DataCell* Source)
{
	int isDone = 1;
	

	while (isDone>0)
	{
		isDone = 0;
		while (Source->previous != NULL) Source = Source->previous;//przewija do pocz¹tku
		while (Source->next->next != NULL)//pêtla to pojedyñczego przejœcia
		{
			if (0 < strcoll(Source->Contact->name, Source->next->Contact->name))
			{
				Source = moveDown(Source);
				isDone++;
			}
			else Source = Source->next;
		}
	}
}

void sortSurname(struct DataCell* Source)
{
	int isDone = 1;


	while (isDone > 0)
	{
		isDone = 0;
		while (Source->previous != NULL) Source = Source->previous;//przewija do pocz¹tku
		while (Source->next->next != NULL)//pêtla to pojedyñczego przejœcia
		{
			if (0 < strcoll(Source->Contact->surname, Source->next->Contact->surname))
			{
				Source = moveDown(Source);
				isDone++;
			}
			else Source = Source->next;
		}
	}
}

void sortCategory(struct DataCell* Source)
{
	int isDone = 1;


	while (isDone > 0)
	{
		isDone = 0;
		while (Source->previous != NULL) Source = Source->previous;//przewija do pocz¹tku
		while (Source->next->next != NULL)//pêtla to pojedyñczego przejœcia
		{
			if (0 < strcoll(Source->Contact->category, Source->next->Contact->category))
			{
				Source = moveDown(Source);
				isDone++;
			}
			else Source = Source->next;
		}
	}
}

void search(struct DataCell* Source)
{
	char searchTab[21]="\0";
	char nameForSearch[30] = "\0";
	char surnameForSearch[30] = "\0";
	char temp = '\0';

	while (temp!='`')//pêtla do wpisywania
	{
		system("cls");
		printf("Wyniki wyszukiwania:\n%25s %25s %25s %25s\n\n", "Imiê", "Nazwisko", "Nr Tel", "Kategoria");
		while (Source->previous != NULL) Source = Source->previous;//przewija do pocz¹tku
		while (Source->next != NULL)
		{
			strcpy(nameForSearch, Source->Contact->name);
			strcpy(surnameForSearch, Source->Contact->surname);
			if (strstr(_strlwr(nameForSearch), _strlwr(searchTab)) != NULL || strstr(_strlwr(surnameForSearch), _strlwr(searchTab)) != NULL)
			{
				printf("%25s %25s %25d %25s\n", Source->Contact->name, Source->Contact->surname, Source->Contact->phoneNumber, Source->Contact->category);
			}
			Source = Source->next;
		}
		printf("\nwciœcij '`' aby wyjœæ\n");
		printf("szukaj: %s", searchTab);
		temp = getch();
		
		for (int i = 0;i<20; i++)
		{
			if (searchTab[i] == '\0')//przechodzi na koniec stringa
			{
				if (temp!='\b')//czy ma usun¹æ
				{
					searchTab[i] = temp;
				}
				else// tak, ma usun¹æ
				{
					if(i!=0) searchTab[i - 1] = '\0';
				}
				
				break;
			}
		}
	}
}

void searchCategory(struct DataCell* Source)
{
	char searchTab[21] = "\0";
	char categoryForSearch[30] = "\0";
	char temp = '\0';

	while (temp != '`')//pêtla do wpisywania
	{
		system("cls");
		printf("Wyniki wyszukiwania:\n%25s %25s %25s %25s\n\n", "Imiê", "Nazwisko", "Nr Tel", "Kategoria");
		while (Source->previous != NULL) Source = Source->previous;//przewija do pocz¹tku
		while (Source->next != NULL)
		{
			strcpy(categoryForSearch, Source->Contact->category);
			if (strstr(_strlwr(categoryForSearch), _strlwr(searchTab)) != NULL)
			{
				printf("%25s %25s %25d %25s\n", Source->Contact->name, Source->Contact->surname, Source->Contact->phoneNumber, Source->Contact->category);
			}
			Source = Source->next;
		}
		printf("\nwciœcij '`' aby wyjœæ\n");
		printf("szukaj: %s", searchTab);
		temp = getch();

		for (int i = 0; i < 20; i++)
		{
			if (searchTab[i] == '\0')
			{
				if (temp != '\b')
				{
					searchTab[i] = temp;
				}
				else
				{
					if (i != 0) searchTab[i - 1] = '\0';
				}

				break;
			}
		}
	}
}

void addContact(struct DataCell* Source)
{
	char temp = '\0';
	char inputTab[30] = "\0";
	char name[30];
	char surname[30];
	int phoneNumber = 0;
	char category[30];

	for (int i = 1; i <= 4; i++)//iteracje 0.-imie 1.- nazwisko 2.-numer 3.-grupa
	{
		temp = '\0';
		while (temp != '\t')//tabem przechodzi siê do nastêpngo inputu
		{
			system("cls");
			printf("%10s %10s %10s %10s\n\n", "Imiê", "Nazwisko", "Nr Tel", "Grupa");
			
			switch (i)
			{
			case 1:
			{
				printf("%10s",inputTab);
				break;
			}
			case 2:
			{
				printf("%10s %10s",name,inputTab);
				break;
			}
			case 3:
			{
				printf("%10s %10s %10s",name,surname,inputTab);
				break;
			}
			case 4:
			{
				printf("%10s %10s %10d %10s",name,surname,phoneNumber,inputTab);
				break;
			}
			default:
				break;
			}

			temp = getch();

			//tworzenie stringa
			for (int i = 0; i < 20; i++)
			{
				if (inputTab[i] == '\0')
				{
					if (temp != '\b' && temp!='\t')
					{
						inputTab[i] = temp;
					}
					else if (temp =='\b')
					{
						if (i != 0) inputTab[i - 1] = '\0';
					}

					break;
				}
			}

		}


		switch (i)
		{
		case 1:
		{
			strcpy(name, inputTab);
			break;
		}
		case 2:
		{
			strcpy(surname, inputTab);
			break;
		}
		case 3:
		{
			phoneNumber = atoi(inputTab);
			break;
		}
		case 4:
		{
			strcpy(category, inputTab);
			break;
		}
		default:
			break;
		}
		resetString(inputTab);
	}

	Source = addDataCell(Source, name, surname, phoneNumber, category);

	
}

struct DataCell* deleteContact(struct DataCell* Source)
{
	char input = '\0';
	struct DataCell* HoveredCell;
	HoveredCell = Source;
	while (Source->previous != NULL) Source = Source->previous;//przewija do pocz¹tku

	while (input!='`')
	{
		system("cls");
		printf("%25s %25s %25s %25s\n", "Imiê", "Nazwisko", "Nr Tel", "Grupa");
		while (Source->previous != NULL) Source = Source->previous;//przewija do pocz¹tku
		while (Source->next != NULL)
		{
			printf("\n%25s %25s %25s %25s", Source->Contact->name, Source->Contact->surname, Source->Contact->phoneNumber, Source->Contact->category);
			if (HoveredCell == Source)printf(" <---");
			Source = Source->next;
		}
		
		input = getch();
		if (input=='w')//poruszanie sie po liœci w s
		{
			if(HoveredCell->previous!=NULL) HoveredCell = HoveredCell->previous;
		}
		else if (input == 's')
		{
			if(HoveredCell->next->next!=NULL) HoveredCell = HoveredCell->next;
		}
	}
	while (Source->previous != NULL) Source = Source->previous;//przewija do pocz¹tku

	if (HoveredCell->previous != NULL) HoveredCell->previous->next = HoveredCell->next;
	else Source = HoveredCell->next;
	if(HoveredCell->next!=NULL) HoveredCell->next->previous = HoveredCell->previous;


	//free(HoveredCell->Contact);
	//free(HoveredCell);
	
	return Source;
}