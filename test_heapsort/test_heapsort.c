#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int MAX_ARRAY = 10;
int NUMBER_RANGE = 100;
int* raw_array = 0;

// 种随机数
void init_rand_env()
{
	srand((unsigned)time(0));
}

// 产生一批数字
void rand_array_number()
{
	int i;
	for (i = 0; i < MAX_ARRAY; i++)
		raw_array[i] = rand() % NUMBER_RANGE;
}

// 输出数组
void output_array()
{
	int i;
	for (i = 0; i < MAX_ARRAY; i++)
		printf("%d ", raw_array[i]);
	printf("\n");
}

// 计算左子树下标
int left(int i)
{
	return (i + 1) * 2 - 1;
}

// 计算右子树下标
int right(int i)
{
	return (i + 1) * 2;
}

// 对堆中某个子树排序
void max_heapify(int* A, int size, int i)
{
	int l, r, largest,tmp;
	l = left(i);
	r = right(i);
	if (l < size && A[l] > A[i])
		largest = l;
	else
		largest = i;
	if (r < size && A[r] > A[largest])
		largest = r;
	if (largest != i) {
		tmp = A[i];
		A[i] = A[largest];
		A[largest] = tmp;
		max_heapify(A, size, largest);
	}
}

// 构建最大堆
void build_max_heap(int* A, int size)
{
	int i;
	for (i = (size+1)>>1; i > 0; ) {
		--i;
		max_heapify(A, size, i);
	}
	
}

// 堆排序
void heap_sort(int* A, int size)
{
	int i,tmp;
	build_max_heap(A, size);
	printf("C make heap finish\n");
	output_array();
	for (i = size-1; i > 0; i--) {
		tmp = A[0];
		A[0] = A[i];
		A[i] = tmp;
		size--;		
		max_heapify(A, size, 0);
		output_array(); 
	}
}

int main(int argn, char* argc[])
{
	if (argn != 3)
	{
		printf("usage: test_heapsort MAX_ARRAY NUMBER_RANGE\n");
		return -1;
	}
	MAX_ARRAY = atoi(argc[1]);
	NUMBER_RANGE = atoi(argc[2]);
	init_rand_env();

	raw_array = (int *)malloc(sizeof(int) * MAX_ARRAY);
	rand_array_number();
	output_array();
	heap_sort(raw_array, MAX_ARRAY);

	output_array();
	free(raw_array);
	return 0;
}
