#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum{
    MAXNAME=260,
    MAXLEN=512
};

typedef struct info{
    int id;
    char *name;
    char *ext;
    float minhz;
    float maxhz;
    int st;
    int opt;
    int *xsize;
    struct info *next;
} inf0;

typedef struct element{
    struct info inf0;
    int id;
    struct element *next;
    struct element *previous;
} element;

typedef struct Head{
    struct element *first;
    struct element *current;
    struct element *last;
    int amount;
} Head;

typedef struct inf2{
    int id;
    char *name;
    struct inf2 *next;
} inf2;

typedef struct element2{
    struct inf2 inf2;
    int id;
    struct element2 *next;
    struct element2 *previous;
} element2;

typedef struct Head2{
    struct element2 *first;
    struct element2 *current;
    struct element2 *last;
    int amount;
} Head2;

void cls(int syst){
    if(syst == 1) system("clear");
    else system("cls");
}

struct Head* initHead(struct Head *head){
    head = (struct Head*)malloc(1 * sizeof(struct Head));
    head->amount = 0;
    head->current = NULL;
    head->first = NULL;
    return head;
}

struct Head2* initHead2(struct Head2 *Head2){
    Head2 = (struct Head2*)malloc(1 * sizeof(struct Head2));
    Head2->amount = 0;
    Head2->current = NULL;
    Head2->first = NULL;
    return Head2;
}

struct Head* addElement(struct info inf0, struct Head *head){
    struct element *element;
    element = (struct element*)malloc(1 * sizeof(struct element));

    element->id = head->amount;
    element->inf0 = inf0;
    head->amount = head->amount + 1;
    if(element->id == 0) {
        head->first = element;
        head->last = element;
    }
    else{
        element->previous = head->last;
        head->last->next = element;
        head->last = element;
    }

    return head;
}

struct Head2* addelement2(struct inf2 inf2, struct Head2 *Head2){
    struct element2 *element2;
    element2 = (struct element2*)malloc(1 * sizeof(struct element2));

    element2->id = Head2->amount;
    element2->inf2 = inf2;
    Head2->amount = Head2->amount + 1;
    if(element2->id == 0) {
        Head2->first = element2;
        Head2->last = element2;
    }
    else{
        element2->previous = Head2->last;
        Head2->last->next = element2;
        Head2->last = element2;
    }

    return Head2;
}

void printList(struct Head *head){
    int counter = 0, j;
    if(head->amount != 0){
        head->current = head->first;
        printf("+---+---------------------+---------------------+---------------------+---------+---------+----------------+\n");
        printf("| N |%20s |%20s |%20s |%8s |%8s |%15s |\n", "Name", "Extraction", "Min & max kHz", "Strings", "Options", "Max size, cm");
        printf("+---+---------------------+---------------------+---------------------+---------+---------+----------------+\n");
        printf("| 1 |%20s |%20s | %8f & %8f |%8d |%8d |", head->current->inf0.name, head->current->inf0.ext, head->current->inf0.minhz, head->current->inf0.maxhz, head->current->inf0.st, head->current->inf0.opt);
        for(j=0; j<2; j++){
            printf("%7d", head->current->inf0.xsize[j]);
            if(j==0) printf(" x");
        }
        printf("|\n+---+---------------------+---------------------+---------------------+---------+---------+----------------+\n");

        for(counter = 1; counter < head->amount; counter++){
            head->current = head->current->next;
            printf("|%2d |%20s |%20s | %8f & %8f |%8d |%8d |", counter+1, head->current->inf0.name, head->current->inf0.ext, head->current->inf0.minhz, head->current->inf0.maxhz, head->current->inf0.st, head->current->inf0.opt);
            for(j=0; j<2; j++){
                printf("%7d", head->current->inf0.xsize[j]);
                if(j==0) printf(" x");
            }
            printf("|\n+---+---------------------+---------------------+---------------------+---------+---------+----------------+\n");
        }
        printf("\n");
    }
    else printf("No elements in list\n");
}

