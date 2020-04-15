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
		printf("��ѡ������Ҫ���еĶ�����ʽ��\n");
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
			printf("\n�������,���������롣\n");
		}
	}while(1);
	 
	system("cls");
	
	while(1){
	switch(menu()){
		case 1:
				printf("���еĳ���Ϊ%d",LengthAQueue(&Q));
				break;
		case 2:
				//datasize = malloc(sizeof(Q.data_size));
				printf("��Ҫ����ɶ\n"); 	
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
			printf("����������������룡");
			scanf("%d",&i); 
	}
}
	
	return 0;
}


int menu(){
	int i;
	printf("\n\n�����ɶ\n\n");
	printf("1:�鿴���г���\n2:���\n3������\n4:��������\n5����ȡ��ͷԪ��\n");
	printf("6:��ն���\n7:���ٶ���\n8���˳�\n"); 
	scanf("%d",&i);
	return i;
}


