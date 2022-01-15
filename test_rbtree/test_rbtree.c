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
	enum COLOR color;
	int key;
	struct node* left;
	struct node* right;
	void* p;
};

struct tree {
	struct node* root;
};

/**
* 1.��x������y�滻x��λ�ã�
* 2.��y����������x������
* 3.��yԭ����������x��������
*/
void left_rotate(struct tree* T, struct node* x) {
	struct node* y;
	
	y = x->right;
	x->right = y->left;
	if (y->left == 0)
		y->left->p = x;
	y->p = x->p;
	if (x->p == 0)
		T->root = y;
	else if (x == x->p->left)
		x->p->left = y;
	else
		x->p->right = y;
	x->p = y;

}

int main(int argn, char* argc[])
{
	return 0;
}
