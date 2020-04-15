#include "AQueue.h" 
#include <stdlib.h>
#include <string.h>


void InitAQueue(AQueue *Q){
	int i;
	for(i=0;i<MAXQUEUE;i++){
		Q->data[i] = (void *)malloc(Q->data_size);
	}
	Q->front = 0;
	Q->rear = 0;
	return;
}


void DestoryAQueue(AQueue *Q){
	int i;
	for(i=0;i < MAXQUEUE;i++){
		free(Q->data[i]);
	}
	return;
}


Status IsFullAQueue(const AQueue *Q){
	if(Q->front==(Q->rear+1)%MAXQUEUE){
		return TRUE;
	}else{
		return FALSE;
	}
}


Status IsEmptyAQueue(const AQueue *Q){
	if(Q->front==Q->rear){
		return TRUE;
	}else{
		return FALSE;
	}
}


int LengthAQueue(AQueue *Q){
	return (Q->rear - Q->front + MAXQUEUE) % MAXQUEUE;
}


Status EnAQueue(AQueue *Q, void *data){
	if(IsFullAQueue(Q)){
		return FALSE;
	}
	Q->rear = (Q->rear+1) % MAXQUEUE;
	memcpy(Q->data[Q->rear],data,Q->data_size);
	return TRUE;
}


Status DeAQueue(AQueue *Q){
	if(IsEmptyAQueue(Q)){
		return FALSE; 
	}
	Q->front = (Q->front + 1) % MAXQUEUE;
	return TRUE;
}


void ClearAQueue(AQueue *Q){
	if(IsEmptyAQueue(Q)){
		return;
	}
	Q->front = 0;
	Q->rear = 0;
	return;
}


Status GetHeadAQueue(AQueue *Q, void *e){
	if(IsEmptyAQueue(Q)){
		return FALSE;
	}
	int i = Q->front;
	i = (i + 1) % MAXQUEUE;
	memcpy(e, Q->data[i],Q->data_size);
	return TRUE;
}


Status TraverseAQueue(const AQueue *Q, void (*aPrint)(void *q, int size)){
	if(IsEmptyAQueue(Q)){
		return FALSE;
	}
	int i;
	i = Q->front + 1;
	while(i<=(Q->rear-Q->front+MAXQUEUE)%MAXQUEUE){
		aPrint(Q->data[i],Q->data_size);
		i = (i+1) % MAXQUEUE;
	}
	printf("\n");
	return TRUE;
}


void APrint(void *q,int size){
	if(size == sizeof(double)){
		printf("%lf\t",*(double*)q);
	}else if(size == sizeof(char)){
		printf("%c\t",*(char*)q);
	}else if(size == sizeof(int)){
		printf("%d\t",*(int*)q);
	}
}	
