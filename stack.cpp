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
Status Pop(SqStack& s, SElemType& e) //弹出该栈的栈顶元素
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
	s.top = NULL;
	return OK;
}

Status OptorCompare(char ch, SqStack s)//运算符优先级判断
{
	switch (ch) {
	case '+':
		if (GetTop(s) == '(' || GetTop(s) == '#') return '<';
		else return '>';
		break;
	case '-':
		if (GetTop(s) == '(' || GetTop(s) == '#') return '<';
		else return '>';
		break;
	case '*':
		if (GetTop(s) == '+' || GetTop(s) == '-'
			|| GetTop(s) == '(' || GetTop(s) == '#') return '<';
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
	else return false;
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
		return  b / a;
		break;
	}
}
Status ReadChar(SqStack& Num, SqStack& Optr) {
	int flag = 0;
	double  theta = 0, x = 0;//运算符
	double a = 0, b = 0;//数字；
	double  ch = 0;
	Push(Optr, '#');//输入结束标识符	
	for (int i = 0; i < 100; i++) {
		printf("请输入表达式:\n");
		while ((ch = getchar()) != '\n') //获得键盘输入的无符号整形的值
		{
			if (IsNumber(ch))
			{
				ch = ch - '0';//如果是数字就将其转换为十进制的值
				if (flag == 0)//如果是输入两位数及以上，由于getchar()只能都一位数，所以需要用flag来判断前一个getchar()是不是数字
				{

					Push(Num, ch);//将数字进栈
				}
				else {
					Pop(Num, a);
					ch = a * 10 + ch;
					Push(Num, ch);
				}
				flag = 1;
			}
			else {
				flag = 0;
				switch ((int)OptorCompare(ch, Optr))//如果是操作符先和栈里的栈顶操作符进行优先级比较
				{
				case '<':
					Push(Optr, ch);//如果已经进栈的操作符优先级低于需要进栈的操作符，则新操作符进栈
					break;
				case '>'://如果已经进栈的操作符优先级高于需要进栈的操作符，则
					Pop(Optr, theta);//已经进栈的操作符出栈
					Pop(Num, a);//弹出-个数字
					Pop(Num, b);////弹出-个数字
					Push(Num, Operate(a, b, theta));//对两个数字进行加减乘除，并将结果压入数字栈；
					if ((int)OptorCompare(ch, Optr) == '=')//如果需要进栈的操作符是')'
						Pop(Optr, theta);//则将操作符栈中的')'弹出
					else
						Push(Optr, ch);//压入新的操作符
					break;
				case '=':
					Pop(Optr, x);//出现‘=’的情况只能是'('与')'相遇，所以弹出'(';
					break;
				}
			}
		}
		Pop(Optr, theta);
		while (theta != '#') {
			Pop(Num, a);
			Pop(Num, b);
			Push(Num, Operate(a, b, theta));//对两个数字进行加减乘除，并将结果压入数字栈；
			Pop(Optr, theta);
		}
		Pop(Num, b);//将最终结果弹出栈
		printf("=%f\n", b);//打印
		//for循环重置flag与压入结束操作符；
		flag = 0;
		Push(Optr, '#');
	}
	return OK;
}