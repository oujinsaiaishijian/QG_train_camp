#include "BinaryTree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(){
	
	//����һ��ָ�뺯�� 
	Status (*visit2)(TElemType e);
	//�Ѻ���Visit����ָ�����visit��ʹvisitָ��Visit 
	visit2 = visit;
	
	int maxsize = 20;
	int n; 
	TElemType definition[maxsize];
	printf("������һ���򵥵�ǰ׺���ʽ\n\n");
	scanf("%s",definition);
	printf("%c\n\n",definition[0]);
	printf("hello"); 
	BiTree B;
	InitBiTree(&B);
	CreateBiTree(B,definition);
	
	printf("ǰ������ǣ�\n");
	PreOrderTraverse(B,visit2);
	printf("\n��������ǣ�\n");
	InOrderTraverse(B,visit2);
	printf("\n��������ǣ�\n");
	PostOrderTraverse(B, visit2);
	
	
	n = Value(B);
	printf("\n�������ǣ�%d\n",n);
	
	return 0;
}
