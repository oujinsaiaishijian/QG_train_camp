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
	printf("��������ı��ʽ��ע����#��β\n");
	gets(str1);
	int i = strlen(str1);
	char *t =&str1[i-1];
	if(*t!='#'){
				printf("\n��ı��ʽû����#��β,����������\n");
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
	
	
	printf("\n�ҳɹ�����");
	
	return 0;
	
	
}
