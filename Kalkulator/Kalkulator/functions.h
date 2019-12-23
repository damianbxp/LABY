#ifndef _F
#define _F

struct Stack
{
	float data[3];		 //[0][Re][Im]<-liczba		[x][0][0]<- operator w kolejnoœci +-*/
	struct Stack* previous;
};

void PUSH(struct Stack*,float*);

void POP(struct Stack*);
#endif // !_F
