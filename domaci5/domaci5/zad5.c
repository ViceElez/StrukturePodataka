#define CRT_SECURE_NO_WARNINGS

#include <ctype.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>

struct _struct;
typedef struct _struct* Position;
typedef struct _struct {
	char element;
	Position next;
}Stack;

Position CreateNode(int);
int DeleteNode(Position, Position);
Position FindPrevious(Position, Position);
int InsertAfter(Position, Position);
int ReadFromFile(Position, FILE*);
void StackOperation(char, Position);
Position FindLast(Position);




int main(void) {

	Stack head = {
		.element = 0
		,.next = NULL
	};

	FILE* fp = fopen("C:\\Users\\leona\\Desktop\\Vice\\StrukturePodataka\\domaci5\\postifx.txt", "r");

	ReadFromFile(&head, fp);
}

Position CreateNode(int newElement) {
	Position newNode = NULL;
	newNode = (Position)malloc(sizeof(Stack));
	if (newNode == NULL) {
		printf("Greska pri stvaranju novog elementa");
		return NULL;
	}

	newNode->element = newElement;
	newNode->next = NULL;

	return newNode;
}

Position FindPrevious(Position curr, Position head) {
	Position temp = head;
	while (temp->next != NULL && temp->next != curr) {
		temp = temp->next;
		return temp;
	}

	return NULL;
}

int DeleteNode(Position ptr, Position head) {
	if (ptr==NULL || head==NULL) return -1;
	Position prev = FindPrevious(ptr, head);
	if (prev==NULL) return -1;

	prev->next = ptr->next;
	free(ptr);
	return 0;
}

int InsertAfter(Position previous, Position np) {
	np->next = previous->next;
	previous->next = np;
	return 0;
}

Position FindLast(Position head) {
	Position last = head->next;
	while (last->next != NULL) {
		last = last->next;
	}
	return last;
}

int ReadFromFile(Position head, FILE* fp) {
	Position newNode = NULL;
	int number = 0;
	char ch;
	bool isNumber = false; 

	if (fp == NULL) {
		printf("Greska pri otvaranju datoteke.\n");
		return 1;
	}

	while ((ch = fgetc(fp)) != EOF) {
		if (isdigit(ch)) {			
			number = number * 10 + (ch - '0');
			isNumber = true;
		}
		else {
			if (isNumber) {
				
				newNode = CreateNode(number);
				InsertAfter(head, newNode);
				number = 0;
				isNumber = false;
			}

			
			if (ch == '*' || ch == '+' || ch == '-' || ch == '/') {
				StackOperation(ch, head);
			}
		}
	}

	if (isNumber) {
		newNode = CreateNode(number);
		InsertAfter(head, newNode);
	}


	printf("Izraz je: %d\n", (head->next)->element);
	return 0;
}



void StackOperation(char operation, Position head) {
	Position last = FindLast(head);
	Position secondLast = FindPrevious(last, head);

	int result = 0;
	switch (operation) {
	case '+':
		result = secondLast->element + last->element;
		break;
	case '-':
		result = secondLast->element - last->element;
		break;
	case '*':
		result = secondLast->element * last->element;
		break;
	case '/':
		if (last->element != 0)
			result = secondLast->element / last->element;
		else {
			printf("Error: Division by zero\n");
			return;
		}
		break;
	}
	DeleteNode(last, head);
	DeleteNode(secondLast, head);

	Position newElem = CreateNode(result);
	InsertAfter(head, newElem);
}