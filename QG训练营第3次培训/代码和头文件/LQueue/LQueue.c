#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LQueue.h"


void InitLQueue(LQueue *Q){
	Node *p = (Node *)malloc(sizeof(Node));
	p->next = NULL;
	Q->front = p;
	Q->rear = p;
	return;
}


void DestoryLQueue(LQueue *Q){
	if(IsEmptyLQueue(Q)){
		return;
	}
	ClearLQueue(Q);
	free(Q->front);
	free(Q->rear);
}


Status IsEmptyLQueue(const LQueue *Q){
	if(Q->front==Q->rear){
		return TRUE;
	}else{
		return FALSE;
	}
}


Status GetHeadLQueue(LQueue *Q, void *e){
	if(IsEmptyLQueue(Q)){
		return FALSE;
	}
	memcpy(e, Q->front->next->data, Q->data_size);
}


int LengthLQueue(LQueue *Q){
	int length;
	Node *p = (Node *)malloc(sizeof(Node));
	p = Q->front;
	for(length=0;p!=Q->rear;length++){
		p = p->next;
	}
	return length;
}


Status EnLQueue(LQueue *Q, void *data){
	Node *p = (Node *)malloc(sizeof(Node));
	p->data = malloc(sizeof(Q->data_size));
	memcpy(p->data,data,Q->data_size);
	p->next = NULL;
	Q->rear->next = p;
	Q->rear = p;
	return TRUE;
}


Status DeLQueue(LQueue *Q){
	if(IsEmptyLQueue(Q)){
		return FALSE;
	}
	Node *p =(Node *)malloc(sizeof(Node));
	p = Q->front->next;
	Q->front->next = p->next;
	if(NULL==Q->front->next){
		Q->rear = Q->front; 
	}
	free(p);
	return TRUE;
}


void ClearLQueue(LQueue *Q){
	if(IsEmptyLQueue(Q)){
		return;
	}
	Node *p,*q;
	Q->rear = Q->front;
	p = Q->front->next;
	while(NULL!=p){
		q = p;
		p = p->next;
		free(q);
	} 
	free(p);
	return;
}


Status TraverseLQueue(const LQueue *Q, void (*lPrint)(void *q,int size)){
	if(IsEmptyLQueue(Q)){
		return FALSE;
	}
	Node *p = malloc(Q->data_size);
	p = Q->front->next;
	while(p!=NULL){
		lPrint(p->data,Q->data_size);
		p = p->next;
	} 
	printf("\n");
	return TRUE;
}


void LPrint(void *q,int size){
	printf("\n");
	if(size == sizeof(double)){
		printf("%lf\t",*(double*)q);
	}else if(size == sizeof(char)){
		printf("%c\t",*(char*)q);
	}else if(size == sizeof(int)){
		printf("%d\t",*(int*)q);
	}
}
