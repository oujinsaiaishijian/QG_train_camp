#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "calculate0.h"
#include <stdio.h>


int main(){
	
	ElemType str1[50];
	ElemType str2[50];
	SqStack S;
	initStack(&S, 50);
	
	//make sure that str ending with #
	while(1){
	printf("请输入你的表达式，注意以#结尾\n");
	gets(str1);
	int i = strlen(str1);
	char *t =&str1[i-1];
	if(*t!='#'){
				printf("\n你的表达式没有以#结尾,请重新输入\n");
			}else{
				break;
				}
	}
	
	Change(&S,str1,str2);
	
	printf("\n\n");
	printf("str2 = %s\n\n",str2); 
	int o = strlen(str2);
	char *oa =&str2[o];
	*oa = '\0';
	puts(str2);
	
	getch();
	
	
	printf("\n我成功了吗？");
	
	return 0;
	
	
}
