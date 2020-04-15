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

//中缀转后缀
void Change(SqStack *S,ElemType str1[],ElemType str2[]);

//后缀的计算 
void CalFunction(SqStack *S,char str[]); 

//基于数组的顺序栈
Status initStack(SqStack *s,int sizes);//初始化栈
Status isEmptyStack(SqStack *s);//判断栈是否为空
Status getTopStack(SqStack *s,ElemType *e); //得到栈顶元素
Status clearStack(SqStack *s);//清空栈
Status destroyStack(SqStack *s);//销毁栈
Status stackLength(SqStack *s,int *length);//检测栈长度
Status pushStack(SqStack *s,ElemType data);//入栈
Status popStack(SqStack *s,ElemType *data);//出栈




#endif 
