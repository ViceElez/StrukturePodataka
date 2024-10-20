#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define MAX_SIZE 50
#define ERROR -1

struct _struct;
typedef  struct _struct* position;
typedef struct _struct{
    char name[MAX_SIZE];
    char surname[MAX_SIZE];
    int birthYear;
    position next;
}Person;



int AddBehindHead(position, char*,char*,int);
position CreatePerson(char*,char*,int);
int printList(position);
int AddAtEnd(position,char*,char*,int);
position FindBySurname(position,char*);
int Delete(position,char*);

int main(void)
{
   Person head={0,0,0,0};

    AddBehindHead(&head,"Josip","Jovic",2005); //a)

    printList(&head); //b)
    printf("\n");
    printf("\n");

    AddAtEnd(&head,"Ivan","Ivic",2000); //c)
    printList(&head);
    printf("\n");
    printf("\n");

    FindBySurname(&head,"Jovic"); //d)

    Delete(&head,"Josip");  //e)
    printList(&head);
    printf("\n");
    printf("\n");


    return 0;
}

position CreatePerson(char *name, char *surname, int birthYear) {
    position newPerson=NULL;
    newPerson=(position)malloc(sizeof(Person));
    if(newPerson==NULL) {
        printf("Nema mjesta u memoriji\n");
        return NULL;
    }

    strcpy(newPerson->name,name);
    strcpy(newPerson->surname,surname);
    newPerson->birthYear=birthYear;
    newPerson->next=NULL;
    return newPerson;
}

int AddBehindHead(position head, char *name, char *surname, int birthYear)
{
    position newPerson=NULL;
    newPerson=CreatePerson(name,surname,birthYear);
    if(newPerson==NULL) {
        return ERROR;
    }

    newPerson->next=head->next;
    head->next=newPerson;

    return 0;
}

int printList(position head)
{
    position ptr=head->next;
   if(ptr==NULL) {
       printf("Lista je prazna\n");
       return ERROR;
   }

    while(ptr!=NULL) {
        printf("%s %s %d\n", ptr->name, ptr->surname, ptr->birthYear);
        ptr=ptr->next;
    }
    return EXIT_SUCCESS;
}

int AddAtEnd(position head, char *name, char *surname, int birthYear)
{
    position newPerson=NULL;
    newPerson=CreatePerson(name,surname,birthYear);
    if(newPerson==NULL) {
        return ERROR;
    }
    position ptr=head;
    while(ptr->next!=NULL) {
        ptr=ptr->next;
    }
    ptr->next=newPerson;
    newPerson->next=NULL;
    return 0;
}

position FindBySurname(position head, char *surname)
{
    position ptr=head->next;
    if(ptr==NULL) {
        printf("Lista je prazna\n");
        return ERROR;
    }
    while(ptr!=NULL ) {
        if(strcmp(ptr->surname,surname)==0) {
            return ptr;
        }
        ptr=ptr->next;
    }

    return 0;
}

int Delete(position head,char *name) {
    position previous=head;
    position current=head->next;
    while(previous->next!=NULL) {
        if(strcmp((previous->next)->name,name)==0) {
         previous->next=current->next;
            free(current);
            return EXIT_SUCCESS;
        }
        previous=current;
        current=current->next;
    }
    printf("Osoba nije pronadjena\n");

    return ERROR;

}
