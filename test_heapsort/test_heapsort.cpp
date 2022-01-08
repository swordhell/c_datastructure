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

// C++ֱ�ӵ�ʵ�ֶ�����
void cpp_heap_sort()
{
	std::vector<int> heap;
	std::vector<int> result;
	int i = 0;
	auto output = [](std::vector<int>& heap) {// ��ӡ����Ϣ
		std::for_each(heap.begin(), heap.end(), [](auto& i) {std::cout << i << " "; }); std::cout << std::endl;
	};
	heap.reserve(MAX_ARRAY);
	for (i = 0; i < MAX_ARRAY; i++) // �������������
		heap.push_back(raw_array[i]);
	std::make_heap(heap.begin(), heap.end()); // ��ʼ����
	std::cout << "c++ make_heap finish\n";
	output(heap);
	for (i = 0; i < MAX_ARRAY; i++) {  // ����������������
		result.push_back(heap.front());
		std::pop_heap(heap.begin(), heap.end());
		heap.pop_back();
	}
	std::cout << "c++ sort finish\n";
	output(result);
}
