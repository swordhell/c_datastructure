#include <stdio.h>
#include <stdlib.h>

/**
 * 1. ÿ���ڵ���Ǻ�ɫ�����Ǻ�ɫ��
 * 2. ������Ǻ�ɫ��
 * 3. ÿ��Ҷ�ӽڵ�(nil)�Ǻڵġ�
 * 4. ��ɫ�ڵ��Ҷ���Ǻ�ɫ��
 * 5. ��ÿ����㣬�Ӹý�㵽������ڵ������·���ϰ�����ͬ��Ŀ�ĺڽ�㡣
 * https://github.com/torvalds/linux/blob/master/lib/rbtree.c
 */

enum COLOR {
	RED = 1,
	BLACK = 2,
};

struct node {
	COLOR color;
	int key;
	node* left;
	node* right;
	void* p;
};

int main(int argn, char* argc[]) {
	return 0;
}
