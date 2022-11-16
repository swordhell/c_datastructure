#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>

extern int MAX_ARRAY;
extern int NUMBER_RANGE;
extern int* raw_array;

// C++直接的实现堆排序
void cpp_heap_sort()
{
	std::vector<int> heap;
	std::vector<int> result;
	int i = 0;
	auto output = [](std::vector<int>& heap) {// 打印堆信息
		std::for_each(heap.begin(), heap.end(), [](auto& i) {std::cout << i << " "; }); std::cout << std::endl;
	};
	heap.reserve(MAX_ARRAY);
	for (i = 0; i < MAX_ARRAY; i++) // 构造随机的数字
		heap.push_back(raw_array[i]);
	std::make_heap(heap.begin(), heap.end()); // 开始建堆
	std::cout << "c++ make_heap finish\n";
	output(heap);
	for (i = 0; i < MAX_ARRAY; i++) {  // 反复弹出堆中内容
		result.push_back(heap.front());
		std::pop_heap(heap.begin(), heap.end());
		heap.pop_back();
	}
	std::cout << "c++ sort finish\n";
	output(result);
}
