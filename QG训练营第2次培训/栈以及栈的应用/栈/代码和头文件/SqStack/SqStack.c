#include <stdio.h>
#include <stdlib.h>
#include "../head/SqStack.h" 


Status initStack(SqStack *s,int sizes){
	s->elem = (int*)malloc(sizeof(ElemType)*sizes);
	s->size = sizes;
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
	return SUCCESS;
}


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


