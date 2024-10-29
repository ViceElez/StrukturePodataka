
#define _CRT_SECURE_NO_WARNINGS

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define MAX_SIZE 50
#define ERROR -1

struct _struct;
typedef struct _struct* position;

typedef struct _struct{
    char name[MAX_SIZE];
    char lastName[MAX_SIZE];
    int birthYear;
    position next;
}Person;

position CreatePerson(char*, char* , int );

int PrependList(position, char* , char* , int );

int PrintList(position);

int AppendList(position, char* , char* , int );

position FindLast(position);

int InsertAfter(position, position );

int Delete(position, char* );

position findPrevious(position, char* );

position FindBySurname(position, char *);

int AddAfterCertainElement(position,char *, char *, int, char*);

int AddBeforeCertainElement(position,char *, char *, int, char*);

int SortListByLastName(position);

int InsertToFile(position);

int ReadListFromFile(position);





int main(){
    Person head = {
        .name = {0},
        .lastName = {0},
        .birthYear = 0,
        .next = NULL
    };

    Person head1 = {
        .name = {0},
        .lastName = {0},
        .birthYear = 0,
        .next = NULL
    };




    PrependList(&head, "Ivan", "Ivic", 1983);


    PrintList(head.next);


    AppendList(&head, "Ana", "Anic", 2001);
    AppendList(&head, "Mislav", "Misic", 2001);
    AppendList(&head, "Josip", "Jopic", 2001);
    PrintList(head.next);


    FindBySurname(head.next, "Anic");


    Delete(&head, "Ivan");
    PrintList(head.next);

    AddAfterCertainElement(head.next,"Toma","Tomic",2001,"Jopic");
    PrintList(head.next);

    AddBeforeCertainElement(&head,"Anka","Ankanov",2001,"Ana");
    PrintList(head.next);

    SortListByLastName(&head);
    PrintList(head.next);

    InsertToFile(head.next);

    ReadListFromFile(&head1);
    PrintList(head1.next);


    return 0;
}





position CreatePerson(char* name, char* lastName, int birthYear){
    position newPerson = NULL;
    newPerson = (position)malloc(sizeof(Person));
    if(newPerson == NULL){
        printf("Nema mista u memoriji\n");
        return NULL;
    }
    strcpy(newPerson->name, name);
    strcpy(newPerson->lastName, lastName);
    newPerson->birthYear = birthYear;
    newPerson->next = NULL;
    return newPerson;
}

int PrependList(position head, char* name, char* lastName, int birthYear){
    position newPerson = NULL;
    newPerson = CreatePerson(name, lastName, birthYear);
    if(newPerson == NULL){
        printf("Nije bilo moguce kreirat novu osobu");
        return ERROR;
    }
    InsertAfter(head, newPerson);
    return EXIT_SUCCESS;
}

int PrintList(position first){
    position temp = NULL;
    temp = first;
    printf("\n");
    while(temp != NULL){
        printf("%s %s %d\n", temp->name, temp->lastName, temp->birthYear);
        temp = temp->next;
    }
    return EXIT_SUCCESS;
}

int AppendList(position head, char* name, char* lastName, int birthYear){
    position newPerson = NULL;
    newPerson = CreatePerson(name, lastName, birthYear);
    if(newPerson == NULL){
        printf("Nije bilo moguce dodat novu osobu");
        return ERROR;
    }
    position last = NULL;
    last = FindLast(head);
    InsertAfter(last, newPerson);
    return EXIT_SUCCESS;
}

position FindLast(position head){
    position last = NULL;
    last = head;
    while(last->next != NULL){
        last = last->next;
    }
    return last;
}

int InsertAfter(position previous, position np){
    np->next = previous->next;
    previous->next = np;
    return EXIT_SUCCESS;
}

position FindBySurname(position first, char *surname){
    position temp = NULL;
    temp = first;
    while(temp){
        if(strcmp(surname, temp->lastName) == 0) return temp;
        temp = temp->next;
    }
    return NULL;
}

position findPrevious(position head, char* name){
    position current = NULL;
    current = head;
    while(current->next != NULL){
        if(strcmp((current->next)->name, name) == 0) {
            return current;
        }
        current=current->next;
    }
    return NULL;
}

int Delete(position head, char* name){
    position previous = findPrevious(head, name);
    position current = previous->next;
    previous->next = current->next;
    free(current);
    return EXIT_SUCCESS;
}

int AddAfterCertainElement(position ptr,char *name, char *lastName, int birthYear, char *findingLastName) {
    position np=CreatePerson(name,lastName,birthYear);
    position current=FindBySurname(ptr,findingLastName);
    InsertAfter(current,np);

    return 0;
}

int AddBeforeCertainElement(position head, char *name, char *lastName, int birthYear, char *findingLastName) {
    position np = CreatePerson(name, lastName, birthYear);
    position previous = findPrevious(head->next, findingLastName);
    if (previous == NULL) {
        np->next = head->next;
        head->next = np;
    } else {
        InsertAfter(previous, np);
    }

    return 0;
}

int SortListByLastName(position ptr) {
    position j, prev_j, temp, end=NULL;
    while(ptr->next!=end) {
        prev_j=ptr;
        j=ptr->next;
        while(j->next!=end) {
            if(strcmp(j->lastName,j->next->lastName)>0) {
                temp=j->next;
                prev_j->next=temp;
                j->next=temp->next;
                temp->next=j;
                j=temp;
            }
            prev_j=j;
            j=j->next;
        }
        end=j;
    }
}

int InsertToFile(position ptr) {
    if(ptr==NULL) {
        printf("Lista je prazna");
    }
    FILE *fp=NULL;
    fp=fopen("C:\\Users\\leona\\Desktop\\Vice\\StrukturePodataka\\domaci3\\datoteka.txt","w");
    if(fp==NULL) {
        printf("Dogodila se greska prilikom otvaranja datoteke");
        return 1;
    }
    while(ptr!=NULL) {
        fprintf(fp,"%s %s %d\n",ptr->name,ptr->lastName,ptr->birthYear);
        ptr=ptr->next;
    }

    fclose(fp);
    return 0;

}

int ReadListFromFile(position ptr) {
    FILE *fp=NULL;
    fp=fopen("C:\\Users\\leona\\Desktop\\Vice\\StrukturePodataka\\domaci3\\datotekaIzKojeCitamo.txt","r");
    if(fp==NULL) {
        printf("Dogodila se greska prilikom otvaranja datoteke");
        return 1;
    }

    char buffer[200];
    while (fgets(buffer, sizeof(buffer), fp)) {
        char tempName[50];
        char tempLastName[50];
        int tempBirthYear;

        if (sscanf(buffer, "%s %s %d", tempName, tempLastName, &tempBirthYear) == 3) {
            AppendList(ptr, tempName, tempLastName, tempBirthYear);
        }
        else
            printf("Krivi format podataka u datoteci");
    }

    fclose(fp);

    return 0;
}


