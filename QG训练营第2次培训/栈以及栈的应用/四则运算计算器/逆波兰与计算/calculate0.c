#include <stdlib.h>
#include <stdio.h>
//ctype���ڲ����ַ��Ƿ������ض����ַ����
#include <ctype.h>
#include "calculate0.h"


/*��׺ת��׺����*/
void Change(SqStack *S,ElemType str1[],ElemType str2[]){
	
	int i = 0;
	int j = 0;
	ElemType e;
	
	while(str1[i]!='#'){
		
		/*���������ַ���ֱ�������ֱ����һλ���������ַ���ӡ�ո�,Ȼ������ѭ�� */
		while(isdigit(str1[i])){
			str2[j] = str1[i];
			j++;
			printf("%c",str1[i++]);
			if(!isdigit(str1[i])){
				printf(" ");
			}
		}
		
		/*�Ӽ���������ȼ���ͣ����ջ��Ԫ��Ϊ����ֱ����ջ������ջ�д洢
		�������ȫ����ջ�����������������ֹͣ��������������������ѹջ����Ϊ��
		����Ҫ��������ƥ��ʱ������������浥�����ۡ����������ȼ��͵������ѹ��ջ��*/
		if(str1[i]=='+'||str1[i]=='-'){
			if(isEmptyStack(S)){
				pushStack(S,str1[i]);
			}
			else{
				do{
					popStack(S,&e);
					if(e=='('){
						pushStack(S,e);
					}
					else{
						str2[j] = e;
						j++;
						printf("%c ",e);
					}
				}while( !isEmptyStack(S) && e != '(');
					
					pushStack(S,str1[i]);
				}
		}
		
		/*������������ʱ����������ʣ��������������ֱ��ƥ�䵽������Ϊֹ
		������ֻ��������ӡ��������Ҳ��ѹջ��*/
		else if(str1[i]==')'){
			popStack(S,&e);
			while(e!='('){
				str2[j] = e;
				j++;
				printf("%c ",e);
				popStack(S,&e);
				}
		}
		
		/*�ˡ����������Ŷ������ȼ��ߵģ�ֱ��ѹջ*/
		else if(str1[i]=='*'||str1[i]=='/'||str1[i]=='('){
			pushStack(S,str1[i]);
		}else if(str1[i]=='#'){
			break;
		}else{
			printf("\n�����ʽ����\n");
			return ;
		}
		i++;
	}
	
	/*����ջ��ʣ�����������ε�ջ��ӡ*/
	while(!isEmptyStack(S)){
		popStack(S,&e);
		str2[j] = e;
		j++;
		printf("%c ",e);
	}
	
}
/*
void CalFunction(SqStack *S,char str[]){
	ElemType e, d;
	char string[25];
	while(str[i]!='\0'){
		
		while(isdigit(str[i])){
			 pushStack(S,str[i]);
			 i++;
			 }
	  
	  switch(str[i]){
	  	case '+':
	  		popStack(S,&e);
	  		popStack(S,&d);
	  		
	  		
	  		
	  		break;
  		case '-':
  			
  			
  			break;
 			case '*':
 				
 				
 				break;
				
			case '/':
				
				
				break;
 			
	  	
		}


}
*/

Status stackLength(SqStack *s,int *length){
	*length = s->top + 1;
	return SUCCESS;
}


Status pushStack(SqStack *s,ElemType data){
	if(s->top==s->size-1){
		return ERROR;
	}
	s->top ++;
	s->elem[s->top] = data;
	return SUCCESS;
}


Status popStack(SqStack *s,ElemType *data){
	if(s->top==-1){
		return ERROR;
	}
	*data = s->elem[s->top];
	s->top--;
	return SUCCESS;
}


Status initStack(SqStack *s,int a){
	s->elem = (ElemType*)malloc(sizeof(ElemType)*a);
	s->size = a;
	s->top = -1;
	return SUCCESS;
}


Status isEmptyStack(SqStack *s){
	if(s->top==-1){
		return SUCCESS;
	}else{
		return ERROR;
	}
}


Status getTopStack(SqStack *s,ElemType *e){
	if(s->top==-1){
		return ERROR;
	}
	*e = s->elem[s->top];
	return SUCCESS;
}


Status clearStack(SqStack *s){
	if(s->top==-1){
		return ERROR;
	}
	s->top = -1;
	return SUCCESS;
}


Status destroyStack(SqStack *s){
	free(s->elem);
	s->elem = NULL;
	free(s); 
	return SUCCESS;
}


