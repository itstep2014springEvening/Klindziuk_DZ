#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXDIGITS 1000
#define BASE 10000

typedef int myLongType[MAXDIGITS];

void readLong(FILE *inputFile, myLongType a)
{
    memset(a,0,sizeof(myLongType));
    char current=fgetc(inputFile);
    while (current!='\n')
    {
        for (int i=a[0]; i>=1; --i)
        {
            a[i+1]=a[i+1]+a[i]*10/BASE;
            a[i]=a[i]*10%BASE;
        }
        a[1]=a[1]+current-'0';
        if (a[a[0]+1]>0)
            ++a[0];
        current=fgetc(inputFile);
    }
}

void writeLong(FILE *outputFile, const myLongType a)
{
    //char ls[10],s[10];
    char ls[(int) log10(MAXDIGITS)],s[(int) log10(MAXDIGITS)];
    sprintf(ls,"%d",BASE/10);  // itoa() почему-то не работал
    fprintf(outputFile,"%d",a[a[0]]);
    for(int i=a[0]-1; i>=1; --i)
    {
        sprintf(s,"%d",a[i]);
        while (strlen(s)<strlen(ls)) // а в паскале тут всего одна строка  s:='0'+s;
        {
            char tmpStr[10]="0";
            strcat(tmpStr,s);
            strcpy(s,tmpStr);
        }
        fprintf(outputFile,"%s",s);
    }
    fprintf(outputFile,"\n");
}

void sumLong(const myLongType a, const myLongType b, myLongType c)
{
    memset(c,0,sizeof(myLongType));
    int k;
    if (a[0]>b[0])
        k=a[0];
    else
        k=b[0];
    for (int i=1; i<=k; ++i)
    {
        c[i+1]=(c[i]+a[i]+b[i])/BASE;
        c[i]=(c[i]+a[i]+b[i])%BASE;
    }
    if (c[k+1]==0)
        c[0]=k;
    else
        c[0]=k+1;
}

void multiLong(const myLongType a, const myLongType b, myLongType c)
{
    memset(c,0,sizeof(myLongType));
    for (int i=1; i<=a[0]; ++i)
        for (int j=1; j<=b[0]; ++j)
        {
            int dv;
            dv=(a[i]*b[j]+c[i+j-1]);
            c[i+j]=c[i+j]+(dv/BASE);
            c[i+j-1]=dv%BASE;
        }
    c[0]=a[0]+b[0];
    while (c[0]>1 && c[c[0]]==0)
        --c[0];
}

int main()
{
    myLongType a,b,c;
    /*
    printf("A= ");
    readLong(a);
    printf("B= ");
    readLong(b);

    printf("Sum\n");
    printf("C= ");
    sumLong(a,b,c);
    writeLong(c);

    printf("Mylti\n");
    printf("C= ");
    multiLong(a,b,c);
    writeLong(c);
    */
    FILE *inputFile,*outputFile;
    inputFile=fopen("input.txt","r");
    outputFile=fopen("output.txt","w");
/*
    printf("A= ");
    readLong(a);
    printf("B= ");
    readLong(b);
*/
    //readLong(stdin,a);
    readLong(inputFile,a);
    //readLong(stdin,b);
    readLong(inputFile,b);
    //writeLong(a);
    //writeLong(b);

    //printf("Sum\n");
    //printf("C= ");
    sumLong(a,b,c);
    //writeLong(stdout,c);
    writeLong(outputFile,c);


    fclose(outputFile);
    fclose(inputFile);
    return 0;
}
