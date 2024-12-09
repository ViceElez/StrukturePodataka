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
int ReadFromFile(Position);
void StackOperation(char, Position);
Position FindLast(Position);
int Pop(Position head);




int main(void) {

	Stack head = {
		.element = 0
		,.next = NULL
	};
	int num;


	num = ReadFromFile(&head);

	printf("rezultat je %d", num);


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
	if (ptr == NULL || head == NULL) return -1;
	Position prev = FindPrevious(ptr, head);
	if (prev == NULL) return -1;

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

int ReadFromFile(Position head) {
	FILE* f;
	f = fopen("C:/Users/jopab/OneDrive/Dokumenti/SP.24-25/pp/list.txt", "r");
	Position newNode = NULL;
	int number = 0;
	char ch[10];
	int i, num1, num2;


	if (f == NULL) {
		puts("Greska pri otvaranju dat");
		return 0;
	}


	while (feof(f) == 0) {
		number = 0;
		ch[0] = '\0';
		fscanf(f, "%s", ch);

		if (isdigit(ch[0]) != 0) {
			for (i = 0; ch[i] != '\0'; i++) {
				number = number * 10 + (ch[i] - '0');
			}
			newNode = CreateNode(number);
			InsertAfter(head, newNode);
			continue;
		}

		switch (ch[0])
		{
		case '+':
			num1 = Pop(head);
			num2 = Pop(head);
			newNode = CreateNode(num1 + num2);
			InsertAfter(head, newNode);
			break;

		case '-':
			num1 = Pop(head);
			num2 = Pop(head);
			newNode = CreateNode(num2 - num1);
			InsertAfter(head, newNode);
			break;

		case '*':
			num1 = Pop(head);
			num2 = Pop(head);
			newNode = CreateNode(num1 * num2);
			InsertAfter(head, newNode);
			break;

		case '/':
			num1 = Pop(head);
			num2 = Pop(head);
			newNode = CreateNode(num2 / num1);
			InsertAfter(head, newNode);
			break;

		default:
			break;



		}


	}
	num1 = Pop(head);
	return num1;


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

int Pop(Position head) {
	Position temp = head->next;
	int num = 0;
	num = temp->element;
	head->next = temp->next;
	free(temp);
	return num;

}