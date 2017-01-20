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

uint8_t data[100] = {0,1,3,6,7,4,2,5,8,9};
Node* root = NULL;

void createTree(_In_ uint8_t* data, size_t dataSize);
Node* compare(_In_ Node* parents, uint8_t newData);
void printTree(_In_ Node* root);

uint8_t main(void) {
	
	//create random
	srand(time(NULL));
	for (int i = 0; i < sizeof(data); i++) {
		data[i] = rand()% ((int)sizeof(data) +1);
	}
	createTree(data, sizeof(data));
	printTree(root);

	//printf("\n%p", &nodeMap[0]);
	printf("\nPause! Please press any button");
	getchar();
	return 0;
}

void createTree(_In_ uint8_t* data, size_t dataSize) {
	//create root

	root = (Node*)malloc(sizeof(Node));
	root->parent = NULL;
	root->left = NULL;
	root->right = NULL;
	root->same = 0;
	root->data = data[0];

	for (int i = 1; i < dataSize; i++) {
		compare(root, data[i]);
	}
}

Node* compare(_In_ Node* parents, uint8_t newData) {
	if (newData < parents->data) {
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
	else if(newData > parents->data){
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

void printTree(_In_ Node* parents) {
	if (parents->left != NULL) {
		printTree(parents->left);
		printf("%d:%d ", parents->data, parents->same+1);
	}
	if (parents->right != NULL) {
		if(parents->left == NULL)
			printf("%d:%d ", parents->data, parents->same+1);
		printTree(parents->right);
	}
	if(parents->left == NULL && parents->right == NULL) {
		printf("%d:%d ", parents->data, parents->same+1);
	}
}