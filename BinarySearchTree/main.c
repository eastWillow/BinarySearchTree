#include <stdint.h>
#include <stdio.h>

typedef struct _Node
{
	intptr_t* parent;
	intptr_t* left;
	intptr_t* right;
	int data;
} Node;

uint8_t main(void) {
	Node node1;
	void* node1Ptr;
	node1Ptr = &node1;
	node1.data = 10;

	printf("HelloWorld\n");
	printf("node.data = %d\n", node1.data);
	printf("nodePtr = %x\n", (intptr_t)node1Ptr);
	getchar();
	return 0;
}