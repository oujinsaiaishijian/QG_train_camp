#include <stdio.h>
#include <stdlib.h>
#include "../inc/qgsort.h"
#include <time.h>

int main(){

	//取得文件中数字的个数，创建数组 
	int size=0;
	int m;
	FILE *fp = fopen("data.txt","r");

    while(!feof(fp)){
    	fscanf(fp,"%d\n",&m);
    	size++;
	}
	
	int array1[size];
	int array2[size];
	int array3[size];
	int array4[size];
	int array5[size];
	
	// 把数据放入数组中
	rewind(fp);
	int i=0;
    while(!feof(fp)){
    	fscanf(fp,"%d\n",&m);
    	array1[i]=m;
    	array2[i]=m;
    	array3[i]=m;
    	array4[i]=m;
    	array5[i]=m;
    	i++;
	}
    fclose(fp);
    
    int c=clock();
    //插入 
	insertSort(array1,size);
    int b=clock();
    printf("\n\n插入排序的时长是%dms\n\n",b-c); 

    
        	    
    //快速排序
    c=clock();
	QuickSort_Recursion(array2,0,size-1);
	b=clock();
	
	printf("\n\n快速排序的时长是%dms\n\n",b-c); 
 
    
    	
	//计数排序 
	int max = array3[0];
	int count = 0;
	for(i=1;i<size;i++){
		if(max<array4[i]){
			max = array3[i];
		}
	} 
    
    c=clock();
    CountSort(array3,size,max);
    b=clock();
    
    printf("\n\n计数排序的时长是%dms\n\n",b-c); 
    
    
    //基数排序
	c=clock();
	RadixCountSort(array4,size); 
    b=clock();
    printf("\n\n基数排序的时长是%dms",b-c); 
    
    
    //归并
	c=clock();
	
    Merge_sort(array5,size); 
    
    
    b=clock();
    
    printf("\n\n归并排序的时长是%dms\n\n",b-c); 
	

	getch();
	return 0;
}


