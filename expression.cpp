#include "stack.h"
int main() {
	SqStack Optr,Num;
	InitStack(Optr );
	InitStack(Num);
	int flag = 0;
	double  theta=0,x=0 ;
	double a=0, b=0;
	double  ch=0;
	Push(Optr, '#');
	printf("请输入表达式:\n");
		for (int i = 0; i < 100; i++) {
		while ((ch = getchar()) != '\n') {
			if (IsNumber(ch)) {
				ch = ch - '0';
				if (flag == 0) {

					Push(Num, ch);
				}
				else {
					while (flag != 0) {
						Pop(Num, a);
						ch = a * 10 + ch;
						flag--;
					}
					Push(Num, ch);
				}
				flag++;
			}
			else {
				flag = 0;
				char sn = (int)OptorCompare(ch, Optr);
				switch (sn)
				{
				case '<':
					Push(Optr, ch);
				break;
				case '>':
					Pop(Optr, theta);
					Pop(Num, a);
					Pop(Num, b);
					Push(Num, Operate(a, b, theta));
					if((int)OptorCompare(ch, Optr)=='=')
						Pop(Optr, theta);
					else 
					Push(Optr, ch);
					break;
				case '=':
					Pop(Optr, x);
					break;
				}
			}
		}
		Pop(Optr, theta);
	while (theta  != '#') {
	    Pop(Num, a);		
		Pop(Num, b);
		Push(Num, Operate(a, b, theta));
		Pop(Optr, theta);	
	}
	Pop(Num, b);
	printf("=%f\n", b);
	flag = 0;
	Push(Optr, '#');
	}	
	Clear(Num);
	Clear(Optr );
	system("pause");
}