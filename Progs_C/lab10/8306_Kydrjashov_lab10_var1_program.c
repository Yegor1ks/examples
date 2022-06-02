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
} element;


typedef struct Head{
    struct element *first;
    struct element *current;
    struct element *last;
    int amount;
} Head;

void cls(int syst);

struct Head* initHead(struct Head *head);
struct Head* addElement(struct info inf0, struct Head *head);
void printList(struct Head *head, int print);
struct Head* addUnknown(struct info inf0, int position, struct Head *head);

char **ClStAr(char **s2, int n);
char **simple_split(char *str, int length, char sep);
struct Head* Leg(char **s2, inf0 *MASS, int mm, struct Head *head);

int main(){
    char **s2=NULL;
    int nn, len0, len1, i, j, n, m, mm, pr, known, print, syst;
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
            print = 0;
            printf("Information in file:\n");
            printList(head, print);
            fclose(f);

            printf("Choose number of new element from the table: ");
            scanf("%d", &known);
            known = mm - known;

            if(known <= mm){
                printf("Input <Name;Extraction;MinkHz;MaxkHz;Strings;Options;MaxSizeX;MaxSizeY>\n");
                fflush(stdin);
                fgets(f2, MAXLEN, stdin);
                n = strlen(f2);
                f2[n-1]='\0';
                s2 = simple_split(f2, n, sep);
                if(s2){
                    ELEM = (inf0*)malloc(1*sizeof(inf0));
                    head = Leg(s2, ELEM, 0, head);
                    head = addUnknown(ELEM[0], known, head);
                    printf("New information:\n");
                    print = 1;
                    printList(head, print);
                    s2 = ClStAr(s2, 5);
                }
            }
            else printf("Wrong number!\n");
        }
    }
    else printf("False name of file or no such file\n");

    return 0;
}

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
    if(element->id == 0){
        head->first = element;
        head->last = element;
    }
    else{
        head->last->next = element;
        head->last = element;
    }
    return head;
}

void printList(struct Head *head, int print){
    int counter = 0, j;
    if(head->amount != 0){
        head->current = head->first;
        printf("+---+---------------------+---------------------+---------------------+---------+---------+----------------+\n");
        printf("| N |%20s |%20s |%20s |%8s |%8s |%15s |\n", "Name", "Extraction", "Min & max kHz", "Strings", "Options", "Max size, cm");
        printf("+---+---------------------+---------------------+---------------------+---------+---------+----------------+\n");
        if(print == 0) printf("|%2d ", head->amount);
        else printf("| 1 ");
        printf("|%20s |%20s | %8f & %8f |%8d |%8d |", head->current->inf0.name,head->current->inf0.ext, head->current->inf0.minhz, head->current->inf0.maxhz, head->current->inf0.st, head->current->inf0.opt);
        for(j=0; j<2; j++){
            printf("%7d", head->current->inf0.xsize[j]);
            if(j==0) printf(" x");
        }
        printf("|\n+---+---------------------+---------------------+---------------------+---------+---------+----------------+\n");

        for(counter = 1; counter < head->amount; counter++){
            head->current = head->current->next;
            if(print == 0) printf("|%2d ", head->amount - counter);
            else printf("|%2d ", counter+1);
            printf("|%20s |%20s | %8f & %8f |%8d |%8d |", head->current->inf0.name,head->current->inf0.ext, head->current->inf0.minhz, head->current->inf0.maxhz, head->current->inf0.st, head->current->inf0.opt);
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

struct Head* addUnknown(struct info inf0, int position, struct Head *head){
    int counter;
    struct element *element;
    element = (struct element*)malloc(1 * sizeof(struct element));
    element->inf0 = inf0;

    if(position < 0){
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