void printList1(struct Head2 *Head2, struct Head *Head){
    int counter = 0, j;
    if(Head2->amount != 0){
        Head2->current = Head2->first;

        printf("+---+---------------------+---------------------+---------------------+---------+---------+----------------+\n");
        printf("| N |%20s |%20s |%20s |%8s |%8s |%15s |\n", "Name", "Extraction", "Min & max kHz", "Strings", "Options", "Max size, cm");
        printf("+---+---------------------+---------------------+---------------------+---------+---------+----------------+\n");
        printf("| 1 |%20s |%20s | %8f & %8f |%8d |%8d |", Head2->current->inf2.elm->name, Head2->current->inf2.elm->ext, Head2->current->inf2.elm->minhz, Head2->current->inf2.elm->maxhz, Head2->current->inf2.elm->st, Head2->current->inf2.elm->xsize);
        for(j=0; j<2; j++){
            printf("%7d", Head2->current->inf2.elm->xsize[j]);
            if(j==0) printf(" x");
        }
        printf("|\n+---+---------------------+---------------------+---------------------+---------+---------+----------------+\n");

        for(counter = 1; counter < Head2->amount; counter++){
            Head2->current = Head2->current->next;
            printf("| 1 |%20s |%20s | %8f & %8f |%8d |%8d |", Head2->current->inf2.elm->name, Head2->current->inf2.elm->ext, Head2->current->inf2.elm->minhz, Head2->current->inf2.elm->maxhz, Head2->current->inf2.elm->st, Head2->current->inf2.elm->xsize);
            for(j=0; j<2; j++){
                printf("%7d", Head2->current->inf2.elm->xsize[j]);
                if(j==0) printf(" x");
            }
            printf("|\n+---+---------------------+---------------------+---------------------+---------+---------+----------------+\n");
        }
        printf("\n");
    }
    else printf("No element1s in list\n");
}

void printList2(struct Head2 *Head2){
    int counter = 0, j;
    if(Head2->amount != 0){
        Head2->current = Head2->first;
        printf("+---+---------------------+\n");
        printf("| N |%20s |\n", "Name");
        printf("+---+---------------------+\n");
        printf("| 1 |%20s |", Head2->current->inf2.name);
        printf("\n+---+---------------------+\n");

        for(counter = 1; counter < Head2->amount; counter++){
            Head2->current = Head2->current->next;
            printf("|%2d |%20s |", counter+1, Head2->current->inf2.name);
            printf("\n+---+---------------------+\n");
        }
        printf("\n");
    }
    else printf("No element1s in list\n");
}

struct Head2* addUnknown(inf2 inf2, int position, struct Head2 *Head2){
    int counter;
    struct element2 *element2;
    if(position > -1 && position < Head2->amount) {
        element2 = (struct element2*)malloc(1 * sizeof(struct element2));
        element2->inf2 = inf2;

        if(position == 0) {
            element2->next = Head2->first;
            Head2->first->previous = element2;
            Head2->first = element2;
        }
        else{
            Head2->current = Head2->first;
            for (counter = 0; counter < Head2->amount; counter++) {
                if(counter == position - 1){
                    element2->next = Head2->current->next;
                    element2->previous = Head2->current;
                    Head2->current->next = element2;
                }
                else Head2->current = Head2->current->next;
            }
        }
        Head2->amount++;
    }
    else{
        if(position == Head2->amount) Head2 = addelement2(inf2, Head2);
    }

    return Head2;
}

char **ClStAr(char **s2, int n){
    int i;
    for(i=0; i<n; i++){
        free(s2[i]);
        s2[i] = NULL;
    }
    free(s2);
    s2 = NULL;

    return s2;
}

char **simple_split(char *str, int length, char sep){
    char **str_array=NULL;
    int i, j, k, m;
    int key,count;
    for(j=0,m=0;j<length;j++){
        if(str[j]==sep) m++;
    }
    key=0;
    str_array=(char**)malloc((m+1)*sizeof(char*));
    if(str_array){
        for(i=0, count=0; i<=m; i++, count++){
            str_array[i]=(char*)malloc(length*sizeof(char));
            if(str_array[i]) key=1;
            else{
                key=0;
                i=m;
            }
        }
        if(key){
            for(j=0, k=0, m=0; j<length; j++){
                if(str[j]!=sep) str_array[m][j-k]=str[j];
                else{
                    str_array[m][j-k]='\0';
                    k=j+1;
                    m++;
                }
            }
        }
     }
     if(m != 7){
        printf("Wrong element!\n");
        if(str != NULL) str_array = ClStAr(str_array, count+1);
     }
     return str_array;
}

