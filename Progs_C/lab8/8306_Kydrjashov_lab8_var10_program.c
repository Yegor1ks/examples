#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXNAME 260
#define MAXLEN 256

typedef struct ZNAK2{
    char *Name;
    char *ZOD;
    int *DATE;
} mas0;

void ClStAr(char **s2, int n);
char **simple_split(char *str, int length, char sep);
void sortdat(mas0 MASS2[MAXLEN], int n, int stroki);

int main(){
    char *nane, **s2=NULL, *zdk;
    int nn, nz, len0, len1, i, ii, j, n, m, mm, pr;
    mas0 MASS2[MAXLEN];
    char fl[MAXLEN], sep;
    FILE *f;

    f = fopen("DSV.txt", "r");
    sep=';';
    printf("\n");
    if (f!=NULL){
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
        for(i=0; i<mm; i++){
            fgets(fl, MAXNAME, f);
            n = strlen(fl);
            if(i!=(mm-1)) fl[n-1]='\0';
            else fl[n]='\0';
            n = strlen(fl);

            s2 = simple_split(fl, n, sep);
            if(s2!=NULL){
                len0 = strlen(s2[0]);
                len1 = strlen(s2[1]);

                MASS2[i].Name=(char*)malloc((len0+1)*sizeof(char));
                MASS2[i].ZOD=(char*)malloc((len1+1)*sizeof(char));
                MASS2[i].DATE=(int*)malloc(3*sizeof(int));

                if((MASS2[i].Name!=NULL)&&(MASS2[i].ZOD!=NULL)&&(MASS2[i].DATE!=NULL)){
                    strcpy(MASS2[i].Name, s2[0]);
                    strcpy(MASS2[i].ZOD, s2[1]);
                    for(j=0; j<3; j++) MASS2[i].DATE[j]=atoi(s2[2+j]);
                }
                else{
                    printf("Out if memory!\n");
                    i=mm;
                }
                ClStAr(s2, 3);
            }
            else{
                printf("Row data not available!\n");
                ClStAr(s2, 3);
            }
        }

        printf("+---------------------+---------------------+-----------+\n");
        printf("|%20s |%20s |%10s |\n","Name","Zodiac","Birth");
        printf("+---------------------+---------------------+-----------+\n");
        for(i=0; i<mm; i++){
            printf("|%20s |%20s |", MASS2[i].Name, MASS2[i].ZOD);
            if(MASS2[i].DATE[1]<10) printf(" ");
            if(MASS2[i].DATE[0]<10) printf(" ");
            for(j=0; j<3; j++) printf("%d.", MASS2[i].DATE[j]);
            printf("|\n+---------------------+---------------------+-----------+\n");
        }
        zdk=(char*)malloc(MAXNAME);
        printf("Input zodiac sign: ");
        fgets(zdk, MAXNAME, stdin);
        nz = strlen(zdk);
        zdk[nz-1] = '\0';
        sortdat(MASS2, n, mm);
        for(i=0, pr=0; i<mm; i++){
            if((nn=strcmp(MASS2[i].ZOD, zdk))==0){
                pr++;
            }
        }
        if(pr!=0){
            printf("+---------------------+---------------------+-----------+\n");
            printf("|%20s |%20s |%10s |\n","Name","Zodiac","Birth");
            printf("+---------------------+---------------------+-----------+\n");
            for(i=0; i<mm; i++){
                if((nn=strcmp(MASS2[i].ZOD, zdk))==0){
                    printf("|%20s |%20s |", MASS2[i].Name, MASS2[i].ZOD);
                    if(MASS2[i].DATE[1]<10) printf(" ");
                    if(MASS2[i].DATE[0]<10) printf(" ");
                    for(j=0; j<3; j++) printf("%d.", MASS2[i].DATE[j]);
                    printf("|\n+---------------------+---------------------+-----------+\n");
                }
            }
        }
        else printf("No people <%s> zodiac\n", zdk);
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

void sortdat(mas0 MASS2[MAXLEN], int n, int stroki){
    mas0 tmp[MAXLEN];
    int i, j, m;
    for(i=0; i<stroki-1; i++){
        for(j=0; j<stroki-1-i; j++){
            for(m=2; m>=0; m--){
                if(MASS2[j].DATE[m]>MASS2[j+1].DATE[m]){
                    tmp[j]=MASS2[j];
                    MASS2[j]=MASS2[j+1];
                    MASS2[j+1]=tmp[j];
                    m=-1;
                }
                else{
                    if(MASS2[j].DATE[m]!=MASS2[j+1].DATE[m]) m=-1;
                }
            }
        }
    }
}
