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
//注意要用&L传值啊 
	if(SUCCESS==InitList(&L)){
		printf("初始化头节点成功,下面开始创建简单链表并打印\n\n"); 
	}else{
		printf("初始化头节点失败。");
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
			printf("创建新节点时，内存申请失败！");
			return 0;
		}
		prev->next = rear;
		prev = prev->next;
	}	
	
//3. showing
	
	//定义一个指针函数 
	void (*visit2)(ElemType e);
	//把函数Visit赋给指针变量visit，使visit指向Visit 
	visit2 = visit;
	//通过函数指针调用Visit,把链表打印出来 
	TraverseList(L,visit2);
	printf("\n\n看吧，现在有了一个简单的链表，那么下面，让我来插入一个节点,我会把4插入在3和5的中间\n\n");
	//将prev重置为头节点，再前进到第三位，然后用temp作存储插入数据的节点 
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
	printf("\n\n是吧，自然数就要整整齐齐的quq\n");
	getch();
	printf("那么，就开始查询单链表中点吧！"); 
	getch();
	system("cls");
//5.finding the midnode;
	printf("我们的链表长这个样子:\n\n");
	TraverseList(L,visit2);
	getch();
	temp = FindMidNode(&L);
	printf("\n\nemmm,这个链表的中间节点的data应该是%d",temp->data);
	getch();
	system("cls");
//6.loop topic
   printf("那么接下来就是循环链表的测试了，我现在已经把末指针给接到头指针上了，先遍历一下看看\n\n");
   getch();
	 rear->next = L->next;
	 for(i=0;i<20;i++){
	 	printf("%d  ",rear->data);
	 	rear = rear->next;
	 }
	 printf("\n\n是吧！我好像把它变成了一个循环链表了呢,调用一下islooplist吧！（给自己加戏）\n\n"); 
	 getch();
	 if(SUCCESS==IsLoopList(rear)){
	 	printf("哇！这个链表真的是循环的也！（继续加戏）"); 
	 	getch();
	 }else{
	 	printf("好了好了，现在就不是了。"); 
	 }
	 printf("那我现在要把它解开了，就是把data为7的节点的next置为NULL\n\n");
	 do{
	 	rear=rear->next;
	 }while(rear->data!=7);
	 rear->next=NULL;
	 getch();
	 system("cls");
//7.searching if this linkedlist have the data we want.
	 printf("哎，没力气了，现在进行下一项，用SearchList检测链表中是否有我们想要的data,");
	 getch();
	 printf("看看链表中有没有6，7，8，9好了\n\n");
	 getch();
	 for(i=6;i<10;i++){
	 	if(SUCCESS==SearchList(L,i)){
	 		printf("%d是在里面的\n",i);
		 }else{
		 	printf("嚯!%d可不在里面\n",i);
		 }
	 }
	 getch();
	 printf("真得扳着指头数还有多少个啊,我先删除一个节点好了，为了剩下的操作作准备\n"); 
	 getch();
	 system("cls");
//8.delete a note
	 TraverseList(L,visit2);
	 printf("\n\n那么现在，我把最后一个节点删掉");
	 temp = L->next;
	 //finding the note we want to delect
	 for(i=0;i<5;i++){
	 	temp = temp->next;
	 }
	 //delecting
	 DeleteList(temp, &i);
	 printf("\n\n喏，我删除的节点的data是%d，不信你看\n\n",i);
	 //showing the delected linkedlist
	 TraverseList(L,visit2);
	 getch(); 
	 printf("\n\n好了，要准备反转链表和奇偶对调了"); 
	 getch(); 
	 system("cls");
//9.reversing the list
	 printf("先来一手反转链表吧,反转之前是这样的\n\n");
	 TraverseList(L,visit2);
	 ReverseList(&L);
	 printf("\n\n反转之后是这样的\n\n"); 
	 TraverseList(L,visit2);
	 getch();
//10.reverseevenlist
	 printf("\n\n下面，就是奇偶对调了\n\n");
	 LinkedList new_head;
	 new_head = ReverseEvenList(&L);
	 TraverseList(new_head,visit2);
	 printf("是吧，奇偶对调了吧。\n\n");
	 getch();
//11.destroylist
	 printf("耶耶耶耶耶只剩下销毁链表啦！"); 
	 getch();
	 DestroyList(&L);
	 printf("\n\n好啦好啦！销毁了销毁了散了散了\n\n");
	 getch();
	 printf("谢谢师姐！"); 
	return 0;
}

void introducing(){
	printf("Owo:师姐你好哇，这里是我的训练考核内容。\n\n");
	system("pause");
	system("cls");
	printf("Owo:大概是这个样子的，现在已经准备好了1~7的自然数，我会先把单链表做好，然后把数据显示出来看看。\n\n"); 
	getch();
	printf("Owo:然后就，一直像现在这样敲敲敲吧，就会有“交互式”体验了嘻嘻嘻。");	
	getch();
	system("cls");
}
