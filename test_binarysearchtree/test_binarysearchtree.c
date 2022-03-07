/**
 * 实际上，我们并不能总是保证随机地构造二叉搜索树，然而可以设计二叉搜索树的变体，来
 * 保证基本操作具有好的最坏情况性能。第 13 章给出了一个这样的变形，即红黑树，它的树高为
 * OClgn) 。第 18 章将介绍 树，它特别适用千二级（磁盘）存储器上的数据库维护。
 * 
 * 二叉搜索树。对任何结点 x, 其左子树中的关键字最大不超过 x.key, 其右子树中的关键字最小不
 * 低于 x. key 。
 * 
 * 包括 SEARCH MINIMUM OMUM PREDECESSOR SUCCESSOR INSERT DELETE 等。因此，我们
 * 使用一棵搜索树既可以作为一个字典又可以作为一个优先队列。
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>

/**
* 树的结点
*/
struct node {
	struct node* left;
	struct node* right;
	struct node* p;
	int key;
};

/**
* 树结构
*/
struct tree {
	struct node* root;
};

// 种随机数
void init_rand_env()
{
	srand((unsigned)time(0));
}

// 中序遍历树
void inorder_tree_walk(struct node* x)
{
	if (x != 0)
	{
		inorder_tree_walk(x->left);
		printf("%d ", x->key);
		inorder_tree_walk(x->right);
	}
}

// 查找
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

// 查找最小数
// 其实就树里面最左边的叶子
struct node* bst_minimum(struct node* x)
{
	assert(x != 0);
	while (x->left != 0)
	{
		x = x->left;
	}
	return x;
}

// 查找最小数
// 其实就树里面最右边的叶子
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
 * 给定一棵二叉搜索树中的一个结点，有时候需要按中序遍历的次序查找它的后继。
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
* 要将一个新值 插入到一棵二叉搜索树 中，需要调用过程 TREE-INSERT 。该过程以结点z
* 作为输入，其中 z. key=v, z. left=NIL, z. right=NIL 。这个过程要修改 的某些属性，
* 来把 插入到树中的相应位置上。
*/
void bst_tree_insert(struct tree* T, struct node* z)
{
	struct node* y = 0;
	struct node* x = T->root;
	while (x != 0) // 找到合适的插入叶子结点
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
* 删除一棵树并且遍历子树
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
