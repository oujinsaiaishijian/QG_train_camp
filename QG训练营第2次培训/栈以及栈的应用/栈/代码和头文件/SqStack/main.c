#include <stdio.h>
#include "../head/SqStack.h" 


int main(){
	int i,sizes;
	int data;
	SqStack S;
	printf("������һ�����ʵ�������������sizes��");
	scanf("%d",&sizes);
	initStack(&S,sizes);
  
  while(1){
  	
    printf("��ѡ�����в���\n");
		printf("1:��ջ����\n");
		printf("2:��ջ����\n");
		printf("3:�ж�ջ�Ƿ�Ϊ��\n");
		printf("4:ȡջ��Ԫ��\n");
		printf("5:������ջ\n");
		printf("6:�������ջ\n");
		printf("7:�˳�\n");
		scanf("%d",&i);
		
		switch(i){
							case 1:
									 printf("�������ջ��ElemType,");
									 scanf("%d", &data);
									 pushStack(&S, data);
									 printf("\n��ջ�ɹ���\n");
									 break;         
							case 2:popStack(&S, &data);
									 printf("��ջ��Ԫ����%d\n",data);
									 break;
							case 3:
									 if(isEmptyStack(&S)){
									 	printf("�ǵģ����ջ�ǿյ�\n");
									 }else{
									 	printf("�������ջ������\n");
									 } 
									 break; 
							case 4:
									 getTopStack(&S,&data);
									 printf("ջ����Ԫ����%d",data);
									 break;
						  case 5:
						  		 clearStack(&S);
						  		 break;
						  case 6:
						  		 destroyStack(&S);
						  		 break;
							case 7:
									 return 0;
							default:
							printf("�������,���������룡����\n");
							break;
        			}
					}
	printf("\n\n");
	system ("pause");
	return 0;
	
}
