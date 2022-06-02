#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum{
    MAXNAME=64,
    MAXLEN=512
};

typedef struct info{
    char *name;
    char *ext;
    float minhz;
    float maxhz;
    int st;
    int opt;
    int *xsize;
} inf0;

void ClStAr(char **s2, int n);
char **simple_split(char *str, int length, char sep);
void sort(inf0 *MASS, int stroki);

int main(){
    char **s2=NULL, nore[MAXNAME];
    int len0, len1, i, j, n, nn, m, mm, pr;
    inf0 *MASS;
    char fl[MAXLEN], sep;
    FILE *f;
    printf("[The optimal width to display the table is 110]\n");

    f = fopen("CSV.txt", "r");
    sep=';';
    if (f!=NULL){
        mm = MAXLEN;
        for(i=0, m=0; i<mm; i++){
            fgets(fl, MAXLEN, f);
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
        for(i=0; i<mm; i++){
            fgets(fl, MAXLEN, f);
            n = strlen(fl);
            if(i!=(mm-1)) fl[n-1]='\0';
            else fl[n]='\0';
            n = strlen(fl);

            s2 = simple_split(fl, n, sep);
            if(s2!=NULL){
                len0 = strlen(s2[0]);
                len1 = strlen(s2[1]);

                MASS[i].name=(char*)malloc((len0+1)*sizeof(char));
                MASS[i].ext=(char*)malloc((len1+1)*sizeof(char));
                MASS[i].xsize=(int*)malloc((2)*sizeof(int));

                if((MASS[i].name!=NULL)&&(MASS[i].ext!=NULL)){
                    strcpy(MASS[i].name, s2[0]);
                    strcpy(MASS[i].ext, s2[1]);
                    MASS[i].minhz=atof(s2[2]);
                    MASS[i].maxhz=atof(s2[3]);
                    MASS[i].st=atoi(s2[4]);
                    MASS[i].opt=atoi(s2[5]);
                    for(j=0; j<2; j++) MASS[i].xsize[j]=atoi(s2[6+j]);
                }
                else{
                    printf("Out if memory!\n");
                    i=mm;
                }
                ClStAr(s2, 5);
            }
            else{
                printf("Row data not available!\n");
                ClStAr(s2, 5);
            }
        }
        sort(MASS, mm);
        printf("+---------------------+---------------------+---------------------+---------+---------+----------------+\n");
        printf("|%20s |%20s |%20s |%8s |%8s |%15s |\n", "Name", "Extraction", "Min & max kHz", "Strings", "Options", "Max size, cm");
        printf("+---------------------+---------------------+---------------------+---------+---------+----------------+\n");
        for(i=0; i<mm; i++){
            printf("|%20s |%20s | %8f & %8f |%8d |%8d |", MASS[i].name, MASS[i].ext, MASS[i].minhz, MASS[i].maxhz, MASS[i].st, MASS[i].opt);
            for(j=0; j<2; j++){
                printf("%7d", MASS[i].xsize[j]);
                if(j==0) printf(" x");
            }
            printf("|\n+---------------------+---------------------+---------------------+---------+---------+----------------+\n");
        }

        printf("\nInput <Name> or <Extraction>: ");
        fgets(nore, MAXNAME, stdin);
        nn=strlen(nore);
        nore[nn-1]='\0';
        printf("\n");

        for(i=0, pr=0; i<mm; i++){
            if(((nn=strcmp(MASS[i].name, nore))==0)||((nn=strcmp(MASS[i].ext, nore))==0)){
                pr++;
            }
        }
        if(pr!=0){
            printf("+---------------------+---------------------+---------------------+---------+---------+----------------+\n");
            printf("|%20s |%20s |%20s |%8s |%8s |%15s |\n", "Name", "Extraction", "Min & max kHz", "Strings", "Options", "Max size, cm");
            printf("+---------------------+---------------------+---------------------+---------+---------+----------------+\n");
            for(i=0; i<mm; i++){
                if(((nn=strcmp(MASS[i].name, nore))==0)||((nn=strcmp(MASS[i].ext, nore))==0)){
                    printf("|%20s |%20s | %8f & %8f |%8d |%8d |", MASS[i].name, MASS[i].ext, MASS[i].minhz, MASS[i].maxhz, MASS[i].st, MASS[i].opt);
                    for(j=0; j<2; j++){
                        printf("%7d", MASS[i].xsize[j]);
                        if(j==0) printf(" x");
                    }
                    printf("|\n+---------------------+---------------------+---------------------+---------+---------+----------------+\n");
                }
            }
        }
        else printf("No such instruments\n");

        free(MASS);
        MASS=NULL;
    }
    else printf("False name of file or no such file\n");
    fclose(f);
    return 0;
}

void ClStAr(char **s2, int n){
    int i;
    for(i=0;i<n;i++){
        free(s2[i]);
        s2[i]=NULL;
    }
    free(s2);
    s2=NULL;
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
    if(str_array!=NULL){
        for(i=0,count=0;i<=m;i++,count++){
            str_array[i]=(char*)malloc(length*sizeof(char));
            if(str_array[i]!=NULL) key=1;
            else{
                key=0;
                i=m;
            }
        }
        if(key){
            k=0;
            m=0;
            for(j=0;j<length;j++){
                if(str[j]!=sep) str_array[m][j-k]=str[j];
                else{
                    str_array[m][j-k]='\0';
                    k=j+1;
                    m++;
                }
            }
        }
        else ClStAr(str_array,count);
     }
     return str_array;
}

void sort(inf0 *MASS, int stroki){
    inf0 *tmp;
    int i, j, m;
    tmp=(inf0*)malloc(stroki*sizeof(inf0));
    for(i=0; i<stroki-1; i++){
        for(j=0; j<stroki-1-i; j++){
            if(MASS[j].minhz>MASS[j+1].minhz){
                tmp[j]=MASS[j];
                MASS[j]=MASS[j+1];
                MASS[j+1]=tmp[j];
            }
        }
    }
}
