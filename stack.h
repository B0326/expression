#include<stdio.h>
#include<stdlib.h>
#define SIZE 100
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0;
#define INFENASIBLE -1
#define OVERFLOW -2
typedef double Status;
typedef double  SElemType;

#define STACKINCREMENT 10

typedef struct {
	SElemType* base;
	SElemType* top;
	int stacksize;
}SqStack;

Status InitStack(SqStack& s);//构造空栈；
Status GetTop(SqStack s);//获得栈顶元素；
Status Push(SqStack& s, SElemType e);//插入e为新的栈顶元素；
Status Pop(SqStack& s, SElemType& e);//删除栈顶元素，并用e值作为返回；
Status Clear(SqStack& s);
bool IsNumber(char ch);
Status OptorCompare(char ch, SqStack s);
Status Operate(double a, double b, char theta);
Status ReadChar(SqStack& Num, SqStack& Optr);
