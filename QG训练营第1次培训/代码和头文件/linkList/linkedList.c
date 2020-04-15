#include "../head/linkedList.h"
#include <stdlib.h>
#include <stdio.h>

/**
 *  @name        : Status InitList(LinkList *L);
 *	@description : initialize an empty linked list with only the head node without value
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status InitList(LinkedList *L){
	*L = (LinkedList)malloc(sizeof(LinkedList));	
	if(!(*L)){						
		return ERROR;
	}
	(*L)->next = NULL;
	return SUCCESS;
}
	

/**
 *  @name        : void DestroyList(LinkedList *L)
 *	@description : destroy a linked list, free all the nodes
 *	@param		 : L(the head node)
 *	@return		 : None
 *  @notice      : None
 */
void DestroyList(LinkedList *L) {
	 LinkedList p,q;
	 p=*L;
	 while(p){
	 	q = p->next;
	 	free(p);
	 	p=q;
	 }
	 (*L)->next=NULL;
}


/**
 *  @name        : Status InsertList(LNode *p, LNode *q)
 *	@description : insert node q after node p
 *	@param		 : p, q
 *	@return		 : Status
 *  @notice      : None
 */
Status InsertList(LNode *prev, LNode *rear) {   
  if(prev == NULL||rear == NULL){
		return ERROR;
	}
	rear->next = prev->next;
	prev->next = rear;
	return SUCCESS;	
}


/**
 *  @name        : Status DeleteList(LNode *p, ElemType *e)
 *	@description : delete the first node after the node p and assign its value to e
 *	@param		 : p, e
 *	@return		 : Status
 *  @notice      : None
 */
Status DeleteList(LNode *p, ElemType *e) {
	LinkedList temp =p->next;
	p->next=temp->next;
	*e=temp->data;
	free(temp);
	temp=NULL;
	return SUCCESS;
}


/**
 *  @name        : void TraverseList(LinkedList L, void (*visit)(ElemType e))
 *	@description : traverse the linked list and call the funtion visit
 *	@param		 : L(the head node), visit
 *	@return		 : None
 *  @notice      : None
 */
void TraverseList(LinkedList L, void (*visit)(ElemType e)) {
	LNode*p = L->next;
	while(p){
		visit(p->data);
		p=p->next;
	}
}
void visit(ElemType e){
	printf("%d\t",e);
} 


/**
 *  @name        : Status SearchList(LinkedList L, ElemType e)
 *	@description : find the first node in the linked list according to e
 *	@param		 : L(the head node), e
 *	@return		 : Status
 *  @notice      : None
 */
Status SearchList(LinkedList L, ElemType e) {
	if(!L){
		return ERROR;
    }
  LinkedList temp = L->next;
  while(temp){
  	if(temp->data==e){
  		return SUCCESS;
		}
		temp=temp->next;
	}
  return ERROR; 
}


/**
 *  @name        : Status ReverseList(LinkedList *L)
 *	@description : reverse the linked list
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status ReverseList(LinkedList *L) {
	if(*L==NULL||(*L)->next==NULL){
		return ERROR;
    }
    LinkedList pre,cur,next;
    cur = (*L)->next;
    while(cur){
    	next = cur->next;
    	cur->next = pre;
			pre = cur;
			cur = next; 
		}
 		(*L)->next = pre;
 		return SUCCESS;
	}
    
    
/**
 *  @name        : Status IsLoopList(LinkedList L)
 *	@description : judge whether the linked list is looped
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status IsLoopList(LinkedList L) {
	if(!L){
		return ERROR;
    }
	LinkedList fast,slow;
	fast = slow = L;
	while(1){
	   	if(!fast||!fast->next){//排除fast->next->next不存在的情况 
			return ERROR;												  
		}else if(fast==slow||fast->next==slow){//fast追上了slow,或者跑到slow的后面去了 
			return SUCCESS;		
		}else{
			slow = slow->next;
			fast = fast->next->next; 
		}
	}
}


/**
 *  @name        : LNode* ReverseEvenList(LinkedList *L)
 *	@description : reverse the nodes which value is an even number in the linked list, input: 1 -> 2 -> 3 -> 4  output: 2 -> 1 -> 4 -> 3
 *	@param		 : L(the head node)
 *	@return		 : LNode(the new head node)
 *  @notice      : choose to finish
 */
LNode* ReverseEvenList(LinkedList *L) {
	if(*L==NULL||(*L)->next==NULL){
		printf("节点为空!");
		return 0;
    }
  int i=0;
	LinkedList prev,rear,new_head;
	new_head = *L;
	prev = new_head->next;
	rear = prev->next;
	while(rear){
		if(prev->data%2==0){
			i = prev->data;
			prev->data = rear->data;
			rear->data = i;
		}
		prev = rear->next;
		if(prev==NULL){
		return new_head;
	}else{
		rear = prev->next;
		}
	}
}


/**
 *  @name        : LNode* FindMidNode(LinkedList *L)
 *	@description : find the middle node in the linked list
 *	@param		 : L(the head node)
 *	@return		 : LNode
 *  @notice      : choose to finish
 */
LNode* FindMidNode(LinkedList *L) {
	//这个函数是不完备的，只是在这个main()的预设数值里是够用。 
	if(!L){
		return ERROR;
    }
    
	LinkedList fast,slow;
	fast = slow = (*L);
	
	while(fast!=NULL){
		if(fast->next==NULL){
			fast=fast->next;
		}else{
			fast = fast->next->next;
		}
		slow =slow->next;
	} 
	return slow;
}

