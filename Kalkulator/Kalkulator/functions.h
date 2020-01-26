#ifndef _F
#define _F

struct Stack
{
	float data[3];		 //[0][Re][Im]<-liczba		[x][0][0]<- operator w kolejnoœci +-*/()
	struct Stack* previous;
};

struct Stack* PUSH(struct Stack*,float*);

struct Stack* POP(struct Stack*,float*);

void keyboardInput();

struct Stack* generateStack(struct Stack*);

struct Stack* inverseStack(struct Stack*);

struct Stack* calculate(struct Stack*, float*);

struct Stack* enterStack(struct Stack*);
#endif // !_F
