#ifndef _F
#define _F

struct Stack
{
	float data[3];		 //[0][Re][Im]<-liczba		[x][0][0]<- operator w kolejno�ci +-*/
	struct Stack* previous;
};

struct Stack* PUSH(struct Stack*,float*);

struct Stack* POP(struct Stack*,float*);

void keyboardInput(float*);
#endif // !_F
