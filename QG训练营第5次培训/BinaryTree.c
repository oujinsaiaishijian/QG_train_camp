#include "BinaryTree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 *  @name        : Status InitBiTree(BiTree T);
 *  @description : ����ն�����T
 *  @param       : �����������T
 */
Status InitBiTree(BiTree *T){
	*T = (BiTNode*)malloc(sizeof(BiTNode));
	if(T==NULL){
		return ERROR;
	}
	(*T)->lchild = NULL;
	(*T)->rchild = NULL; 
	return SUCCESS;
}


/**
 *  @name        : Status DestroyBiTree(BiTree T);
 *  @description : �ݻٶ�����T
 *  @param       : �����������T
 */
Status DestroyBiTree(BiTree T){
	if(T){
		if(T->lchild){
		DestroyBiTree(T->lchild);
	}else if(T->rchild){ 
		DestroyBiTree(T->rchild);
	}
		free(T);
		return SUCCESS;
		
	}else{
		return ERROR;
	}
}


/**
 *  @name        : Status CreateBiTree(BiTree T, char* definition);
 *  @description : ���������T
 *  @param       : �����������T, ��������������ַ���definition
 */
//����ǰ׺���ʽ 
Status CreateBiTree(BiTree T, char* definition){
	char ch = *definition;
	
	T->data = ch;

	if('0' <= T->data && T->data <= '9'){
		T->lchild = NULL;
		T->rchild = NULL;
	}else{
		T->lchild = (BiTree)malloc(sizeof(BiTNode));
		T->rchild = (BiTree)malloc(sizeof(BiTNode));
		CreateBiTree(T->lchild, definition+1);
		CreateBiTree(T->rchild, definition+1);
	}
}


Status visit (TElemType e){
		printf("%c\t",e);
}


/**
 *  @name        : Status PreOrderTraverse(BiTree T, Status (*visit)(TElemType e));
 *  @description : �������������T
 *  @param       : �����������T, �Խ��Ĳ�������visit
 */
Status PreOrderTraverse(BiTree T, Status (*visit)(TElemType e)){
	if(T==NULL){
		return ERROR;
	}else{
		visit(T->data);
		PreOrderTraverse(T->lchild,visit);
		PreOrderTraverse(T->rchild,visit);
	}
}

/**
 *  @name        : Status InOrderTraverse(BiTree T, Status (*visit)(TElemType e));
 *  @description : �������������T
 *  @param       : �����������T, �Խ��Ĳ�������visit
 */
Status InOrderTraverse(BiTree T, Status (*visit)(TElemType e)){
	if(T==NULL){
		return ERROR;
	}else{
		InOrderTraverse(T->lchild,visit);
		visit(T->data);
		InOrderTraverse(T->rchild,visit);
	}	
} 


/**
 *  @name        : Status PostOrderTraverse(BiTree T, Status (*visit)(TElemType e)));
 *  @description : �������������T
 *  @param       : �����������T, �Խ��Ĳ�������visit
 */
Status PostOrderTraverse(BiTree T, Status (*visit)(TElemType e)){
	if(T==NULL){
		return ERROR;
	}else{
		PostOrderTraverse(T->lchild, visit);
		PostOrderTraverse(T->rchild, visit);
		visit(T->data);
	}	
}


/**
 *  @name        : int Value(BiTree *T);
 *  @description : �Թ������ǰ׺���ʽ��������ֵ
 *  @param       : �����������T
 *  @note        : ���ڽ��ṹ�������ø�Tagֵ��־������������������������
 *                 �ɸ�����Ҫ�������Ӳ���.
 */
int Value(BiTree T){
	if('0'<=T->data&&T->data<='9'){
		return(T->data-'0');
	}else{
		switch(T->data){
			case'+':  
				return Value(T->lchild) + Value(T->rchild); 
				break;
			case'-':  
				return Value(T->lchild) - Value(T->rchild); 
				break;
			case'*':  
				return Value(T->lchild) * Value(T->rchild); 
				break;
			case'/':  
				return Value(T->lchild) / Value(T->rchild); 
				break;
		}
	}
}
