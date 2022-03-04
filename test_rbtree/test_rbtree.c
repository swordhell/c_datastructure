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
* 1.将x的右树y替换x的位置；
* 2.将y的左树放入x右树；
* 3.将y原本左树放入x的右树；
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
