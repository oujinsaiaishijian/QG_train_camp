#include <stdio.h>
#include "../head/SqStack.h" 


int main(){
	int i,sizes;
	int data;
	SqStack S;
	printf("请输入一个合适的整数，用来做sizes：");
	scanf("%d",&sizes);
	initStack(&S,sizes);
  
  while(1){
  	
    printf("请选择下列操作\n");
		printf("1:进栈操作\n");
		printf("2:出栈操作\n");
		printf("3:判断栈是否为空\n");
		printf("4:取栈顶元素\n");
		printf("5:清空这个栈\n");
		printf("6:销毁这个栈\n");
		printf("7:退出\n");
		scanf("%d",&i);
		
		switch(i){
							case 1:
									 printf("请输入进栈的ElemType,");
									 scanf("%d", &data);
									 pushStack(&S, data);
									 printf("\n进栈成功！\n");
									 break;         
							case 2:popStack(&S, &data);
									 printf("出栈的元素是%d\n",data);
									 break;
							case 3:
									 if(isEmptyStack(&S)){
									 	printf("是的，这个栈是空的\n");
									 }else{
									 	printf("不，这个栈并不空\n");
									 } 
									 break; 
							case 4:
									 getTopStack(&S,&data);
									 printf("栈顶的元素是%d",data);
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
							printf("输入错误,请重新输入！！！\n");
							break;
        			}
					}
	printf("\n\n");
	system ("pause");
	return 0;
	
}
