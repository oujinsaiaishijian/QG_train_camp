#include "BinaryTree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(){
	
	//定义一个指针函数 
	Status (*visit2)(TElemType e);
	//把函数Visit赋给指针变量visit，使visit指向Visit 
	visit2 = visit;
	
	int maxsize = 20;
	int n; 
	TElemType definition[maxsize];
	printf("请输入一个简单的前缀表达式\n\n");
	scanf("%s",definition);
	printf("%c\n\n",definition[0]);
	printf("hello"); 
	BiTree B;
	InitBiTree(&B);
	CreateBiTree(B,definition);
	
	printf("前序遍历是：\n");
	PreOrderTraverse(B,visit2);
	printf("\n中序遍历是：\n");
	InOrderTraverse(B,visit2);
	printf("\n后序遍历是：\n");
	PostOrderTraverse(B, visit2);
	
	
	n = Value(B);
	printf("\n计算结果是：%d\n",n);
	
	return 0;
}
