#include <stdio.h>
#include "../head/LinkStack.h" 



int main(){
	int i;
	int data;
  LinkStack S; 
  initLStack(&S);
  
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
									 scanf("%d",&data);
									 pushLStack(&S, data);
									 printf("\n进栈成功！\n");
									 break;         
							case 2:popLStack(&S,&data);
									 printf("出栈的元素是%d\n",data);
									 break;
							case 3:
									 if(isEmptyLStack(&S)){
									 	printf("是的，这个栈是空的\n");
									 }else{
									 	printf("不，这个栈并不空\n");
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
							printf("输入错误,请重新输入！！！\n");
							break;
        			}
					}
	printf("\n\n");
	system ("pause");
	return 0;
	
}

