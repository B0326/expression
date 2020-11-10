#include "stack.h"


Status InitStack(SqStack& s)//������ջ��
{
	s.base = (SElemType*)malloc(SIZE * sizeof(SElemType));//����һ�������Ŀռ�Ϊջ�洢���ݵĿռ�
	if (!s.base) return FALSE;
	s.top = s.base;//��ջ������ջ�ױ�ʾΪ��ջ
	s.stacksize = 100;//ջ�Ŀռ��С
	return OK;
}
Status GetTop(SqStack s) //��ò���ջ��Ԫ��Ϊ����ֵ
{
	if (s.top == s.base) return ERROR;	
	 return *(s.top - 1);	 //����ջ��Ԫ��
}
Status Push(SqStack& s, SElemType e)//����eΪ�µ�ջ��Ԫ�أ�
{
	if (s.top - s.base == s.stacksize) {
		s.base = (SElemType*)realloc(s.base, (s.stacksize + SIZE) * sizeof(SElemType));
		//����ջ�Ŀռ�
		if (!s.base) exit(OVERFLOW);
		s.top = s.base + s.stacksize;
		s.stacksize += SIZE;
	}
	*s.top = e;//����Ԫ��eΪջ��Ԫ��
	s.top = s.top + 1;//ջ��ָ��ָ���ջ����һ���յĿռ䣻
	return OK;
}
Status Pop(SqStack& s, SElemType &e) //������ջ��ջ��Ԫ��
{
	if (s.top == s.base) return ERROR;
	s.top = s.top - 1;//ջ��
	e = *s.top;
	return OK;
}
Status Clear(SqStack& s) //�ͷ�ջ
{
	free(s.base);
	s.base = NULL;
	s.top=NULL;
	return OK;
}

Status OptorCompare(char ch, SqStack s)//��������ȼ��ж�
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
bool IsNumber(char ch) //�ж������ֻ��������
{
	if (ch >= '0' && ch <= '9') return true;
	else return false ;
}
Status Operate(double  a, double b, char theta)//�Ӽ��˳�
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