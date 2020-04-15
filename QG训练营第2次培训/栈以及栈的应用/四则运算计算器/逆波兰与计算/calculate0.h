#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#define MAXBUFFER 10

typedef enum Status 
{
	ERROR = 0, SUCCESS = 1
} Status;

typedef char ElemType;

typedef struct SqStack 
{
	ElemType *elem;
	int top;
	int size;
} SqStack;

//��׺ת��׺
void Change(SqStack *S,ElemType str1[],ElemType str2[]);

//��׺�ļ��� 
void CalFunction(SqStack *S,char str[]); 

//���������˳��ջ
Status initStack(SqStack *s,int sizes);//��ʼ��ջ
Status isEmptyStack(SqStack *s);//�ж�ջ�Ƿ�Ϊ��
Status getTopStack(SqStack *s,ElemType *e); //�õ�ջ��Ԫ��
Status clearStack(SqStack *s);//���ջ
Status destroyStack(SqStack *s);//����ջ
Status stackLength(SqStack *s,int *length);//���ջ����
Status pushStack(SqStack *s,ElemType data);//��ջ
Status popStack(SqStack *s,ElemType *data);//��ջ




#endif 
