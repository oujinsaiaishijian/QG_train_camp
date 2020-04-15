#include "../head/LinkStack.h"
#include <stdlib.h>
#include <stdio.h>


Status initLStack(LinkStack *s){
	s->top = (LinkStackPtr)malloc(sizeof(LinkStackPtr));
	s->count = 0;
	if(s->top!=NULL){
		s->top->next = NULL;
	}
	return SUCCESS;
}


Status isEmptyLStack(LinkStack *s){
	if(s->top->next == NULL){
		return SUCCESS;
	}else{
		return ERROR;
	}
}


Status getTopLStack(LinkStack *s,ElemType *e){
	if(s->count == 0){
		printf("Õ»¿Õ");
		ERROR;
	}
	*e = s->top->data;
	printf("Õ»¶¥ÔªËØÎª£º%d\n",s->top->data);
	return SUCCESS;
}


Status clearLStack(LinkStack *s){
	s->count = 0;
	return SUCCESS;
}


Status destroyLStack(LinkStack *s){
	LinkStackPtr prev = s->top;
	LinkStackPtr rear = s->top->next;
	if(rear!=NULL){
		free(prev);
		prev = rear;
		rear = rear->next;
	}
	free(s);
	return SUCCESS;
}

 
Status LStackLength(LinkStack *s,int *length){
	if(*length = s->count){
	return SUCCESS;
}else{
	return ERROR;
	}
}


Status pushLStack(LinkStack *S,ElemType data){
	LinkStackPtr s = (LinkStackPtr)malloc(sizeof(StackNode));
	s->data = data;
	s->next = S->top;
	S->top = s;	
	S->count ++;
	return SUCCESS;
} 
 

Status popLStack(LinkStack *s,ElemType *data){
	LinkStackPtr p;
	
	if(isEmptyLStack(s)){
		return ERROR;
	}
	*data = s->top->data;
	p = s->top;
	s->top = s->top->next;
	free(p);
	s->count--;
	return SUCCESS;
}


