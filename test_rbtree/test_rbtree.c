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
	struct node* p;
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
	if (y->left != 0)
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

void right_rotate(struct tree* T, struct node* x) {
	struct node* y;

	y = x->left;
	x->left = y->right;

	if (y->right != 0)
		y->right->p = x;
	y->p = x->p;
	if (x->p == 0)
		T->root = y;
	else if (x == x->p->left)
		x->p->left = y;
	else
		x->p->right = y;
	x->p = y;
}

void rb_insert_fixup(struct tree* T, struct node* z) {

}

void rb_insert(struct tree* T,struct node* z ) {
	struct node* x,* y;
	y = 0;
	x = T->root;
	while (x != 0) {
		y = x;
		if (z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	z->p = y;
	if ( y == 0){
		T->root = z;
	}
	else if (z->key < y->key) {
		y->left = z;
	}
	else
	{
		y->right = z;
	}
	z->left = 0;
	z->right = 0;
	z->color = RED;

	rb_insert_fixup(T, z);
}

int main(int argn, char* argc[])
{
	return 0;
}
