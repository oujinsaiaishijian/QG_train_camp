#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include "../inc/qgsort.h"


/**
 *  @name        : void insertSort(int *a,int n);
 *  @description : ��������
 *  @param       : ����ָ�� a, ���鳤�� n
 */
void insertSort(int *a,int n){
	int count,temp,last;
	//�ӵڶ�����ʼ
	for(count=1;count<n;count++){
		temp = a[count];
		//�Ӻ���ǰ�Ƚϣ��������������������Ųһλ 
		for(last=count;last>0&&a[last-1]>temp;last--){
			a[last] = a[last-1];
		}
		//�ҵ����ʵ�λ���ˣ���λ 
		a[last] = temp;
	}
}


/**
 *  @name        : void QuickSort(int *a, int begin, int end);
 *  @description : �������򣨵ݹ�棩
 *  @param       : ����ָ��a���������begin�������յ�end
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
 *  @description : �������������ţ�
 *  @param       : ����ָ��a���������begin�������յ�end
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
 *  @description : ��������
 *  @param       : ����ָ��a�����鳤��size���������ֵmax
 */
void CountSort(int *a, int size , int max){
	int i,j;
	int *counts,*temp;
	// counts��"����"���Ƶ���Դ 
	counts = (int *)malloc((max+1)*sizeof(int));
	temp = (int *)malloc((size)*sizeof(int));
	
	if(counts == NULL){
		printf("�����ڴ�ʧ�ܣ�");
		exit(1);
	}
	if(temp == NULL){
		printf("�����ڴ�ʧ�ܣ�");
		exit(1);
	}
	
	for(i=0;i<max+1;i++){
		counts[i] = 0;
	}
	//ͳ��ÿ��Ԫ�س��ֵĴ���,(counts���±���������Ҫͳ�Ƶ�Ԫ�ر���)
	for(j=0;j<size;j++){
		counts[a[j]] = counts[a[j]] + 1;
	}
	//��Ԫ�ر���Ĵ���������ǰһ��Ԫ�صĴ������õ�Ԫ��ƫ����
	for(i=1;i<max+1;i++){
		counts[i] = counts[i] + counts[i-1];
	}
	//ʹ�ü�������ȥ����ÿһ��Ԫ��Ҫ�����λ��
	for(j=size-1;j>=0;j--){
		//counts��ֵ��Ԫ��Ҫ���õ�temp�е�ƫ���� 
		temp[counts[a[j]]-1] = a[j]; 
		//counts�ļ���-1
		counts[a[j]] = counts[a[j]] - 1; 
	} 
	memcpy(a,temp,size*sizeof(int));
	free(counts);
	free(temp);
}


/**
 *  @name        : void RadixCountSort(int *a,int size)
 *  @description : ������������
 *  @param       : ����ָ��a�����鳤��size
 */
void RadixCountSort(int *a,int size){
	// �õ����ֵ��λ�� 
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
		printf("�����ڴ�ʧ�ܣ�");
		exit(1);
	}
	if(temp == NULL){
		printf("�����ڴ�ʧ�ܣ�");
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
 *  @description : �鲢���򣨺ϲ����飩
 *  @param       : ����ָ��a���������begin�������е�mid�������յ�end����������ָ��temp
 */
void MergeArray(int *a,int begin,int mid,int end,int *temp){
	// ����յ��λ��
	int leftend = mid - 1;
	// ��Ž������ĳ�ʼλ��,�������Ŀ�ʼ��Ź鲢�Ľ�� 
	int tmp = begin;
	// �鲢����ܸ���
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
 *  @description : �鲢����
 *  @param       : ����ָ��a���������begin�������յ�end����������ָ��temp
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


//ͳһ�����ӿ�
void Merge_sort(int *a, int n){
	int *temp;
	//malloc ������ط��е�������������MergeSort��ʱ����ȥ��Щ���£����Ǹ��� 
	temp = (int *)malloc(n*sizeof(int));
	if(temp!=NULL){
		MergeSort(a,0,n-1,temp);
		free(temp);
	}else{
		printf("�ռ䲻��");
		exit(1); 
	}
}
