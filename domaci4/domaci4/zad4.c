#define _CRT_SECURE_NO_WARNINGS

#include <ctype.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct _struct;
typedef struct _struct* position;
typedef struct _struct {
    int coeff;
    int exp;
    position next;
} Polinom;

position createElement(int, int);
int sortInput(position, position);
int sumOfTwoLists(position, position, position);
int multiplicationOfTwoLists(position, position, position);
int ReadFromFile(position, FILE*);
int inserAfter(position,position);
int DeleteAfter(position);
int Print(position);
int lengthOfList(position);

int main(void) {
    Polinom head1 = {
        .coeff = 0
        , .exp = 0
    };

    Polinom head2 = {
        .coeff = 0
        , .exp = 0
    };

    Polinom headSum = {
        .coeff = 0
        , .exp = 0
    };

    Polinom headMultiply = {
        .coeff = 0
        , .exp = 0
    };

	FILE* fp1 =fopen("C:\\Users\\leona\\Desktop\\Vice\\StrukturePodataka\\domaci4\\polinom1.txt", "r");
	FILE* fp2 = fopen("C:\\Users\\leona\\Desktop\\Vice\\StrukturePodataka\\domaci4\\polinom2.txt", "r");

	ReadFromFile(&head1, fp1);
	ReadFromFile(&head2, fp2);

	Print(head1.next);
	printf("\n");

	Print(head2.next);
	printf("\n");
	printf("\n");

	sumOfTwoLists(head1.next, head2.next, &headSum);
	Print(headSum.next);
	printf("\n");
	printf("\n");

	multiplicationOfTwoLists(head1.next, head2.next, &headMultiply);
	Print(headMultiply.next);
	printf("\n");


    return 0;
}

position createElement(int tempCoeff, int tempExp) {
    position nE = NULL;
    nE = (position)malloc(sizeof(Polinom));
    if (nE == NULL) {
        printf("Greska pri stvaranju novog elementa");
        return NULL;
    }
    nE->coeff = tempCoeff;
    nE->exp = tempExp;
    nE->next = NULL;

    return nE;

}

int ReadFromFile(position ptr, FILE *fp) {
    if (fp == NULL) {
        printf("Greska pri otvaranju datoteke");
        return 1;
    }

    char buffer[200];
    while (fgets(buffer, sizeof(buffer), fp)) {
        int tempCoeff;
        int tempExp;
        int numBytes;
        int buf_num=0;

        while (sscanf(buffer+buf_num, "%d %d%n ", &tempCoeff, &tempExp,&numBytes) == 2) {
            sortInput(ptr, createElement(tempCoeff, tempExp));
			buf_num += numBytes;
        } 

    }
    fclose(fp);

    return 0;
}

int sortInput(position head, position nE) {
    position temp = head;
    while (temp->next != NULL && temp->next->exp < nE->exp) {
        temp = temp->next;
    }

    if (temp->next != NULL && temp->next->exp > nE->exp) {
        inserAfter(temp, nE);
    }
    else if (temp->next != NULL && temp->next->exp == nE->exp) {
        int sum = 0;
        sum = temp->next->coeff + nE->coeff;
        if (sum == 0) {
            DeleteAfter(temp);
        }
        free(nE);
    }
    else {
        inserAfter(temp, nE);
    }
}

int inserAfter(position prev, position nE) {
	nE->next = prev->next;
	prev->next = nE;

	return 0;
}

int DeleteAfter(position ptr) {
	position temp = ptr->next;
    ptr->next = ptr->next->next;
	free(temp);

	return 0;
}
 
int Print(position ptr) {
	while (ptr != NULL) {
		printf("%d %d ", ptr->coeff, ptr->exp);
		ptr = ptr->next;
	}
	return 0;
}

int sumOfTwoLists(position ptr1, position ptr2, position headSum) {
    while (ptr1!=NULL && ptr2!=NULL) {
            if (ptr1->exp == ptr2->exp) {
                int sum= ptr1->coeff + ptr2->coeff;
				if (sum != 0) {
                    sortInput(headSum, createElement(sum, ptr1->exp));
					ptr1 = ptr1->next;
					ptr2 = ptr2->next;
                    break;
                }
            }
            else if (ptr1->exp > ptr2->exp) {
				sortInput(headSum, createElement(ptr2->coeff, ptr2->exp));
				ptr2 = ptr2->next;
			}
            else if (ptr1->exp < ptr2->exp) {
				sortInput(headSum, createElement(ptr1->coeff, ptr1->exp));
				ptr1 = ptr1->next;
            }
    }

	while (ptr1 != NULL) {
		sortInput(headSum, createElement(ptr1->coeff, ptr1->exp));
		ptr1 = ptr1->next;
	}
    while (ptr2!=NULL)
    {
        sortInput(headSum, createElement(ptr2->coeff, ptr2->exp));
		ptr2 = ptr2->next;
    }
	return 0;
}

int multiplicationOfTwoLists(position ptr1, position ptr2, position headMultiply) {
    
    int maxLen = 0;
    if (lenghtOfList(ptr1) >= lenghtOfList(ptr2)) {
		maxLen = lenghtOfList(ptr1);
    }
    else {
		maxLen = lenghtOfList(ptr2);
    }
    
    while (maxLen != 0) {
        if (ptr1 == NULL) {
            sortInput(headMultiply, createElement(ptr2->coeff, ptr2->exp));
			ptr2 = ptr2->next;
            maxLen--;
        }
        else if (ptr2 == NULL) {
            sortInput(headMultiply, createElement(ptr1->coeff, ptr1->exp));
			ptr1 = ptr1->next;
            maxLen--;
        }
        else {
            headMultiply->coeff = ptr1->coeff * ptr2->coeff;
            headMultiply->exp = ptr1->exp + ptr2->exp;
            sortInput(headMultiply, createElement(headMultiply->coeff, headMultiply->exp));
			ptr1 = ptr1->next;
			ptr2 = ptr2->next;
            maxLen--;
        }

    }
       
    
	return 0;
}

int lenghtOfList(position ptr) {
	int len = 0;
	while (ptr != NULL) {
		len++;
		ptr = ptr->next;
	}
	return len;
}
