#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include "../inc/qgsort.h"


/**
 *  @name        : void insertSort(int *a,int n);
 *  @description : 插入排序
 *  @param       : 数组指针 a, 数组长度 n
 */
void insertSort(int *a,int n){
	int count,temp,last;
	//从第二个开始
	for(count=1;count<n;count++){
		temp = a[count];
		//从后往前比较，如果不满足条件则往后挪一位 
		for(last=count;last>0&&a[last-1]>temp;last--){
			a[last] = a[last-1];
		}
		//找到合适的位置了，落位 
		a[last] = temp;
	}
}


/**
 *  @name        : void QuickSort(int *a, int begin, int end);
 *  @description : 快速排序（递归版）
 *  @param       : 数组指针a，数组起点begin，数组终点end
 */
void QuickSort_Recursion(int *a, int begin, int end){
	if(begin<end){
		int q = Partition(a,begin,end);
		QuickSort_Recursion(a,begin,q-1);
		QuickSort_Recursion(a,q+1,end);
	}
} 


/**
 *  @name        : void QuickSort(int *a, int begin, int end)
 *  @description : 快速排序（枢轴存放）
 *  @param       : 数组指针a，数组起点begin，数组终点end
 */
int Partition(int *a, int begin, int end){
	int x = a[end];
	int i = begin - 1;
	int j;
	for(j=begin;j<=end-1;j++){
		if(a[j]<x){
			i++;
			int temp = a[i];
			a[i] = a[j];
			a[j] = temp;
		}
	}
	int temp = a[i+1];
	a[i+1] = a[end];
	a[end] = temp;
	return i+1;
} 


/**
 *  @name        : void CountSort(int *a, int size , int max)
 *  @description : 计数排序
 *  @param       : 数组指针a，数组长度size，数组最大值max
 */
void CountSort(int *a, int size , int max){
	int i,j;
	int *counts,*temp;
	// counts是"记数"名称的来源 
	counts = (int *)malloc((max+1)*sizeof(int));
	temp = (int *)malloc((size)*sizeof(int));
	
	if(counts == NULL){
		printf("申请内存失败！");
		exit(1);
	}
	if(temp == NULL){
		printf("申请内存失败！");
		exit(1);
	}
	
	for(i=0;i<max+1;i++){
		counts[i] = 0;
	}
	//统计每个元素出现的次数,(counts的下标索引即是要统计的元素本身)
	for(j=0;j<size;j++){
		counts[a[j]] = counts[a[j]] + 1;
	}
	//将元素本身的次数加上它前一个元素的次数，得到元素偏移量
	for(i=1;i<max+1;i++){
		counts[i] = counts[i] + counts[i-1];
	}
	//使用计数数组去放置每一个元素要排序的位置
	for(j=size-1;j>=0;j--){
		//counts的值是元素要放置到temp中的偏移量 
		temp[counts[a[j]]-1] = a[j]; 
		//counts的记数-1
		counts[a[j]] = counts[a[j]] - 1; 
	} 
	memcpy(a,temp,size*sizeof(int));
	free(counts);
	free(temp);
}


/**
 *  @name        : void RadixCountSort(int *a,int size)
 *  @description : 基数计数排序
 *  @param       : 数组指针a，数组长度size
 */
void RadixCountSort(int *a,int size){
	// 得到最大值的位数 
	int max = a[0];
	int i;
	int count = 0;
	for(i=1;i<size;i++){
		if(max<a[i]){
			max = a[i];
		}
	}
	while(max!=0){
		max /= 10;
		count ++;
	}
	
	int *counts,*temp; 
	temp = (int *)malloc((size+1)*sizeof(int));
	counts = (int *)malloc(10*sizeof(int));
	
	if(counts == NULL){
		printf("申请内存失败！");
		exit(1);
	}
	if(temp == NULL){
		printf("申请内存失败！");
		exit(1);
	}
	
	int j,k,tmp;
	int radix = 1;
	for(i=1;i<=count;i++){
		for(j=0;j<10;j++){
			counts[j] = 0;
		}
		for(k=1;k<=size;k++){
			tmp = (a[k] / radix) % 10;
			counts[tmp]++;
		}
		
		for(j=1;j<10;j++){
			counts[j] += counts[j-1];
		}
		for(k=size;k>=1;k--){
			tmp = (a[k] / radix) % 10;
			temp[counts[tmp]] = a[k];
			counts[tmp]--;
		}
		radix *= 10;
		memcpy(a,temp,(size+1)*sizeof(int));
	}
}



/**
 *  @name        : void MergeArray(int *a,int begin,int mid,int end,int *temp);
 *  @description : 归并排序（合并数组）
 *  @param       : 数组指针a，数组起点begin，数组中点mid，数组终点end，承载数组指针temp
 */
void MergeArray(int *a,int begin,int mid,int end,int *temp){
	// 左边终点的位置
	int leftend = mid - 1;
	// 存放结果数组的初始位置,决定从哪开始存放归并的结果 
	int tmp = begin;
	// 归并后的总个数
	int number = end - begin + 1;
	
	while(begin<=leftend&&mid<=end){
		if(a[begin]<=a[mid]){
			temp[tmp++] = a[begin++];
		}else{
			temp[tmp++] = a[mid++];
		}
	}
	
	while(begin<=leftend){
		temp[tmp++] = a[begin++];
	}
	while(mid<=end){
		temp[tmp++] = a[mid++];
	}
	
	int i;
	for(i=0;i<number;i++,end--){
		a[end] = temp[end];
	}
}


/**
 *  @name        : void MergeSort(int *a,int begin,int end,int *temp);
 *  @description : 归并排序
 *  @param       : 数组指针a，数组起点begin，数组终点end，承载数组指针temp
 */
void MergeSort(int *a,int begin,int end,int *temp){
	int mid;
	if(begin<end){
		mid = (begin + end) / 2;
		MergeSort(a,begin,mid,temp);
		MergeSort(a,mid+1,end,temp); 
		MergeArray(a,begin,mid+1,end,temp);
	}
}


//统一函数接口
void Merge_sort(int *a, int n){
	int *temp;
	//malloc 在这个地方有点玄机，在下面MergeSort的时候看上去有些啰嗦，但是更快 
	temp = (int *)malloc(n*sizeof(int));
	if(temp!=NULL){
		MergeSort(a,0,n-1,temp);
		free(temp);
	}else{
		printf("空间不足");
		exit(1); 
	}
}
