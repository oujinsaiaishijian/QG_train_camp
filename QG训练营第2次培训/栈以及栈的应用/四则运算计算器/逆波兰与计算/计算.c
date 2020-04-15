#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<ctype.h>

#define INITSIZE  20
#define INCREMENT 10
#define MAXBUFFER 10
#define LEN   sizeof(Elemtype2)

/*ջ�Ķ�̬����˳��洢�ṹ*/
typedef double Elemtype2;
typedef struct{
	Elemtype2 *base;
	Elemtype2 *top;
	int StackSize; 
}SqStack;

void InitStack(SqStack *S)
{
	S->base=(Elemtype2*)malloc(sizeof(Elemtype2)*INITSIZE);
	S->top=S->base;
	S->StackSize=INITSIZE;
}

void PushStack(SqStack *S,Elemtype2 e)
{
	if(S->top - S->base >= S->StackSize)
	{
		S->base=(Elemtype*)realloc(S->base,(S->StackSize+INCREMENT)*LEN);
		assert(S->base !=NULL);
		S->top=S->base+S->StackSize;
		S->StackSize+=INCREMENT;
	}
	*S->top =e;
	 S->top++;
}

void PopStack(SqStack *S,Elemtype *e)
{
	*e=*--S->top;
}

void CalFunction(SqStack *S,char str[])
{
	Elemtype number,e,d;
	char arr[MAXBUFFER];
	int i=0,j=0;
	
	InitStack(S);
	
	while(str[i]!='\0')
	{
		while(isdigit(str[i])||str[i]=='.')  //��������
		{
			arr[j++]=str[i++];
			arr[j]='\0';
			
			if( j >= MAXBUFFER )
			{
				printf("���뵥�����ݹ���\n");
				return ;
			}
			if(str[i]==' ')
			{
				number=atof(arr);    //����atof�����������ַ�ת��Ϊdouble������
				PushStack(S,number); //��ת����������ѹջ
				j=0;
				break;
			}
		}
		
		switch(str[i])
		{
			case '+':
				PopStack(S,&e);
				PopStack(S,&d);
				PushStack(S,d+e);
				break;
			case '-':
				PopStack(S,&e);
				PopStack(S,&d);
				PushStack(S,d-e);
				break;
			case '*':
				PopStack(S,&e);
				PopStack(S,&d);
				PushStack(S,d*e);
				break;
			case '/':
				PopStack(S,&e);
				PopStack(S,&d);
				if(e == 0)
				{
					printf("���������ĸΪ�㣡\n");
					return ;
				}
				PushStack(S,d/e);
				break;
		}
		i++; 	
	}
	
	PopStack(S,&e);
	printf("������Ϊ��%lf",e);	
}

int main()
{
	char str[100];
	SqStack S;
	printf("�밴�沨�����ʽ��������,ÿ������֮���ÿո����:");
	gets(str);
	CalFunction(&S,str);
	return 0;
}


// ������� 5 - (6 + 7) * 8 + 9 / 4

// ���룺5 8 6 7 + * - 9 4 / + # 

// ����� - 96.750000

