#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _Node
{
	intptr_t* parent;
	intptr_t* left;
	intptr_t* right;
	int data;
} Node;

Node *nodeMap[10];

void newLeaf(_In_ uint8_t* data, _Inout_ Node *map[]);

uint8_t main(void) {
	uint8_t data[] = { 5,1,2,7,9 };
	newLeaf(data, nodeMap);

	printf("%p", &nodeMap[0]);
	getchar();
	return 0;
}

void createTree(_In_ uint8_t* data, _Inout_ Node *map[]) {
	//create root

	map[0] = (Node*)malloc(sizeof(Node));
	map[0]->parent = NULL;
	map[0]->data = data[0];

	for (int i = 1; i < sizeof(data); i++) {
		if (map[i-1]->data < data[i]) {
			if (map[i-1]->left == NULL) {
				map[i] = (Node*)malloc(sizeof(Node));
				map[i - 1]->left = map[i];
				map[i]->parent = map[i - 1];
				map[i]->data = data[i];
			}
			else {

			}
		}
		else {

		}
	}
}