struct Head* Leg(char **s2, inf0 *MASS, int mm, struct Head *head){
    int len0, len1, j;
    len0 = strlen(s2[0]);
    len1 = strlen(s2[1]);
    MASS[mm].name=(char*)malloc((len0+1)*sizeof(char));
    MASS[mm].ext=(char*)malloc((len1+1)*sizeof(char));
    MASS[mm].xsize=(int*)malloc(2*sizeof(int));

    if(MASS[mm].name && MASS[mm].ext && MASS[mm].xsize){
        strcpy(MASS[mm].name, s2[0]);
        strcpy(MASS[mm].ext, s2[1]);
        MASS[mm].minhz=atof(s2[2]);
        MASS[mm].maxhz=atof(s2[3]);
        MASS[mm].st=atoi(s2[4]);
        MASS[mm].opt=atoi(s2[5]);
        for(j=0; j<2; j++) MASS[mm].xsize[j]=atoi(s2[6+j]);
        head = addElement(MASS[mm], head);
    }
    return head;
}

struct Head2* Leg2(char **s2, inf2 *LIST, int mm, struct Head2 *Head2){
    int len;
    len = strlen(s2[0]);
    LIST[mm].name=(char*)malloc((len+1)*sizeof(char));

    if(LIST[mm].name){
        strcpy(LIST[mm].name, s2[0]);
        Head2 = addelement2(LIST[mm], Head2);
    }
    return Head2;
}

struct Head2* deleteFirstelement2(struct Head2 *Head2){
    if(Head2->amount != 0) {
        if(Head2->amount == 1) {
            Head2->first = NULL;
            Head2->last = NULL;
            Head2->amount--;
        }
        else{
            Head2->first->next->previous = NULL;
            Head2->first = Head2->first->next;
            Head2->amount--;
        }
    }
    else printf("Nothing to delete\n");

    return Head2;
}

struct Head2* deleteLastelement2(struct Head2 *Head2){
    int counter;
    if(Head2->amount != 0) {
        if(Head2->amount == 1) {
            Head2->first = NULL;
            Head2->last = NULL;
            Head2->amount--;
        }
        else{
            if(Head2->amount == 2) {
                Head2->first->next = NULL;
                Head2->last = Head2->first;
                Head2->amount--;
            }
            else{
                Head2->current = Head2->first;
                for (counter = 0; counter < Head2->amount - 2; counter++) Head2->current = Head2->current->next;
                Head2->current->next = NULL;
                Head2->last = Head2->current;
                Head2->amount--;
            }
        }
    }
    else printf("Nothing to delete\n");

    return Head2;
}

struct Head2* deleteelement2(struct Head2 *Head2, int element2){
    int counter;

    if(element2 > -1 && element2 < Head2->amount) {
        if(Head2->amount != 0) {
            if(element2 == 0) Head2 = deleteFirstelement2(Head2);
            else{
                if(element2 == Head2->amount - 1) Head2 = deleteLastelement2(Head2);
                else{
                    Head2->current = Head2->first;
                    for (counter = 0; counter < Head2->amount; counter++) {
                        if(counter == element2 - 1) {
                            Head2->current->next = Head2->current->next->next;
                            Head2->current->next->previous = Head2->current;
                        }
                        else Head2->current = Head2->current->next;
                    }
                    Head2->amount--;
                }
            }
        }
        else printf("Nothing to delete\n");
    }
    else printf("element %d is out of range\n", element2);

    return Head2;
}

struct Head* deleteFirstElement(struct Head *head){

    if(head->amount != 0) {
        if(head->amount == 1) {
            head->first = NULL;
            head->last = NULL;
            head->amount--;
        }
        else{
            head->first->next->previous = NULL;
            head->first = head->first->next;
            head->amount--;
        }
    }
    else printf("nothing to delete :(\n");

    return head;
}

struct Head* deleteLastElement(struct Head *head){
    int counter;
    if(head->amount != 0) {
        if(head->amount == 1) {
            head->first = NULL;
            head->last = NULL;
            head->amount--;
        }
        else{
            if(head->amount == 2) {
                head->first->next = NULL;
                head->last = head->first;
                head->amount--;
            }
            else{
                head->current = head->first;
                for (counter = 0; counter < head->amount - 2; counter++) head->current = head->current->next;
                head->current->next = NULL;
                head->last = head->current;
                head->amount--;
            }
        }
    }
    else printf("nothing to delete\n");

