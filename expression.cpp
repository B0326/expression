#include "stack.h"
int main() {
	SqStack Optr, Num;
	InitStack(Optr);
	InitStack(Num);
	ReadChar(Num, Optr);
	Clear(Num);
	Clear(Optr);
	system("pause");
}