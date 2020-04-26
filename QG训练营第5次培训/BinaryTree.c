#include "BinaryTree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 *  @name        : Status InitBiTree(BiTree T);
 *  @description : 构造空二叉树T
 *  @param       : 二叉树根结点T
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
 *  @description : 摧毁二叉树T
 *  @param       : 二叉树根结点T
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
 *  @description : 构造二叉树T
 *  @param       : 二叉树根结点T, 二叉树先序遍历字符串definition
 */
//创建前缀表达式 
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
 *  @description : 先序遍历二叉树T
 *  @param       : 二叉树根结点T, 对结点的操作函数visit
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
 *  @description : 中序遍历二叉树T
 *  @param       : 二叉树根结点T, 对结点的操作函数visit
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
 *  @description : 后序遍历二叉树T
 *  @param       : 二叉树根结点T, 对结点的操作函数visit
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
 *  @description : 对构造出的前缀表达式二叉树求值
 *  @param       : 二叉树根结点T
 *  @note        : 可在结点结构体中设置个Tag值标志数字与操作符来构造二叉树，
 *                 可根据需要自行增加操作.
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
