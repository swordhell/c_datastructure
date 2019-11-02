#include <stdio.h>
#include <stdlib.h>
#include "llist.h"

typedef struct node
{
	list_head lst;
	int age;
}node;

int main(int argc, char *argv[]) {
	
	node *pnode = NULL;
	list_head *pos = NULL;
	int i = 0;
	LIST_HEAD(main_lst);

	for (i = 0; i< 10; i++)
	{
		pnode = malloc(sizeof(node));
		pnode->age = i;
		INIT_LIST_HEAD(&pnode->lst);

		list_add_tail(&pnode->lst, &main_lst);
	}

	list_for_each(pos, &main_lst)
	{
		node *pnode = list_entry(pos, node, lst);
		printf("age: %d\n", pnode->age);
	}

	while (!list_empty(&main_lst))
	{
		pos = main_lst.next;
		node *pnode = list_entry(pos, node, lst);
		list_del(pos);
		free(pnode);
	}

	return 0;
}
