#include "stack.h"


Status InitStack(SqStack& s)//构造新栈；
{
	s.base = (SElemType*)malloc(SIZE * sizeof(SElemType));//申请一段连续的空间为栈存储数据的空间
	if (!s.base) return FALSE;
	s.top = s.base;//让栈顶等于栈底表示为空栈
	s.stacksize = 100;//栈的空间大小
	return OK;
}
Status GetTop(SqStack s) //获得并以栈顶元素为返回值
{
	if (s.top == s.base) return ERROR;	
	 return *(s.top - 1);	 //返回栈顶元素
}
Status Push(SqStack& s, SElemType e)//插入e为新的栈顶元素；
{
	if (s.top - s.base == s.stacksize) {
		s.base = (SElemType*)realloc(s.base, (s.stacksize + SIZE) * sizeof(SElemType));
		//扩大栈的空间
		if (!s.base) exit(OVERFLOW);
		s.top = s.base + s.stacksize;
		s.stacksize += SIZE;
	}
	*s.top = e;//插入元素e为栈顶元素
	s.top = s.top + 1;//栈顶指针指向该栈的下一个空的空间；
	return OK;
}
Status Pop(SqStack& s, SElemType &e) //弹出该栈的栈顶元素
{
	if (s.top == s.base) return ERROR;
	s.top = s.top - 1;//栈顶
	e = *s.top;
	return OK;
}
Status Clear(SqStack& s) //释放栈
{
	free(s.base);
	s.base = NULL;
	s.top=NULL;
	return OK;
}

Status OptorCompare(char ch, SqStack s)//运算符优先级判断
{
	switch (ch) {
	case '+':
		if (GetTop(s) == '('||GetTop(s)=='#') return '<';
		else return '>';
		break;
	case '-':
		if (GetTop(s) == '(' || GetTop(s) == '#') return '<';
		else return '>';
		break;
	case '*':
		if (GetTop(s) == '+'||GetTop(s) == '-'
			||GetTop(s) == '(' || GetTop(s) == '#') return '<';
		else  return '>';
		break;
	case '/':
		if (GetTop(s) == '+' || GetTop(s) == '-'
			|| GetTop(s) == '(' || GetTop(s) == '#') return '<';
		else  return '>';
		break;
	case '(':
		return '<';
		break;
	case ')':	
		if (GetTop(s) == '(') return '=';
		else return '>';		
		break;
	case '#':
		if (GetTop(s) == '#') return '=';
		else return '>';
		break;
	}
}
bool IsNumber(char ch) //判断是数字还是运算符
{
	if (ch >= '0' && ch <= '9') return true;
	else return false ;
}
Status Operate(double  a, double b, char theta)//加减乘除
{
	switch (theta) {
	case '+':
		return a + b;
		break;
	case '-':
		return b - a;
		break;
	case '*':
		return a * b;
		break;
	case '/':
		return  b/ a;
	}
}