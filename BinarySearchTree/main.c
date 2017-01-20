#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _Node
{
	void* parent;
	void* left;
	void* right;
	uint8_t data;
	uint8_t same;
} Node;

uint8_t data[10] = {0,1,3,6,7,4,2,5,8,9};
Node *nodeMap[sizeof(data)];

void createTree(_In_ uint8_t* data, size_t dataSize, _Inout_ Node *map[]);
Node* compare(_In_ Node* parents, uint8_t newData);
void printTree(_In_ Node* root);

uint8_t main(void) {
	
	//create random
	srand(time(NULL));
	for (int i = 0; i < sizeof(data); i++) {
		data[i] = rand()%10+1;
	}
	createTree(data, sizeof(data), nodeMap);
	printTree(nodeMap[0]);

	//printf("\n%p", &nodeMap[0]);
	printf("\nPause! Please press any button");
	getchar();
	return 0;
}

void createTree(_In_ uint8_t* data, size_t dataSize, _Inout_ Node *map[]) {
	//create root

	map[0] = (Node*)malloc(sizeof(Node));
	map[0]->parent = NULL;
	map[0]->left = NULL;
	map[0]->right = NULL;
	map[0]->same = 0;
	map[0]->data = data[0];

	for (int i = 1; i < dataSize; i++) {
		map[i] = compare(map[0], data[i]);
	}
}

Node* compare(_In_ Node* parents, uint8_t newData) {
	if (parents->data > newData) {
		if (parents->left == NULL) {
			parents->left = (Node*)malloc(sizeof(Node));
			((Node*)parents->left)->parent = parents;
			((Node*)parents->left)->data = newData;
			((Node*)parents->left)->left = NULL;
			((Node*)parents->left)->right = NULL;
			((Node*)parents->left)->same = 0;
			return parents->left;
		}
		else {
			compare(parents->left, newData);
		}
	}
	else if(parents->data < newData){
		if (parents->right == NULL) {
			parents->right = (Node*)malloc(sizeof(Node));
			((Node*)parents->right)->parent = parents;
			((Node*)parents->right)->data = newData;
			((Node*)parents->right)->left = NULL;
			((Node*)parents->right)->right = NULL;
			((Node*)parents->right)->same = 0;
			return parents->right;
		}
		else {
			compare(parents->right, newData);
		}
	}
	else {
		parents->same+=1;
		return parents;
	}
}

void printTree(_In_ Node* root) {
	if (root->left != NULL) {
		printTree(root->left);
		printf("%d ", root->data);
	}
	if (root->right != NULL) {
		if(root->left == NULL)
			printf("%d ", root->data);
		printTree(root->right);
	}
	if(root->left == NULL && root->right == NULL) {
		printf("%d ", root->data);
	}
}