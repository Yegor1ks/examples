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
} inf0;

typedef struct Head{
    struct element *first;
    struct element *current;
    struct element *last;
    int amount;
} Head;

typedef struct element{
    struct info inf0;
    int id;
    struct element *next;
    struct element *previous;
} element;

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
    head->last->next = head->first;
    return head;
}

void printList(struct Head *head){
    int counter = 0, j;
    if(head->amount != 0){

        head->current = head->first;
        printf("+---+---------------------+\n");
        printf("| N |%20s |\n", "Name");
        printf("+---+---------------------+\n");
        printf("| 1 |%20s |", head->current->inf0.name);
        printf("\n+---+---------------------+\n");

        for(counter = 1; counter < head->amount; counter++){
            head->current = head->current->next;
            printf("|%2d |%20s |", counter+1, head->current->inf0.name);
            printf("\n+---+---------------------+\n");
        }
    }
    else printf("No elements in list\n");
}

struct Head* addUnknown(struct info inf0, int position, struct Head *head){
    int counter;
    struct element *element;
    element = (struct element*)malloc(1 * sizeof(struct element));
    element->inf0 = inf0;
    if(position > -1 && position < head->amount){
        if(position == 0){
            element->next = head->first;
            head->first = element;
        }
        else{
            head->current = head->first;
            for(counter = 0; counter < head->amount; counter++){
                if(counter == position - 1){
                    element->next = head->current->next;
                    head->current->next = element;
                }
                else head->current = head->current->next;
            }
        }
        //head->amount++;
    }else{
        if(position == head->amount){
            head = addElement(inf0, head);
        }
    }

    return head;
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
    int i,j,k,m;
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
        else{
            printf("Wrong element!\n");
            if(str != NULL) str_array = ClStAr(str_array, count+1);
        }
     }

     return str_array;
}

struct Head* Leg(char **s2, inf0 *MASS, int mm, struct Head *head){
    int len0, len1, j;
    len0 = strlen(s2[0]);
    MASS[mm].name=(char*)malloc((len0+1)*sizeof(char));

    if(MASS[mm].name){
        strcpy(MASS[mm].name, s2[0]);
        head = addElement(MASS[mm], head);
    }
    return head;
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

struct Head* deleteElement(struct Head *head, int element){
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

struct Head* addToPlace(struct Head* head, inf0 *MASS){
    inf0 *ELEM;
    int known1, known2;
    ELEM = (inf0*)malloc(1*sizeof(inf0));

    printf("Choose number of element to replace from the table: ");
    scanf("%d", &known1);
    known1--;
    if(known1 >= 0 && known1 < head->amount){
        printf("Choose position to place the element: ");
        scanf("%d", &known2);
        known2--;

        if(known2 >= -1){
            ELEM = (inf0*)malloc(1*sizeof(inf0));
            ELEM[0] = MASS[known1];
            if(known2 == -1) addUnknown(ELEM[0], 0, head);
            else{
                if(known2 < head->amount) head = deleteElement(head, known2);
                else known2 = head->amount;
                head = addUnknown(ELEM[0], known2, head);
            }
        }
        else printf("False number!\n");
    }
    else printf("Too big or too small number!\n");

    return head;
};

int main(){
    char **s2=NULL;
    int nn, len0, len1, i, j, n, m, mm, pr, print, syst, known;
    inf0 *MASS, *ELEM;
    char fl[MAXLEN], sep, f2[MAXLEN], yes;
    FILE *f;

    printf("Input [1] if you on Linux or any else if you on Windows\n");
    scanf("%d", &syst);
    getchar();
    printf("Open program in full screen or the optimal width to display the table is 115\nPress 1 to OK\n");
    scanf("%c", &yes);
    cls(syst);

    if(yes == '1'){
        Head* head=NULL;
        head = initHead(head);
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
                        s2 = ClStAr(s2, 5);
                    }
                    else printf("Row data not available!\n");
                }
            }
            else printf("Out of memory!\n");
            printf("Information in file:\n");
            printList(head);
            fclose(f);

            printf("Choose number of new element: ");
            scanf("%d", &known);

            printf("Input new element: ");
            getchar();
            fgets(f2, MAXLEN, stdin);
            n = strlen(f2);
            f2[n-1]='\0';

            s2 = simple_split(f2, n, sep);
            if(s2){
                ELEM = (inf0*)malloc(1*sizeof(inf0));
                head = Leg(s2, ELEM, 0, head);
                head = addUnknown(ELEM[0], known, head);
                printf("\nNew information:\n");
                printList(head);
                s2 = ClStAr(s2, 1);
            }
        }
    }
    else printf("False name of file or no such file\n");

    return 0;
}