    return head;
}

struct Head* deleteElement(struct Head *head, int element) {
    int counter;

    if(element > -1 && element < head->amount) {
        if(head->amount != 0) {
            if(element == 0) head = deleteFirstElement(head);
            else{
                if(element == head->amount - 1) head = deleteLastElement(head);
                else{
                    head->current = head->first;
                    for (counter = 0; counter < head->amount; counter++) {
                        if(counter == element - 1) {
                            head->current->next = head->current->next->next;
                            head->current->next->previous = head->current;
                        }
                        else head->current = head->current->next;
                    }
                    head->amount--;
                }
            }
        }
        else printf("nothing to delete :(\n");
    }
    else printf("element %d is out of range", element);

    return head;
}

struct Head2* addToPlace(struct Head2* Head2, inf2 *LIST){
    inf2 *ELEM;
    int known1, known2;
    ELEM = (inf2*)malloc(1*sizeof(inf2));

    printf("Choose number of element to replace from the table: ");
    //getchar();
    scanf("%d", &known1);
    //printf("%d\n", Head2->amount);
    known1--;
    if(known1 >= 0 && known1 < Head2->amount){
        printf("Choose position to place the element1: ");
        scanf("%d", &known2);
        known2--;

        if(known2 >= -1){
            //ELEM = (inf2*)malloc(1*sizeof(inf2));
            ELEM[0] = LIST[known1];
            if(known2 == -1) addUnknown(ELEM[0], 0, Head2);
            else{
                if(known2 < Head2->amount) Head2 = deleteelement2(Head2, known2);
                else known2 = Head2->amount;
                Head2 = addUnknown(ELEM[0], known2, Head2);
            }
        }
        else printf("False number!\n");
    }
    else printf("Too big or too small number!\n");

    return Head2;
};

int main(){
    char **s2=NULL;
    int nn, len0, len1, i, j, n, m, mm, pr, print, syst;
    inf0 *MASS;
    inf2 *LIST;
    char fl[MAXLEN], sep, f2[MAXLEN], yes, choose;
    FILE *f;

    printf("Input [1] if you on Linux or any else if you on Windows\n");
    scanf("%d", &syst);
    getchar();
    printf("Open program in full screen or the optimal width to display the table is 115\nPress 1 to OK\n");
    scanf("%c", &yes);
    cls(syst);

    if(yes == '1'){
        Head* head=NULL;
        Head2* Head2=NULL;
        head = initHead(head);
        Head2 = initHead2(Head2);
        f = fopen("CSV.txt", "r");
        sep=';';
        if(f){
            mm = MAXLEN;
            for(i=0, m=0; i<mm; i++){
                fgets(fl, MAXNAME, f);
                n = strlen(fl);
                if(fl[n-1]=='\n') m++;
                else{
                    m++;
                    mm=m;
                    i=mm;
                }
                if(i!=mm) fl[n-1]='\0';
            }
            rewind(f);
            MASS=(inf0*)malloc(mm*sizeof(inf0));
            LIST=(inf2*)malloc(mm*sizeof(inf2));
            if(MASS){
                for(i=0; i<mm; i++){
                    fgets(fl, MAXNAME, f);
                    n = strlen(fl);
                    if(i!=(mm-1)) fl[n-1]='\0';
                    else fl[n]='\0';
                    n = strlen(fl);

                    s2 = simple_split(fl, n, sep);
                    if(s2){
                        head = Leg(s2, MASS, i, head);
                        Head2 = Leg2(s2, LIST, i, Head2);
                        s2 = ClStAr(s2, 5);
                    }
                    else printf("Row data not available!\n");
                }
            }
            else printf("Out of memory!\n");
            printf("Information in file:\n");
            printList2(Head2);
            fclose(f);

            Head2 = addToPlace(Head2, LIST);
            printf("\nNew information:\n");
            printList2(Head2);

            printList(head);

            printf("Input 1 to view all information\n");
            getchar();
            scanf("%c", &choose);

            printf("%s\n", head->current->inf0.name);

            if(choose == '1') printList1(Head2);
        }
    }
    else printf("False name of file or no such file\n");

    return 0;
}
