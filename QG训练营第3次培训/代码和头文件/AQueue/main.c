#include <stdio.h>
#include "AQueue.h" 
#include <stdlib.h>

int menu();

int main(){
	
	int i;
	void *datasize;
	void (*aPrint)(void *q,int size);
	aPrint = APrint;
	AQueue Q;

	InitAQueue(&Q);
	
	do{
		printf("请选择你想要进行的队列形式。\n");
		printf("1:double   2:char   3:int\n");
		scanf("%d",&i);
		
		if(i==1){
			Q.data_size = sizeof(double);
			break;
		}else if(i==2){
			Q.data_size = sizeof(char);
			break;
		}else if(i==3){
			Q.data_size = sizeof(int);
			break;
		}else{
			printf("\n输入错误,请重新输入。\n");
		}
	}while(1);
	 
	system("cls");
	
	while(1){
	switch(menu()){
		case 1:
				printf("队列的长度为%d",LengthAQueue(&Q));
				break;
		case 2:
				//datasize = malloc(sizeof(Q.data_size));
				printf("你要输入啥\n"); 	
			    if(Q.data_size == sizeof(double)){
			    	double a;
					scanf("%lf",&a);
					datasize = &a;				
				}else if(Q.data_size == sizeof(char)){
					char b;
					getchar();
					scanf("%c",&b);
					datasize = &b;
				}else if(Q.data_size == sizeof(int)){
					int c;
					scanf("%d",&c);
					datasize = &c;
				}
			    EnAQueue(&Q, datasize);
			    break;
		case 3:
				DeAQueue(&Q);
				break;
		case 4: 
				TraverseAQueue(&Q, aPrint);
				break;
		case 5:
				datasize = malloc(Q.data_size);
				GetHeadAQueue(&Q, datasize);
				if(Q.data_size == sizeof(double)){
					printf("%lf\t",*(double*)datasize);
				}else if(Q.data_size == sizeof(char)){
					printf("%c\t",*(char*)datasize);
				}else if(Q.data_size == sizeof(int)){
					printf("%d\t",*(int*)datasize);
				}
				break;
		case 6:
				ClearAQueue(&Q);
				break;
		case 7:
				DestoryAQueue(&Q);
				break;
		case 8:
				return 0;
		
		default:
			printf("输入错误，请重新输入！");
			scanf("%d",&i); 
	}
}
	
	return 0;
}


int menu(){
	int i;
	printf("\n\n你想干啥\n\n");
	printf("1:查看队列长度\n2:入队\n3：出队\n4:遍历队列\n5：获取队头元素\n");
	printf("6:清空队列\n7:销毁队列\n8：退出\n"); 
	scanf("%d",&i);
	return i;
}


