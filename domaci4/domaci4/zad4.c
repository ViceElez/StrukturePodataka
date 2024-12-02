#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LINE 1024

struct _element;
typedef struct _element* Pointer;
typedef struct _element {
    int koef;
    int exp;
    Pointer next;
}element;

void readFromFile(Pointer);
void readFromFile2(Pointer);
Pointer create(int, int);
void sort(Pointer, Pointer);
void insertAfter(Pointer, Pointer);
void print(Pointer);
Pointer addPolinom(Pointer, Pointer, Pointer);
Pointer multipyPolinom(Pointer, Pointer, Pointer);


int main() {

    element head, head2, headAdd, headTimes;
    head.next = NULL;
    head2.next = NULL;
    headAdd.next = NULL;
    headTimes.next = NULL;

    readFromFile(&head);
    readFromFile2(&head2);
    print(head.next);
    print(head2.next);

    addPolinom(&head, &head2, &headAdd);
    print(headAdd.next);

    multipyPolinom(&head, &head2, &headTimes);
    print(headTimes.next);



    return 0;
}

void readFromFile(Pointer P) {
    FILE* f;
    f = fopen("FileZa4Zad.txt", "r");
    Pointer newEl;
    int e = 0, c = 0;

    if (!f) {
        printf("Greska pri otvaranju datoteke");
    }

    while (feof(f) == 0)
    {
        if (fscanf(f, " %d %d", &c, &e) == 2) {
            newEl = create(c, e);
            sort(P, newEl);
        }
    }
    fclose(f);


}

Pointer create(int c, int e) {
    Pointer newEl;
    newEl = (Pointer)malloc(sizeof(element));

    if (!newEl) {
        printf("Neuspjela alokacija memorije");
    }

    newEl->exp = e;
    newEl->koef = c;
    newEl->next = NULL;

    return newEl;
}

void sort(Pointer P, Pointer newEl) {
    Pointer temp = P;

    while (temp->next != NULL && newEl->exp > temp->next->exp)
    {
        temp = temp->next;
    }

    if (temp->next != NULL && temp->next->exp == newEl->exp) {
        temp->next->koef += newEl->koef;
        free(newEl);
    }
    else {
        insertAfter(temp, newEl);
    }

}

void print(Pointer P) {
    while (P != NULL) {
        printf("(%d * X^%d )+", P->koef, P->exp);
        P = P->next;
    }
    puts("\n");
}

void insertAfter(Pointer P, Pointer new) {
    new->next = P->next;
    P->next = new;
}

void readFromFile2(Pointer P) {
    FILE* f;
    f = fopen("FileZa4Zad2polinom", "r");
    Pointer newEl;
    int e = 0, c = 0;

    if (!f) {
        printf("Greska pri otvaranju datoteke");
    }

    while (feof(f) == 0)
    {
        if (fscanf(f, " %d %d", &c, &e) == 2) {
            newEl = create(c, e);
            sort(P, newEl);
        }
    }
    fclose(f);
}

Pointer addPolinom(Pointer p1, Pointer p2, Pointer p) {
    Pointer temp1 = p1, temp2 = p2;
    while (temp1->next != NULL) {
        Pointer newEl = create(temp1->next->koef, temp1->next->exp);
        sort(p, newEl);
        temp1 = temp1->next;
    }

    while (temp2->next != NULL) {
        Pointer newEl = create(temp2->next->koef, temp2->next->exp);
        sort(p, newEl);
        temp2 = temp2->next;
    }
    return p;
}

Pointer multipyPolinom(Pointer p1, Pointer p2, Pointer p) {
    Pointer temp1 = p1, temp2 = p2;
    for (temp1 = p1; temp1->next != NULL; temp1 = temp1->next) {
        for (temp2 = p2; temp2->next != NULL; temp2 = temp2->next) {
            Pointer newEl = create(temp1->next->koef * temp2->next->koef, temp1->next->exp + temp2->next->exp);
            sort(p, newEl);
        }
    }
    return p;
}