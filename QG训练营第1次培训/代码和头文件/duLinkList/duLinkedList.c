#include "../head/duLinkedList.h"
#include <stdlib.h>
#include <stdio.h>

/**
 *  @name        : Status InitList_DuL(DuLinkedList *L)
 *	@description : initialize an empty linked list with only the head node
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status InitList_DuL(DuLinkedList *L) {
	*L = (DuLinkedList)malloc(sizeof(DuLinkedList));	
	if(!(*L)){
		return ERROR;
	}
	(*L)->next = NULL;
	(*L)->prior= NULL; 
	return SUCCESS;
}

/**
 *  @name        : void DestroyList_DuL(DuLinkedList *L)
 *	@description : destroy a linked list
 *	@param		 : L(the head node)
 *	@return		 : status//这里应该是void 
 *  @notice      : None
 */
void DestroyList_DuL(DuLinkedList *L) {
	DuLinkedList temp,prev=(*L)->next;
	while(temp){
		temp = prev->next;
		free(prev);
		prev = temp;
	}
	*L = NULL;
}

/**
 *  @name        : Status InsertBeforeList_DuL(DuLNode *p, LNode *q)
 *	@description : insert node q before node p
 *	@param		 : p, q
 *	@return		 : status
 *  @notice      : None
 */
Status InsertBeforeList_DuL(DuLNode *p, DuLNode *q) {
	if(p == NULL||q == NULL||p->prior == NULL){
	 return ERROR;
	 } 
	q->next = p;
	q->prior = p->prior;
	p->prior->next = q;
	p->prior = q;
	return SUCCESS;
}

/**
 *  @name        : Status InsertAfterList_DuL(DuLNode *p, DuLNode *q)
 *	@description : insert node q after node p
 *	@param		 : p, q
 *	@return		 : status
 *  @notice      : None
 */
Status InsertAfterList_DuL(DuLNode *p, DuLNode *q) {
	if(p == NULL||q == NULL||p->prior == NULL){
	 return ERROR;
	 } 
	q->next = p->next; 
	q->prior=p;
	p->next->prior = q;
	p->next=q; 	
	return SUCCESS;
}

/**
 *  @name        : Status DeleteList_DuL(DuLNode *p, ElemType *e)
 *	@description : delete the first node after the node p and assign its value to e
 *	@param		 : p, e
 *	@return		 : status
 *  @notice      : None
 */
Status DeleteList_DuL(DuLNode *p, ElemType *e) {
	if(p->prior == NULL&&p->next == NULL){
	 return ERROR;
	 }
	*e = p->next->data;
	DuLNode *q = p->next;
	p->next = p->next->next;
	q->next->prior = p;
	free(q);
	return SUCCESS;
}

/**
 *  @name        : void TraverseList_DuL(DuLinkedList L, void (*visit)(ElemType e))
 *	@description : traverse the linked list and call the funtion visit
 *	@param		 : L(the head node), visit
 *	@return		 : Status
 *  @notice      : None
 */
void TraverseList_DuL(DuLinkedList L, void (*visit)(ElemType e)) {
	DuLNode*p = L->next;
	while(p){
		visit(p->data);
		p=p->next;
	}
}
void visit(ElemType e){
	printf("%d\t",e);
} 
