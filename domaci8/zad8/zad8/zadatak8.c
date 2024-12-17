#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tree;
typedef struct tree* treePos;
typedef struct tree {
	int value;
	treePos right;
	treePos left;
}Tree;

treePos Insert(int,treePos);
treePos CreateTree(int);
void InOrder(treePos);
void PreOrder(treePos);
void PostOrder(treePos);
void LevelOrder(treePos);
int Search(int,treePos);
treePos Delete(int, treePos);
treePos FindMin(treePos);

int main(void) {
	treePos rootPtr = CreateTree(5);
	Insert(3, rootPtr);
	Insert(7, rootPtr);
	Insert(2, rootPtr);
	Insert(4, rootPtr);
	Insert(6, rootPtr);
	Insert(8, rootPtr);

	printf("InOrder: ");
	InOrder(rootPtr);

	printf("\nPreOrder: ");
	PreOrder(rootPtr);

	printf("\nPostOrder: ");
	PostOrder(rootPtr);

	printf("\nLevelOrder: ");
	LevelOrder(rootPtr);

	if (Search(6, rootPtr) == 0)
		printf("\nNema tog elementa(6) u stablu.");
	else
		printf("\nElement 6 postoji u stablu."); 

	if (Search(9, rootPtr) == 0)
		printf("\nNema tog elementa(9) u stablu.");
	else
		printf("\nElement 9 postoji u stablu.");

	rootPtr = Delete(4, rootPtr);
	printf("\nInOrder nakon brisanja elementa: ");
	InOrder(rootPtr);
	

}

treePos Insert(int value,treePos root) {
	if (root == NULL)
		return CreateTree(value);

	if (root->value > value) {
		root->left = Insert(value, root->left);
	}
	else
	{
		root->right = Insert(value, root->right);
	}

	return root;
}

treePos CreateTree(int value) {
	treePos temp = (treePos)malloc(sizeof(Tree));
	if (temp == NULL) {
		printf("Nema mjesta u memoriji.");
		return NULL;
	}
	temp->value = value;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

void InOrder(treePos root) {
	if (root == NULL)
		return;

	InOrder(root->left);
	printf("%d ", root->value);
	InOrder(root->right);

}

void PreOrder(treePos root) {
	if (root == NULL)
		return;

	printf("%d ", root->value);
	PreOrder(root->left);
	PreOrder(root->right);
}

void PostOrder(treePos root) {
	if (root == NULL)
		return;

	PostOrder(root->left);
	PostOrder(root->right);
	printf("%d ", root->value);
}

void LevelOrder(treePos root) {
	if (root == NULL)
		return;
	treePos queue[100];
	int front = 0, rear = 0;
	queue[rear++] = root;

	while (front != rear) {
		treePos current = queue[front++];
		printf("%d ", current->value);

		if (current->left != NULL)
			queue[rear++] = current->left;
		if (current->right != NULL)
			queue[rear++] = current->right;
	}
}

int Search(int value, treePos root) {
	if (root == NULL)
		return 0;
	if (root->value == value)
		return 1;
	else if (root->value > value)
		return Search(value, root->left);
	else
		return Search(value, root->right);
}

treePos Delete(int value, treePos root) {
	if(root==NULL)
		return root;

	else if(root->value>value)
		root->left=Delete(value, root->left);
	else if (root->value < value)
		root->right=Delete(value, root->right);
	else {
		if (root->right == NULL && root->left ==NULL) {
			free(root);
			return NULL;
		}
		else if (root->right == NULL) {
			treePos temp = root;
			root = root->left;
			free(temp);
			return root;
		}
		else if (root->left == NULL) {
			treePos temp = root;
			root = root->right;
			free(temp);
			return root;	
		}
		else {
			treePos temp = FindMin(root->right);
			root->value = temp->value;
			root->right = Delete(temp->value, root->right);
			return root;
		}
	}

	return root;
}

treePos FindMin(treePos root) {
	if (root == NULL)
		return NULL;
	while (root->left != NULL)
		root = root->left;
	return root;
}
