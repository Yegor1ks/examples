#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum{
    MAXNAME = 260,
    MAXLEN = 260
};

typedef struct info{
    char *name;
    char *kind;
    int rank;
    int *rewards;
    char *team;
    struct info *next;
} info;

typedef struct Head{
    struct element *first;
    struct element *current;
    struct element *last;
    int amount;
} Head;

typedef struct element{
    struct info itemInfo;
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

struct Head* appendElement(struct info inf0, struct Head *head){
    struct element *element;
    element = (struct element*)malloc(1 * sizeof(struct element));
    element->next = NULL;
    element->previous = NULL;

    element->id = head->amount;
    element->itemInfo = inf0;
    head->amount++;
    if(element->id == 0){
        head->first = element;
        head->last = element;
    }
    else{
        head->last->next = element;
        element->previous = head->last;
        head->last = element;
    }
    return head;
}

void printList(struct Head *head){
    int counter = 0, j;
    if(head->amount != 0){
        head->current = head->first;
        printf("+----+---------------------+---------------------+------+---------------------+---------------------+\n");
        printf("|%3s |%20s |%20s |%5s |%20s |%20s |\n", "N", "Name", "Kind of sport", "Rank", "Number of rewards", "Team name");
        printf("+----+---------------------+---------------------+------+---------------------+---------------------+\n");

        for(counter = 0; counter < head->amount; counter++){
            printf("|%3d |%20s |%20s |%5d | %3d g, %3d s, %3d b |%20s |",
                    counter+1, head->current->itemInfo.name, head->current->itemInfo.kind, head->current->itemInfo.rank, head->current->itemInfo.rewards[0],
                    head->current->itemInfo.rewards[1], head->current->itemInfo.rewards[2], head->current->itemInfo.team);
            printf("\n+--------------------------+---------------------+------+---------------------+---------------------+\n");
            if(head->current != head->last)
                head->current = head->current->next;
        }
    }
    else printf("No elements in list\n");
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
    char **str_array = NULL;
    int i, j, k, m;
    int key;
    for(j=0,m=0;j<length;j++){
        if(str[j]==sep) m++;
    }
    key=0;
    str_array=(char**)malloc((m+1)*sizeof(char*));
    if(str_array){
        for(i=0; i<=m; i++){
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
     if(m != 6){
        printf("Wrong element %d !\n",m);
        if(str) str_array = ClStAr(str_array, m);
     }
     return str_array;
}

void disposeInfo(struct info *itemInfo){
  free((*itemInfo).name);
  free((*itemInfo).kind);
  free((*itemInfo).rewards);
  free((*itemInfo).team);
}

void parseInfo(char **s2, struct info *itemInfo){
    int len0, len1, len2, j;
    len0 = strlen(s2[0]);
    len1 = strlen(s2[1]);
    len2 = strlen(s2[6]);
    (*itemInfo).name = (char*)malloc((len0+2)*sizeof(char));
    (*itemInfo).kind = (char*)malloc((len1+2)*sizeof(char));
    (*itemInfo).rewards = (int*)malloc(4*sizeof(int));
    (*itemInfo).team = (char*)malloc((len2+2)*sizeof(char));

    if((*itemInfo).name && (*itemInfo).kind && (*itemInfo).rewards && (*itemInfo).team){
        strcpy((*itemInfo).name, s2[0]);
        strcpy((*itemInfo).kind, s2[1]);
        (*itemInfo).rank = atoi(s2[2]);
        for(j=0; j<3; j++) (*itemInfo).rewards[j]=atoi(s2[3+j]);
        strcpy((*itemInfo).team, s2[6]);
    }
    else printf("Out of memory!\n");
};

struct Head* prepareElement(char **s2, struct Head *head){
    info *itemInfo1;
    itemInfo1 = (info*)malloc(sizeof(info));
    parseInfo(s2, itemInfo1);
    head = appendElement(*itemInfo1, head);
    return head;
}

void insertRow(Head *head){
    info *MASSFromInput;
    char *person, sep;
    char **s2 = NULL;
    int n2;
    sep = ';';
    Head *head1;

    printf("\nInput <Name;kind of sport;rank;gold rewards;silver rewards;bronze rewards;team>\n");
    person = (char*)malloc(MAXLEN*sizeof(char));
    getchar();
    fgets(person, MAXLEN, stdin);
    n2 = strlen(person);
    person[n2-1] = '\0';

    MASSFromInput=(info*)malloc(1*sizeof(info));
    s2 = simple_split(person, n2, sep);
    if(s2){
        head1 = prepareElement(s2, head);
    }
    printf("Element have been added on the last place\n");
}

void deleteRow(Head *head){
    int choose = -1, counter = 0;
    if(head->amount == 0){
        printf("No information to delete\n");
    }
    else {
        while(choose != 0){
            printf("\nAll information:\n");
            printList(head);
            printf("\n0 - return to previous menu\nInput the row number to delete: ");
            scanf("%d", &choose);
            if(choose > head->amount){
                printf("Wrong row number. There are %d rows in database.\n", head->amount);
            }
            else{
                if((choose > 0) && (choose <= head->amount)){
                    head->current = head->first;
                    for(counter = 0; counter < choose - 1; counter++){
                        if(head->current != head->last) head->current = head->current->next;
                    }
                    if(head->current == head->first){
                        head->first = head->first->next;
                        head->first->previous = NULL;
                    }
                    else{
                        if(head->current == head->last){
                            head->last = head->last->previous;
                            head->last->next = NULL;
                        }
                        else{
                            head->current->next->previous = head->current->previous;
                            head->current->previous->next = head->current->next;
                        }
                    }

                    head->amount--;
                    free(head->current);
                    head->current = NULL;
                }
            }
        }
    }
}

void editRow(Head *head){
    int choose = -1, counter = 0;
    info *MASSFromEdit;
    char *person, sep;
    char **s2 = NULL;
    int n2;
    sep = ';';
    Head *head1;

    if(head->amount == 0) printf("No rows to edit.\n");
    else{
        while(choose != 0){
            printf("\nAll information:\n");
            printList(head);
            printf("Input the row number to edit\n0 - return to previous menu\n");
            scanf("%d", &choose);
            if(choose > head->amount){
                printf("Wrong row number. There are %d rows in database.\n", head->amount);
            }
            else{
                if((choose > 0) && (choose <= head->amount)){
                    head->current = head->first;
                    for(counter = 0; counter < choose - 1; counter++){
                        if(head->current != head->last)
                            head->current = head->current->next;
                    }
                }

                printf("\nInput <Name;kind of sport;rank;gold rewards;silver rewards;bronze rewards;team>\n");
                person = (char*)malloc(MAXLEN*sizeof(char));
                getchar();
                fgets(person, MAXLEN, stdin);
                n2 = strlen(person);
                person[n2-1] = '\0';

                s2 = simple_split(person, n2, sep);
                if(s2) parseInfo(s2, &(head->current->itemInfo));
            }
        }
    }
}

Head *introduction(Head *head){
    FILE *file;
    info *MASSFromFile;
    char **s2;
    char *filename, str_file[MAXNAME], sep = ';';
    int choose = 0, nf, mm, n, m, i;

    printf("Input\n1 - if you have file\n2 - if you want to work without file\n");
    scanf("%d", &choose);

    if(choose == 1){
        printf("Input file name <*.txt>: ");
        filename = (char*)malloc(MAXNAME*sizeof(char));
        getchar();
        fgets(filename, MAXNAME, stdin);
        nf = strlen(filename);
        filename[nf-1] = '\0';

        file = fopen(filename, "r");
        if(file){
            mm = MAXLEN;
            for(i=0, m=0; i<mm; i++){
                fgets(str_file, MAXNAME, file);
                n = strlen(str_file);
                if(str_file[n-1]=='\n') m++;
                else{
                    m++;
                    mm=m;
                    i=mm;
                }
                if(i!=mm) str_file[n-1]='\0';
            }
            rewind(file);
            MASSFromFile=(info*)malloc(mm*sizeof(info));
            if(MASSFromFile){
                for(i=0; i<mm; i++){
                    fgets(str_file, MAXNAME, file);
                    n = strlen(str_file);
                    if(i != mm-1) str_file[n-1]='\0';
                    else str_file[n]='\0';
                    s2 = simple_split(str_file, n, sep);
                    if(s2){
                        head = prepareElement(s2, head);
                        s2 = ClStAr(s2, 5);
                    }
                    else printf("Row data not available!\n");
                }
            }
            else printf("Out of memory!\n");
        }
        else{
            printf("Cannot open file or no such file\n\n");
            head = introduction(head);
        }
    }
    printf("\n");

    return head;
}

void regulation(Head *head){
    int choose = 0;
    printf("Input\n1 - add person\n2 - delete person\n3 - edit person\n0 - back\n");
    scanf("%d", &choose);

    if(choose == 1){
        insertRow(head);
    }
    if(choose == 2) {
        deleteRow(head);
    }
    if(choose == 3) {
        editRow(head);
    }
    printf("\n");
}

void search(Head *head){
    char *ch1;
    int nch, i, pr;
    printf("Input what to search <name>, <kind of sport>, <team>\n");
    ch1 = (char*)malloc(MAXLEN*sizeof(char));
    getchar();
    fgets(ch1, MAXLEN, stdin);//printf("poehali\n");
    nch = strlen(ch1);
    ch1[nch-1] = '\0';

    head->current = head->first;
    for(i=0, pr=0; i<head->amount; i++){
        if((strcmp(ch1, head->current->itemInfo.name) == 0) || (strcmp(ch1, head->current->itemInfo.kind) == 0) || (strcmp(ch1, head->current->itemInfo.team) == 0)){
            pr++;
        }
        if(head->current != head->last) head->current = head->current->next;
    }
    if(pr != 0){
        printf("+----+---------------------+---------------------+------+---------------------+---------------------+\n");
        printf("|%3s |%20s |%20s |%5s |%20s |%20s |\n", "N", "Name", "Kind of sport", "Rank", "Number of rewards", "Team name");
        printf("+----+---------------------+---------------------+------+---------------------+---------------------+\n");
        head->current = head->first;
        for(i=0; i<head->amount; i++){
            if((strcmp(ch1, head->current->itemInfo.name) == 0) || (strcmp(ch1, head->current->itemInfo.kind)) == 0 || (strcmp(ch1, head->current->itemInfo.team)) == 0){
                printf("|%3d |%20s |%20s |%5d | %3d g, %3d s, %3d b |%20s |",
                    i+1, head->current->itemInfo.name, head->current->itemInfo.kind, head->current->itemInfo.rank, head->current->itemInfo.rewards[0],
                    head->current->itemInfo.rewards[1], head->current->itemInfo.rewards[2], head->current->itemInfo.team);
                printf("\n+--------------------------+---------------------+------+---------------------+---------------------+\n");
            }
            if(head->current != head->last) head->current = head->current->next;
        }
    }
    else printf("No such people\n");
    head->current = head->first;
}

int compareInfo(info i1, info i2, int fNum){
    switch(fNum){
        case 1: return strcmp(i1.name,i2.name); break;
        case 2: return strcmp(i1.kind,i2.kind); break;
        case 3: if(i1.rank > i2.rank) return 1; else return 0; break;
        case 4: if(i1.rewards[0] > i2.rewards[0]) return 1; else return 0; break;
        case 5: if(i1.rewards[1] > i2.rewards[1]) return 1; else return 0; break;
        case 6: if(i1.rewards[2] > i2.rewards[2]) return 1; else return 0; break;
        case 7: return strcmp(i1.team ,i2.team); break;
        default: return 0;
    }
}

void sorting(Head *head){
    int choose = -1, i1, i2, notOrdered = 1;
    element *ptrn, *ptrp;
    if(head->amount == 0){
        printf("No rows to sort.\n");
    }
    else if(head->amount == 1){
        printf("No reason to sort.\n");
    }
    else {
        printf("Enter number of field to sort\n1 - Name\n2 - Kind of sport\n3 - Rank\n4 - Number of gold rewards\n5 - Number of silver rewards\n6 - Number of bronze rewards\n7 - Team name\n0 - return to previous menu\n");
        scanf("%d", &choose);
        if((choose > 0) && (choose <= 7)){
            i2 = 1;
            while(notOrdered > 0){
                notOrdered = 0;
                head->current = head->first;
                for(i1 = 0; i1 < head->amount - i2; i1++){
                    if(compareInfo(head->current->itemInfo, head->current->next->itemInfo, choose) == 1){
                        notOrdered = 1;
                        if(head->current == head->first){
                            if(head->current->next == head->last){
                                head->last = head->current;
                                head->first = head->current->next;
                                head->last->previous = head->first;
                                head->last->next = NULL;
                                head->first->previous = NULL;
                                head->first->next = head->last;
                            } else {
                                head->first = head->current->next;
                                head->first->previous = NULL;
                                head->current->previous = head->first;
                                head->current->next = head->first->next;
                                head->current->next->previous = head->current;
                                head->first->next = head->current;
                            }
                        } else {
                            if(head->current->next == head->last){
                                head->last->previous = head->current->previous;
                                head->last->previous->next = head->last;
                                head->last->next = head->current;
                                head->current->previous = head->last;
                                head->last = head->current;
                                head->last->next = NULL;
                            } else {
                                head->current->previous->next = head->current->next;
                                head->current->next->next->previous = head->current;
                                ptrn = head->current->next->next;
                                ptrp = head->current->previous;
                                head->current->next->next = head->current;
                                head->current->previous = head->current->next;
                                head->current->next = ptrn;
                                head->current->previous->previous = ptrp;
                            }
                        }
                    } else {
                        head->current = head->current->next;
                    }
                }
                i2++;
            }
        }
    }
    printf("People have been sorted\n\n");
}

void saveAll(Head *head){
    int i, f2n;
    char *f2name;
    FILE *fout;

    printf("Input name of the new file <*.txt>: ");
    f2name = (char*)malloc(MAXNAME*sizeof(char));
    getchar();
    fgets(f2name, MAXNAME, stdin);
    f2n = strlen(f2name);
    f2name[f2n-1] = '\0';

    fout = fopen(f2name, "w");
    head->current = head->first;
    for(i=0; i < head->amount; i++){
        fprintf(fout, "%s;%s;%d;%d;%d;%d;%s\n",
                head->current->itemInfo.name, head->current->itemInfo.kind, head->current->itemInfo.rank, head->current->itemInfo.rewards[0],
                head->current->itemInfo.rewards[1], head->current->itemInfo.rewards[2], head->current->itemInfo.team);
        if(head->current != head->last) head->current = head->current->next;
    }
    fclose(fout);
    printf("Saved in %s\n\n", f2name);
}

int main(){
    int choose = -1, syst;
    Head *head;

    printf("Input\n1 - if you on Linux\n2 - if you on Windown or Mac OS\nAnd open console in full screen\n");
    scanf("%d", &syst);

    head = initHead(head);
    head = introduction(head);
    printf("Input\n1 - regulation\n2 - search\n3 - sorting\n4 - print information\n5 - save information in file\n0 - exit\n");
    scanf("%d", &choose);

    while(choose != 0){
        cls(syst);
        if(choose == 1){
            regulation(head);
        }
        if(choose == 2){
            search(head);
        }
        if(choose == 3){
            sorting(head);
        }
        if(choose == 4){
            printList(head);
        }
        if(choose == 5){
            saveAll(head);
        }
        if(choose > 5 || choose < 0) printf("Wrong input\n");
        printf("Input\n1 - regulation\n2 - search\n3 - sorting\n4 - print information\n5 - save information in file\n0 - exit\n");
        scanf("%d", &choose);

    }
    return 0;
}
