/*Write a C program that will scan an input file (.c file) and find out how many floating point
numbers are written on the console as output in that input program.*/
#include<stdio.h>

int main(void)
{
    FILE *p1,*p2;
    char c,tempC;
    int flag=0,count=0;
    p1 = fopen("online1_input.c", "r");
    if(!p1)
        printf("\nFile can't be opened!");
    else{
        c = fgetc(p1);
        while (c != EOF){
            if(c=='"'){
                while((c=fgetc(p1))!=';'){
                    if(c=='%' && (c=fgetc(p1))=='f')
                        flag+=1;
                    else if(c=='&')
                        flag=0;
                }
            }
            count+=flag;
            c=fgetc(p1);
            flag=0;
        }
    }
    fclose(p1);
    printf("No. of Floating Point Numbers written:%d\n",count);
    return 0;
}

