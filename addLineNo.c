/*Write a program to add line numbers to a source program.*/
#include<stdio.h>
#include<stdlib.h>

int main(void)
{
    FILE *p1,*p2;
    char c;
    int i=1;
    int temp=1;
    p1 = fopen("addLineNo.c", "r");
    p2 = fopen("addLineNoOutput.txt","w");

    if(!p1)
        printf("\nFile can't be opened!");
    else
    {
      	c = fgetc(p1);
        while (c != EOF)
        {
            if(c!='\n' && temp==1){
                fprintf(p2,"%d: ",i++);
                temp=0;
            }
            else if(c=='\n' && temp==0){
                temp=1;
            }
            else if(c=='\n' && temp==1)
                fprintf(p2,"%d: ",i++);
            fputc(c,p2);
            c = fgetc(p1);
        }
    }
    fclose(p1);
    fclose(p2);

    p2 = fopen("addLineNoOutput.txt","r");
    while((c=fgetc(p2))!=EOF)
		printf("%c",c);
    fclose(p2);

    return 0;
}
