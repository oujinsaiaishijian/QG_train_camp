#include <stdio.h>
#include "../head/LinkStack.h" 



int main(){
	int i;
	int data;
  LinkStack S; 
  initLStack(&S);
  
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
									 scanf("%d",&data);
									 pushLStack(&S, data);
									 printf("\n��ջ�ɹ���\n");
									 break;         
							case 2:popLStack(&S,&data);
									 printf("��ջ��Ԫ����%d\n",data);
									 break;
							case 3:
									 if(isEmptyLStack(&S)){
									 	printf("�ǵģ����ջ�ǿյ�\n");
									 }else{
									 	printf("�������ջ������\n");
									 } 
									 break; 
							case 4:
									 getTopLStack(&S,&data);
									 break;
						  case 5:
						  		 clearLStack(&S);
						  		 break;
						  case 6:
						  		 destroyLStack(&S);
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

