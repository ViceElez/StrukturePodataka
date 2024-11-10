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
int ReadFromFile(position);
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
        char* buf_ptr = buffer;

        if (sscanf(buffer, "%d %d%n ", &tempCoeff, &tempExp, &numBytes) == 2) {
            sortInput(ptr, createElement(tempCoeff, tempExp));
            buf_ptr += numBytes;
        } else {
            printf("Krivi format podataka u datoteci");
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
 
int Print(position head) {
	position temp = head->next;
	while (temp != NULL) {
		printf("%d %d ", temp->coeff, temp->exp);
		temp = temp->next;
	}
	return 0;
}

int sumOfTwoLists(position ptr1, position ptr2, position headSum) {
    int maxLen = 0;
    if (lenghtOfList(ptr1) > lenghtOfList(ptr2)) {
        maxLen = lenghtOfList(ptr1);
    }
    else {
        maxLen = lenghtOfList(ptr2);
    }

    while (maxLen > 0) {
            if (ptr1->exp == ptr2->exp) {
                int sum= ptr1->coeff + ptr2->coeff;
				if (sum == 0) {
					ptr1 = ptr1->next;
					ptr2 = ptr2->next;
					maxLen--;
                    break;
                }
				headSum->coeff = sum;
                sortInput(headSum, createElement(headSum->coeff, headSum->exp));
                ptr1 = ptr1->next;
                ptr2 = ptr2->next;
                maxLen--;
            }
            else if (ptr1->exp > ptr2->exp) {
				sortInput(headSum, createElement(ptr2->coeff, ptr2->exp));
				ptr2 = ptr2->next;
				maxLen--;
			}
            else if (ptr1->exp < ptr2->exp) {
				sortInput(headSum, createElement(ptr1->coeff, ptr1->exp));
				ptr1 = ptr1->next;
				maxLen--;
            }
    }
	return 0;
}

int multiplicationOfTwoLists(position ptr1, position ptr2, position headMultiply) {
	int maxLen = 0;
	if (lenghtOfList(ptr1) > lenghtOfList(ptr2)) {
		maxLen = lenghtOfList(ptr1);
	}
	else {
		maxLen = lenghtOfList(ptr2);
	}

    while (maxLen > 0) {
        if (ptr1 == NULL) {
            sortInput(headMultiply, createElement(ptr2->coeff, ptr2->exp));
        }
        else if (ptr2 == NULL) {
            sortInput(headMultiply, createElement(ptr1->coeff, ptr1->exp));
        }
        else {
			headMultiply->coeff = ptr1->coeff * ptr2->coeff;
			headMultiply->exp = ptr1->exp + ptr2->exp;
			sortInput(headMultiply, createElement(headMultiply->coeff, headMultiply->exp));
        }
		maxLen--;
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
