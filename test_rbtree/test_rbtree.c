#include <stdio.h>
#include <stdlib.h>

/**
 * 1. ÿ���ڵ���Ǻ�ɫ�����Ǻ�ɫ��
 * 2. ������Ǻ�ɫ��
 * 3. ÿ��Ҷ�ӽڵ�(nil)�Ǻڵġ�
 * 4. ��ɫ�ڵ��Ҷ���Ǻ�ɫ��
 * 5. ��ÿ����㣬�Ӹý�㵽������ڵ������·���ϰ�����ͬ��Ŀ�ĺڽ�㡣
 * 
 * linuxʵ�ֵĺ����Դ��
 * https://github.com/torvalds/linux/blob/master/lib/rbtree.c
 * 
 * ���ƶ�������ʾ��
 * https://www.yanbinghu.com/2019/04/10/9448.html
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
	struct node* nil; // �ڱ��ڵ�
};

/**
* ��������
* yΪx��������
* 1.��x��y�滻x��λ�ã�
* 2.��y����������x������
* 3.��yԭ����������x��������
*/
void left_rotate(struct tree* T, struct node* x) {
	struct node* y;
	
	y = x->right;
	x->right = y->left;
	if (y->left != T->nil)
		y->left->p = x;
	y->p = x->p;
	if (x->p == T->nil)
		T->root = y;
	else if (x == x->p->left)
		x->p->left = y;
	else
		x->p->right = y;
	y->left = x;
	x->p = y;

}

/**
 * ����ת
* yΪx������������
* 1.��x��y�滻x��λ�ã�
* 2.��y����������x������
* 3.��yԭ����������x��������
 */
void right_rotate(struct tree* T, struct node* x) {
	struct node* y;

	y = x->left;
	x->left = y->right;

	if (y->right != T->nil)
		y->right->p = x;
	y->p = x->p;
	if (x->p == T->nil)
		T->root = y;
	else if (x == x->p->left)
		x->p->left = y;
	else
		x->p->right = y;
	x->p = y;
}

/**
* ������ɫ����ת
*/
void rb_insert_fixup(struct tree* T, struct node* z) {
	struct node* y;
	while (z->p->color == RED)
	{
		if (z->p == z->p->p->left)
		{
			y = z->p->p->right;
			if (y->color == RED)
			{
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else if (z == z->p->right)
			{
				z = z->p;
				left_rotate(T, z);
			}
			z->p->color = BLACK;
			z->p->p->color = RED;
			right_rotate(T, z->p->p);
		}
		else
		{
			y = z->p->p->left;
			if (y->color == RED)
			{
				z->p->color = BLACK;
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p;
			}
			else if (z == z->p->left)
			{
				z = z->p;
				right_rotate(T, z);
			}
			z->p->color = BLACK;
			z->p->p->color = RED;
			left_rotate(T, z->p->p);
		}
	}
	T->root->color = BLACK;
	if (T->nil->p == 0)
	{
		T->nil = T->root;
	}
}

/**
* ���뺯��
* 
*/
void rb_insert(struct tree* T,struct node* z ) {
	struct node* x,* y;
	y = T->nil;
	x = T->root;
	while (x != T->nil) {
		y = x;
		if (z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	z->p = y;
	if ( y == T->nil){
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

void rb_transplant(struct tree* T, struct node* u, struct node* v)
{
	if (u->p == T->nil)
	{
		T->root = v;
	}
	else if (u == u->p->left)
	{
		u->p->left = v;
	}
	else
	{
		u->p->right = v;
	}
	v->p = u->p;
}

int main(int argn, char* argc[])
{
	struct tree* T;
	struct node* z = 0;

	T = (struct tree*)malloc(sizeof(struct tree));
	if (T == 0)
	{
		printf("malloc T fail.\n");
		return -1;
	}
	T->nil = (struct node*)malloc(sizeof(struct node));
	if (T->nil == 0)
	{
		printf("malloc T->nil fail.\n");
		return -1;
	}
	T->nil->p = 0;
	T->nil->color = BLACK;
	T->nil->left = 0;
	T->nil->right = 0;

	return 0;
}
