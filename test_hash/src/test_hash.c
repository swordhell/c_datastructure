#include <stdio.h>
#include <stdlib.h>
#include "lhash.h"

int main(int argc, char *argv[]) {
	printf("start test hash object\n");
	void *hash = create_hash(32, 64, "test_hash");
	HashOptResult result = HashOptResult_OK;
	unsigned long val = 0;

	if (hash == NULL)
	{
		printf("[%s]:%d %s create_hash fail!\n", __FILE__, __LINE__, __FUNCTION__);
		return -1;
	}

	result = hash_set(hash, 88, 100);
	printf("[%s]:%d %s result: %d = hash_set(hash, 88, 100);\n", __FILE__, __LINE__, __FUNCTION__, (int)result);
	
	result = hash_find(hash, 88, &val);
	printf("[%s]:%d %s result: %d = hash_find %lu \n", __FILE__, __LINE__, __FUNCTION__, (int)result, val);

	result = hash_del(hash, 88);
	printf("[%s]:%d %s result: %d = hash_del\n", __FILE__, __LINE__, __FUNCTION__, (int)result);
	release_hash(hash);
	return 0;
}
