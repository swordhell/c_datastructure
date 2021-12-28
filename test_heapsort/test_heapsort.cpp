#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>

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
	{
		raw_array[i] = rand() % NUMBER_RANGE;
	}
}

// 输出数组
void output_array()
{
	int i;
	for (i = 0; i < MAX_ARRAY; i++)
	{
		printf("%d ", raw_array[i]);
	}
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
	int i,j,tmp;
	build_max_heap(A, size);
	std::cout << "c建堆完成\n";
	output_array();
	for (i = size-1; i >= 0; i--)
	{
		tmp = A[0];
		for (j = 1; j < size; j++)
			A[j - 1] = A[j];
		size--;
		A[size] = tmp;
		max_heapify(A, size, 0);
		output_array(); 
	}
}

// C++直接的实现堆排序
void cpp_heap_sort()
{
	std::vector<int> heap;
	std::vector<int> result;
	int i = 0;
	auto output = [](std::vector<int>& heap) {// 打印堆信息
		std::for_each(heap.begin(), heap.end(), [](auto& i) {std::cout << i << " ";});std::cout << std::endl;
	};
	heap.reserve(MAX_ARRAY);
	for (i = 0; i < MAX_ARRAY; i++) // 构造随机的数字
		heap.push_back(raw_array[i]);
	std::make_heap(heap.begin(), heap.end()); // 开始建堆
	std::cout << "c++建堆完成\n";
	output(heap);
	for (i = 0; i < MAX_ARRAY;i++) {  // 反复弹出堆中内容
		result.push_back(heap.front());
		std::pop_heap(heap.begin(), heap.end());
		heap.pop_back();
	}
	std::cout << "c++排序完成\n";
	output(result);
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
	cpp_heap_sort();
	heap_sort(raw_array, MAX_ARRAY);

	output_array();
	free(raw_array);
	return 0;
}
