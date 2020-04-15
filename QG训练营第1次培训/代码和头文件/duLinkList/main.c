#include "../head/duLinkedList.h"
#include <stdlib.h>
#include <stdio.h>

void visit(ElemType e);

int main(){
//preparing the data we need
	int a[4]={1,2,3,5};
//preparing the variable we need
	DuLinkedList L;
	DuLinkedList prev,rear,temp;
	int i;
	
//1.initializing	
//ע��Ҫ��&L��ֵ�� 
	if(SUCCESS==InitList_DuL(&L)){
		printf("��ʼ��ͷ�ڵ�ɹ�,���濪ʼ������������ӡ\n\n"); 
	}else{
		printf("��ʼ��ͷ�ڵ�ʧ�ܡ�");
		return 0;
	}
	//��prevָ��ͷ�ڵ㣬Ϊ����Ĳ�����׼�� 
	prev = L;
	
	
//2. InsertList the data
	for(i=0;i<4;i++){
		if((rear = (DuLinkedList)malloc(sizeof(DuLNode)))!=NULL){
			rear->prior = prev;
			rear->data = a[i];
			rear->next = NULL;
		}else{
			printf("�����½ڵ�ʱ���ڴ�����ʧ�ܣ�");
			return 0;
		}
		prev->next = rear;
		prev = prev->next;
	}	
  getch();
	
//3. showing
	//����һ��ָ�뺯�� 
	void (*visit2)(ElemType e);
	//�Ѻ���Visit����ָ�����visit��ʹvisitָ��Visit 
	visit2 = visit;
	//ͨ������ָ�����Visit,�������ӡ���� 
	TraverseList_DuL(L,visit2); 
	getch();

//4.Inserting
 printf("�ţ���϶�ע�⵽���м��һ��4�������ǰ�4���ȥ�ɡ�\n\n");
 //preparing the node
 temp = (DuLinkedList)malloc(sizeof(DuLNode));
 temp->data = 4;
 temp->next = temp->prior=NULL;
 //finding the node before
	prev = L;
	i=0;
	do{
		prev=prev->next;
		i++;
	}while(i<3);
 //InsertingAfter
 InsertAfterList_DuL(prev,temp);
 getch();
 TraverseList_DuL(L,visit2);
 printf("\n\n");
 //InsertingBefore
 prev = L->next;
 temp = (DuLinkedList)malloc(sizeof(DuLNode));
 temp->data = 41;
 temp->next = temp->prior=NULL;
 InsertBeforeList_DuL(prev,temp); 
 TraverseList_DuL(L,visit2);
 //delecting a node
 prev = L;
 printf("\n\n��ע�⵽����Ϲ�Ž�ȥ��һ��dataΪ41�Ľڵ㣬��Ϊ��Ҫ��delectlist_dul\n\n");
 i=-1;
 DeleteList_DuL(prev,&i);
 printf("ɾ���ڵ��data��%d\n\n",i);
 TraverseList_DuL(L,visit2); 
 printf("��������\n\n");
 DestroyList_DuL(&L);
 printf("û����ллʦ��");
 getch();
 return 0;
}


void introducing(){
	printf("Owo:�����Ǽ�ʵ��˫������Ĳ���\n");
	getch();
	
}
