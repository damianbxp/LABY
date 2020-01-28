#ifndef _F
#define _F



struct Data
{
	char name[30];
	char surname[30];
	int phoneNumber;
	char category[20];
};

struct DataCell
{
	struct DataCell* previous;
	struct Data* Contact;
	struct DataCell* next;
};


struct DataCell* loadFromCsv(struct DataCell*);

struct DataCell* addDataCell(struct DataCell*, char*, char*, int, char*);

void resetString(char*);

void printList(struct DataCell*);

struct DataCell* inverseStack(struct DataCell*);

struct DataCell* moveDown(struct DataCell*);

struct DataCell* sortName(struct DataCell*);

#endif // !_F
