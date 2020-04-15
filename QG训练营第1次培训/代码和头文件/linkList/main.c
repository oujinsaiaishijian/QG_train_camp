#include <stdio.h>
#include <stdlib.h>
#include "../head/linkedList.h"

void introducing();
void visit(ElemType e);

int main(){
		
	introducing();
	
// prepare the variable we need
	LinkedList L;
	LinkedList prev,rear,temp;
	int i;
	
//preparing the data we need
	int a[7] = {1,2,3,5,6,7};
	
//1.initializing	
//ע��Ҫ��&L��ֵ�� 
	if(SUCCESS==InitList(&L)){
		printf("��ʼ��ͷ�ڵ�ɹ�,���濪ʼ������������ӡ\n\n"); 
	}else{
		printf("��ʼ��ͷ�ڵ�ʧ�ܡ�");
		return 0;
	}
	getch();
	temp = L;
	prev = L;
	
//2. InsertList the data
	for(i=0;i<6;i++){
		if((rear = (LinkedList)malloc(sizeof(LNode)))!=NULL){
			rear->data = a[i];
			rear->next = NULL;
		}else{
			printf("�����½ڵ�ʱ���ڴ�����ʧ�ܣ�");
			return 0;
		}
		prev->next = rear;
		prev = prev->next;
	}	
	
//3. showing
	
	//����һ��ָ�뺯�� 
	void (*visit2)(ElemType e);
	//�Ѻ���Visit����ָ�����visit��ʹvisitָ��Visit 
	visit2 = visit;
	//ͨ������ָ�����Visit,�������ӡ���� 
	TraverseList(L,visit2);
	printf("\n\n���ɣ���������һ���򵥵�������ô���棬����������һ���ڵ�,�һ��4������3��5���м�\n\n");
	//��prev����Ϊͷ�ڵ㣬��ǰ��������λ��Ȼ����temp���洢�������ݵĽڵ� 
	prev = L;
	i=0;
	do{
		prev=prev->next;
		i++;
	}while(i<3);
	temp = (LinkedList)malloc(sizeof(LNode));
	temp->next = NULL;
	temp->data = 4; 
//4.Inserting 
	InsertList(prev,temp);
	getch();
	TraverseList(L,visit2);
	getch();
	printf("\n\n�ǰɣ���Ȼ����Ҫ���������quq\n");
	getch();
	printf("��ô���Ϳ�ʼ��ѯ�������е�ɣ�"); 
	getch();
	system("cls");
//5.finding the midnode;
	printf("���ǵ������������:\n\n");
	TraverseList(L,visit2);
	getch();
	temp = FindMidNode(&L);
	printf("\n\nemmm,���������м�ڵ��dataӦ����%d",temp->data);
	getch();
	system("cls");
//6.loop topic
   printf("��ô����������ѭ������Ĳ����ˣ��������Ѿ���ĩָ����ӵ�ͷָ�����ˣ��ȱ���һ�¿���\n\n");
   getch();
	 rear->next = L->next;
	 for(i=0;i<20;i++){
	 	printf("%d  ",rear->data);
	 	rear = rear->next;
	 }
	 printf("\n\n�ǰɣ��Һ�����������һ��ѭ����������,����һ��islooplist�ɣ������Լ���Ϸ��\n\n"); 
	 getch();
	 if(SUCCESS==IsLoopList(rear)){
	 	printf("�ۣ�������������ѭ����Ҳ����������Ϸ��"); 
	 	getch();
	 }else{
	 	printf("���˺��ˣ����ھͲ����ˡ�"); 
	 }
	 printf("��������Ҫ�����⿪�ˣ����ǰ�dataΪ7�Ľڵ��next��ΪNULL\n\n");
	 do{
	 	rear=rear->next;
	 }while(rear->data!=7);
	 rear->next=NULL;
	 getch();
	 system("cls");
//7.searching if this linkedlist have the data we want.
	 printf("����û�����ˣ����ڽ�����һ���SearchList����������Ƿ���������Ҫ��data,");
	 getch();
	 printf("������������û��6��7��8��9����\n\n");
	 getch();
	 for(i=6;i<10;i++){
	 	if(SUCCESS==SearchList(L,i)){
	 		printf("%d���������\n",i);
		 }else{
		 	printf("��!%d�ɲ�������\n",i);
		 }
	 }
	 getch();
	 printf("��ð���ָͷ�����ж��ٸ���,����ɾ��һ���ڵ���ˣ�Ϊ��ʣ�µĲ�����׼��\n"); 
	 getch();
	 system("cls");
//8.delete a note
	 TraverseList(L,visit2);
	 printf("\n\n��ô���ڣ��Ұ����һ���ڵ�ɾ��");
	 temp = L->next;
	 //finding the note we want to delect
	 for(i=0;i<5;i++){
	 	temp = temp->next;
	 }
	 //delecting
	 DeleteList(temp, &i);
	 printf("\n\n������ɾ���Ľڵ��data��%d�������㿴\n\n",i);
	 //showing the delected linkedlist
	 TraverseList(L,visit2);
	 getch(); 
	 printf("\n\n���ˣ�Ҫ׼����ת�������ż�Ե���"); 
	 getch(); 
	 system("cls");
//9.reversing the list
	 printf("����һ�ַ�ת�����,��ת֮ǰ��������\n\n");
	 TraverseList(L,visit2);
	 ReverseList(&L);
	 printf("\n\n��ת֮����������\n\n"); 
	 TraverseList(L,visit2);
	 getch();
//10.reverseevenlist
	 printf("\n\n���棬������ż�Ե���\n\n");
	 LinkedList new_head;
	 new_head = ReverseEvenList(&L);
	 TraverseList(new_head,visit2);
	 printf("�ǰɣ���ż�Ե��˰ɡ�\n\n");
	 getch();
//11.destroylist
	 printf("ҮҮҮҮҮֻʣ��������������"); 
	 getch();
	 DestroyList(&L);
	 printf("\n\n����������������������ɢ��ɢ��\n\n");
	 getch();
	 printf("ллʦ�㣡"); 
	return 0;
}

void introducing(){
	printf("Owo:ʦ������ۣ��������ҵ�ѵ���������ݡ�\n\n");
	system("pause");
	system("cls");
	printf("Owo:�����������ӵģ������Ѿ�׼������1~7����Ȼ�����һ��Ȱѵ��������ã�Ȼ���������ʾ����������\n\n"); 
	getch();
	printf("Owo:Ȼ��ͣ�һֱ���������������ðɣ��ͻ��С�����ʽ����������������");	
	getch();
	system("cls");
}
