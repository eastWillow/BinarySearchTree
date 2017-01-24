#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RANDOM 
#define TREE_SIZE 50

typedef struct _Node
{
	void* parent;
	void* left;
	void* right;
	uint16_t data;
	uint16_t same;
} Node;

void createTree(_Out_ Node* *parents, _In_ uint16_t* data, size_t dataSize);
Node* addLeaf(_In_ Node* parents, uint16_t newData);
Node* removeLeaf(_In_ Node* parents, uint16_t targetData);
void printTree(_In_ Node* root);
Node* root = NULL;

uint8_t main(void) {
	

#ifndef RANDOM
	uint16_t data[20] = { 0,1,2,3,7,7,8,4,11,12, 4, 14, 15, 17,19 };
	size_t size = sizeof(data) / sizeof(data[0]);
	uint16_t rand1 = 4;
	uint16_t rand2 = 14;
	uint16_t rand3 = 4;
#endif // !RANDOM
#ifdef RANDOM
	uint16_t data[TREE_SIZE];
	size_t size = sizeof(data) / sizeof(data[0]);
	srand(time(NULL));
	for (int i = 0; i < size; i++) {
		data[i] = rand() % size;
	}
	uint16_t rand1 = rand() % size;
	uint16_t rand2 = rand() % size;
	uint16_t rand3 = rand() % size;
#endif // RANDOM
	

	createTree(&root, data, size);
	printf("\nOrignial Tree\n");
	printTree(root);

	printf("\nAfter Add these %d %d Leaf\n",30,2000);
	addLeaf(root, 30);
	addLeaf(root, 2000);
	printTree(root);

	printf("\nAfter delete these %d %d %d Leaf\n", rand1, rand2, rand3);
	removeLeaf(root, rand1);
	removeLeaf(root, rand2);
	removeLeaf(root, rand3);
	printTree(root);

	printf("\nPause! Please press any button");
	getchar();
	return 0;
}

void createTree(_Out_ Node* *parents, _In_ uint16_t* data, size_t dataSize) {
	((Node*)*parents) = (Node*)malloc(sizeof(Node));
	((Node*)*parents)->parent = NULL;
	((Node*)*parents)->left = NULL;
	((Node*)*parents)->right = NULL;
	((Node*)*parents)->same = 0;
	((Node*)*parents)->data = data[0];

	for (int i = 1; i < dataSize; i++) {
		addLeaf(((Node*)*parents), data[i]);
	}
}
void printTree(_In_ Node* parents) {
	if (parents->left != NULL) {
		printTree(parents->left);
		//printf("%d:%d ", parents->data, parents->same + 1
		printf("%d ", parents->data);
	}
	if (parents->right != NULL) {
		if (parents->left == NULL) {
			//printf("%d:%d ", parents->data, parents->same + 1);
			printf("%d ", parents->data);
		}
		printTree(parents->right);
	}
	if (parents->left == NULL && parents->right == NULL) {
		//printf("%d:%d ", parents->data, parents->same + 1);
		printf("%d ", parents->data);
	}
}

Node* addLeaf(_In_ Node* parents, uint16_t newData) {
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
			addLeaf(parents->left, newData);
		}
	}
	else if (newData > parents->data) {
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
			addLeaf(parents->right, newData);
		}
	}
	else {
		parents->same += 1;
		return parents;
	}
	return NULL;
}

Node* removeLeaf(_In_ Node* parents, uint16_t targetData) {
	if (targetData < parents->data) {
		if((Node*)parents->left != NULL)
			removeLeaf((Node*)parents->left, targetData);//Turn Left
		else {
			printf("\nNot Found%d\n", targetData);
		}
	}
	else if (targetData > parents->data) {
		if ((Node*)parents->right != NULL)
			removeLeaf((Node*)parents->right, targetData);//Turn Right
		else {
			printf("\nNot Found%d\n", targetData);
		}
	}
	else {
		if (parents->left != NULL && parents->right == NULL) { //Only Left
			Node* targetLeftLeaf = ((Node*)parents->left);
			parents->data = targetLeftLeaf->data;
			parents->right = targetLeftLeaf->right;
			parents->left = targetLeftLeaf->left;
			free(targetLeftLeaf);//free memory
		}
		else if (parents->left == NULL && parents->right != NULL) { //Only Right
			Node* targetRightLeaf = ((Node*)parents->right);
			parents->data = targetRightLeaf->data;
			parents->right = targetRightLeaf->right;
			parents->left = targetRightLeaf->left;
			free(targetRightLeaf);//free memory
		}
		else if (parents->left != NULL && parents->right != NULL) { //Both Side
			parents->data = ((Node*)parents->parent)->data;
		}
		else if (parents->left == NULL && parents->right == NULL) { //No Any Leaf
			if (((Node*)parents->parent)->left == parents) {
				((Node*)parents->parent)->left = NULL;
			}
			else if(((Node*)parents->parent)->right == parents){
				((Node*)parents->parent)->right = NULL;
			}
			free(parents);
		}
	}
}
