#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    char ime[MAX];
    char prezime[MAX];
    int bodovi;
}Student;

float RelativanBrojBodova(int);


int main(void) {
    Student *studenti;
    studenti=(Student*)malloc(sizeof(Student));
    FILE *fp;
    fp = fopen("C:\\Users\\leona\\Desktop\\Vice\\StrukturePodataka\\domaci1\\studenti.txt", "r");
    if(fp==NULL) {
        printf("Greska prilikom otvaranja datoteke.");
        return 1;
    }
    int n=0;
    while(fgetc(fp)!='\n');
    while(!feof(fp)) {
        studenti = (Student*)realloc(studenti, (n + 1) * sizeof(Student));
        fscanf(fp,"%s %s %d", studenti[n].ime, studenti[n].prezime, &studenti[n].bodovi);
        n++;
    }

    float relBrBod=0;
    for(int i=0;i<n;i++) {
        relBrBod=RelativanBrojBodova(studenti[i].bodovi);
        printf("%s\t%s\t%d\t%f\n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi, relBrBod);
        relBrBod=0;
    }

    fclose(fp);
    free(studenti);
    return 0;
}

float RelativanBrojBodova(int bodovi) {
    float relBrBod=0;
    relBrBod=((float)bodovi/100)*100;
   return relBrBod;
}
