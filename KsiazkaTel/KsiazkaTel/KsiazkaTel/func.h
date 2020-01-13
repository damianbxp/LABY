#ifndef _F
#define _F

struct Data
{
	char name[30];
	char surname[30];
	int phoneNumber;
	int category; // 0 - brak kategorii | 1 - rodzina | 2 - praca | 3 - znajomi
};

struct DataCell
{
	struct DataCell* previous;
	struct Data* Contact;
	struct DataCell* next;
};

struct DataCell* loadFromCsv(struct DataCell*);

struct DataCell* addDataCell(struct DataCell*, char*, char*, int, int);

void resetString(char*);
#endif // !_F
