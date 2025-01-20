#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct tree;
typedef struct tree* treePos;
typedef struct tree {
	int value;
	treePos right;
	treePos left;
}Tree;

treePos Insert(int, treePos);
treePos CreateTree(int);
void inorderToFile(treePos, FILE*);

int main(void) {
	FILE* file = fopen("C:\\Users\\leona\\Desktop\\Vice\\StrukturePodataka\\domaci9\\zad9\\inline.txt", "w");
	if (file == NULL) {
		printf("Greska pri otvaranju datoteke.");
		return 1;
	}

	treePos rootPtr = CreateTree(5);
	Insert(2, rootPtr);
	Insert(5, rootPtr);
	Insert(7, rootPtr);
	Insert(8, rootPtr);
	Insert(11, rootPtr);
	Insert(1, rootPtr);
	Insert(4, rootPtr);
	Insert(2, rootPtr);
	Insert(3, rootPtr);
	Insert(7, rootPtr);
	inorderToFile(rootPtr, file);

	fprintf(file, "\n");
	replace(rootPtr);
	inorderToFile(rootPtr, file);


	int min = 10;
	int max = 90;
	int niz[10] = { 0 };
	srand(time(NULL));	
	for (int i = 0; i <= 1; i++)
	{
		Insert(((rand() % (max - min + 1)) + min),rootPtr);
	}
	fprintf(file, "\n");
	inorderToFile(rootPtr, file);

	fclose(file);
}

treePos Insert(int value, treePos root) {
	if (root == NULL)
		return CreateTree(value);

	if (root->value < value) {
		root->right = Insert(value, root->right);
	}
	else
	{
		root->left = Insert(value, root->left);
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

int replace(treePos root) {
	if (!root) return 0;

	int leftSum = replace(root->left);  
	int rightSum = replace(root->right); 

	int oldValue = root->value;  
	root->value = leftSum + rightSum; 

	return oldValue + root->value;
}

void inorderToFile(treePos root, FILE* file) {
    if (root==NULL) 
		return;

    inorderToFile(root->left, file);
    fprintf(file, "%d ", root->value);
    inorderToFile(root->right, file);
}
