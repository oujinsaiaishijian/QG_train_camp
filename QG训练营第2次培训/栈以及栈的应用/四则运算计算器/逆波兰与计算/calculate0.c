#include <stdlib.h>
#include <stdio.h>
//ctype用于测试字符是否属于特定的字符类别
#include <ctype.h>
#include "calculate0.h"


/*中缀转后缀函数*/
void Change(SqStack *S,ElemType str1[],ElemType str2[]){
	
	int i = 0;
	int j = 0;
	ElemType e;
	
	while(str1[i]!='#'){
		
		/*过滤数字字符，直接输出，直到下一位不是数字字符打印空格,然后跳出循环 */
		while(isdigit(str1[i])){
			str2[j] = str1[i];
			j++;
			printf("%c",str1[i++]);
			if(!isdigit(str1[i])){
				printf(" ");
			}
		}
		
		/*加减运算符优先级最低，如果栈顶元素为空则直接入栈，否则将栈中存储
		的运算符全部弹栈，如果遇到左括号则停止，将弹出的左括号重新压栈，因为左
		括号要和右括号匹配时弹出，这个后面单独讨论。弹出后将优先级低的运算符压入栈中*/
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
		
		/*当遇到右括号时，把括号里剩余的运算符弹出，直到匹配到左括号为止
		左括号只弹出不打印（右括号也不压栈）*/
		else if(str1[i]==')'){
			popStack(S,&e);
			while(e!='('){
				str2[j] = e;
				j++;
				printf("%c ",e);
				popStack(S,&e);
				}
		}
		
		/*乘、除、左括号都是优先级高的，直接压栈*/
		else if(str1[i]=='*'||str1[i]=='/'||str1[i]=='('){
			pushStack(S,str1[i]);
		}else if(str1[i]=='#'){
			break;
		}else{
			printf("\n输入格式错误！\n");
			return ;
		}
		i++;
	}
	
	/*最后把栈中剩余的运算符依次弹栈打印*/
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


