#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct directory;
typedef struct directory* dirPos;
typedef struct directory {
    char dirName[50];
    dirPos nexDir;
    dirPos parDir;
    dirPos childDir;
} Directory;


void MainMenu(dirPos);
dirPos CreateDirectory(char* name);
void AddDirectory(dirPos, dirPos);
void ChangeDirectory(dirPos* current, char* name);
void GoToParent(dirPos* current);
void ListDirectoryContents(dirPos current);
void RemoveNewline(char* str);

int main(void) {
    dirPos root = CreateDirectory("root");
    dirPos current = root;
    MainMenu(current);
    return 0;
}

void MainMenu(dirPos currentDir) {
    while (true) {
        printf("1 - md\n2 - cd dir\n3 - cd..\n4 - dir\n5 - Izlaz\n");
        printf("Upisite odabir: ");
        int choice;
        scanf("%d", &choice);
        getchar();
        switch (choice) {
        case 1: {
            printf("Upisite ime novog direktorija: ");
            char name[50];
            fgets(name, 50, stdin);
            RemoveNewline(name);
            dirPos newDir = CreateDirectory(name);
            AddDirectory(currentDir, newDir);
            break;
        }
        case 2: {
            printf("Ime direktorija kojem zelite pristupiti: ");
            char name[50];
            fgets(name, 50, stdin);
            RemoveNewline(name);
            ChangeDirectory(&currentDir, name);
            break;
        }
        case 3:
            GoToParent(&currentDir);
            break;
        case 4:
            ListDirectoryContents(currentDir);
            break;
        case 5:
            return;
        default:
            printf("Krivi unos");
            break;
        }
    }
}

dirPos CreateDirectory(char* name) {
    dirPos newDir = (dirPos)malloc(sizeof(Directory));
    if (newDir == NULL) {
        printf("Nema mjesta.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(newDir->dirName, name);
    newDir->childDir = NULL;
    newDir->nexDir = NULL;
    newDir->parDir = NULL;
    return newDir;
}

void AddDirectory(dirPos currentDir, dirPos newDir) {
    if (currentDir->childDir == NULL) {
        currentDir->childDir = newDir;
    }
    else {
        dirPos temp = currentDir->childDir;
        while (temp->nexDir != NULL) {
            temp = temp->nexDir;
        }
        temp->nexDir = newDir;
    }
    newDir->parDir = currentDir;
}

void ChangeDirectory(dirPos* current, const char* name) {
    dirPos temp = (*current)->childDir;
    while (temp != NULL) {
        if (strcmp(temp->dirName, name) == 0) {
            *current = temp;
            return;
        }
        temp = temp->nexDir;
    }
}

void GoToParent(dirPos* current) {
    if ((*current)->parDir != NULL) {
        *current = (*current)->parDir;
    }
    else {
        printf("Vec u rootu");
    }
}

void ListDirectoryContents(dirPos current) {
    if (current->childDir==NULL) {
        printf("Nema direktorija\n");
        return;
    }
    printf("Direktoriji:\n");
    dirPos temp = current->childDir;
    while (temp) {
        printf("- %s\n", temp->dirName);
        temp = temp->nexDir;
    }
}

void RemoveNewline(char* str) {
    char* newline = strchr(str, '\n');
    if (newline) *newline = '\0';
}
