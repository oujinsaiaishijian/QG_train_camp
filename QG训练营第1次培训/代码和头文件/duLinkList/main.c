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
//注意要用&L传值啊 
	if(SUCCESS==InitList_DuL(&L)){
		printf("初始化头节点成功,下面开始创建简单链表并打印\n\n"); 
	}else{
		printf("初始化头节点失败。");
		return 0;
	}
	//把prev指向头节点，为下面的插入作准备 
	prev = L;
	
	
//2. InsertList the data
	for(i=0;i<4;i++){
		if((rear = (DuLinkedList)malloc(sizeof(DuLNode)))!=NULL){
			rear->prior = prev;
			rear->data = a[i];
			rear->next = NULL;
		}else{
			printf("创建新节点时，内存申请失败！");
			return 0;
		}
		prev->next = rear;
		prev = prev->next;
	}	
  getch();
	
//3. showing
	//定义一个指针函数 
	void (*visit2)(ElemType e);
	//把函数Visit赋给指针变量visit，使visit指向Visit 
	visit2 = visit;
	//通过函数指针调用Visit,把链表打印出来 
	TraverseList_DuL(L,visit2); 
	getch();

//4.Inserting
 printf("呐，你肯定注意到了中间差一个4，那我们把4插进去吧。\n\n");
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
 printf("\n\n你注意到我又瞎放进去了一个data为41的节点，因为我要用delectlist_dul\n\n");
 i=-1;
 DeleteList_DuL(prev,&i);
 printf("删除节点的data是%d\n\n",i);
 TraverseList_DuL(L,visit2); 
 printf("销毁链表\n\n");
 DestroyList_DuL(&L);
 printf("没啦！谢谢师姐");
 getch();
 return 0;
}


void introducing(){
	printf("Owo:这里是简单实现双向链表的操作\n");
	getch();
	
}
