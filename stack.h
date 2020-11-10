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

Status InitStack(SqStack& s);//�����ջ��
Status GetTop(SqStack s);//���ջ��Ԫ�أ�
Status Push(SqStack& s, SElemType e);//����eΪ�µ�ջ��Ԫ�أ�
Status Pop(SqStack& s, SElemType& e);//ɾ��ջ��Ԫ�أ�����eֵ��Ϊ���أ�
Status Clear(SqStack& s);
bool IsNumber(char ch);
Status OptorCompare(char ch, SqStack s);
Status Operate(double a, double b, char theta);
Status ReadChar(SqStack& Num, SqStack& Optr);
