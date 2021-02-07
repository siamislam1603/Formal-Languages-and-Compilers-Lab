/*Write a program to print the header files used in a source program.*/

#include<stdio.h>
#include<stdlib.h>
#define A 10
int main(void)
{
    FILE *p1,*p2;
    char c;
    p1 = fopen("HeaderFilePrint.c", "r");
    p2 = fopen("HeaderFilePrintOutput.txt", "w");
    if(!p1)
        printf("\nFile can't be opened!");
    else
    {
        while((c=fgetc(p1)) != EOF)
        {
            if(c=='#'){
                while((c=fgetc(p1))!='<' && c!='\n'){
                    continue;
                }
                if(c=='<'){
                    while((c=fgetc(p1))!='>'){
                        if(c!=' ' || c!='\t' || c!='\n')
                            fputc(c,p2);
                    }
                    fputc('\n',p2);
                }
            }
        }
    }
    fclose(p1);
    fclose(p2);

    p2 = fopen("HeaderFilePrintOutput.txt","r");
    while((c=fgetc(p2))!=EOF)
		printf("%c",c);
    fclose(p2);

    return 0;
}
