#include <stdio.h>
#include <stdlib.h>

/**
 * 1. 每个节点或是红色，或是黑色。
 * 2. 根结点是黑色。
 * 3. 每个叶子节点(nil)是黑的。
 * 4. 红色节点的叶子是黑色。
 * 5. 对每个结点，从该结点到其子孙节点的所有路径上包含相同数目的黑结点。
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
