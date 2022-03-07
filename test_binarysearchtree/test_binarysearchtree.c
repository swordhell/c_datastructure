/**
 * ʵ���ϣ����ǲ��������Ǳ�֤����ع��������������Ȼ��������ƶ����������ı��壬��
 * ��֤�����������кõ��������ܡ��� 13 �¸�����һ�������ı��Σ������������������Ϊ
 * OClgn) ���� 18 �½����� �������ر�����ǧ���������̣��洢���ϵ����ݿ�ά����
 * 
 * ���������������κν�� x, ���������еĹؼ�����󲻳��� x.key, ���������еĹؼ�����С��
 * ���� x. key ��
 * 
 * ���� SEARCH MINIMUM OMUM PREDECESSOR SUCCESSOR INSERT DELETE �ȡ���ˣ�����
 * ʹ��һ���������ȿ�����Ϊһ���ֵ��ֿ�����Ϊһ�����ȶ��С�
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>

/**
* ���Ľ��
*/
struct node {
	struct node* left;
	struct node* right;
	struct node* p;
	int key;
};

/**
* ���ṹ
*/
struct tree {
	struct node* root;
};

// �������
void init_rand_env()
{
	srand((unsigned)time(0));
}

// ���������
void inorder_tree_walk(struct node* x)
{
	if (x != 0)
	{
		inorder_tree_walk(x->left);
		printf("%d ", x->key);
		inorder_tree_walk(x->right);
	}
}

// ����
struct node* bst_search(struct node* x, int key)
{
	if (x == 0 || x->key == key)
	{
		return x;
	}
	if (key > x->key)
	{
		return bst_search(x->right, key);
	}
	else
	{
		return bst_search(x->left, key);
	}
}

// ������С��
// ��ʵ������������ߵ�Ҷ��
struct node* bst_minimum(struct node* x)
{
	assert(x != 0);
	while (x->left != 0)
	{
		x = x->left;
	}
	return x;
}

// ������С��
// ��ʵ�����������ұߵ�Ҷ��
struct node* bst_maximum(struct node* x)
{
	assert(x != 0);
	while (x->right != 0)
	{
		x = x->right;
	}
	return x;
}

/**
 * ����һ�ö����������е�һ����㣬��ʱ����Ҫ����������Ĵ���������ĺ�̡�
 */
struct node* bst_tree_successor(struct node* x)
{
	struct node* y = 0;
	if (x->right != 0)
	{
		return bst_minimum(x->right);
	}
	y = x->p;
	while (y != 0 && x == y->right)
	{
		x = y;
		y = y->p;
	}
	return y;
}
/**
* Ҫ��һ����ֵ ���뵽һ�ö��������� �У���Ҫ���ù��� TREE-INSERT ���ù����Խ��z
* ��Ϊ���룬���� z. key=v, z. left=NIL, z. right=NIL ���������Ҫ�޸� ��ĳЩ���ԣ�
* ���� ���뵽���е���Ӧλ���ϡ�
*/
void bst_tree_insert(struct tree* T, struct node* z)
{
	struct node* y = 0;
	struct node* x = T->root;
	while (x != 0) // �ҵ����ʵĲ���Ҷ�ӽ��
	{
		y = x;
		if (z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	z->p = y;
	if (y == 0)
		T->root = z;
	else if (z->key < y->key)
		y->left = z;
	else
		y->right = z;
}

/**
* ɾ��һ�������ұ�������
*/
void release_tree(struct node* x)
{
	if (x == 0)
		return;
	release_tree(x->right);
	release_tree(x->left);
	free(x);
}

#define new_node(n) z = (struct node*)malloc(sizeof(struct node));\
	if (z==0) return -1;\
	z->key = n; z->right = 0; z->left = 0; z->p = 0;

int main(int argn, char* argc[])
{
	struct tree *T;
	struct node* z = 0;

	init_rand_env();
	T = (struct tree*)malloc(sizeof(struct tree));
	if (T == 0)
	{
		return -1;
	}
	T->root = 0;

	new_node(12);
	bst_tree_insert(T, z);
	new_node(18);
	bst_tree_insert(T, z);
	new_node(19);
	bst_tree_insert(T, z);
	new_node(15);
	bst_tree_insert(T, z);
	new_node(17);
	bst_tree_insert(T, z);
	new_node(13);
	bst_tree_insert(T, z);
	new_node(5);
	bst_tree_insert(T, z);
	new_node(9);
	bst_tree_insert(T, z);
	new_node(2);
	bst_tree_insert(T, z);

	inorder_tree_walk(T->root);

	z = bst_search(T->root, 9);

	release_tree(T->root);
	free(T);
	return 0;
}
