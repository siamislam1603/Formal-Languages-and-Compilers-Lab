/*A C source program with single and multiple line comments is given. As the first step toward
compilation you need to remove the comments and white space (extra spaces, tabs and
newline characters). Develop a program that takes as input file the given source program and
produces a filtered file as stated above. The program must also display both the files.*/

#include<stdio.h>

int main(void)
{
    FILE *p1,*p2;
    char c,tempC;
    p1 = fopen("assignment1_input.c", "r");
    p2 = fopen("assignment1_output.txt","w");
    if(!p1)
        printf("\nFile can't be opened!");
    else
    {
      	c = fgetc(p1);
      	while(c==' '||c=='\n'||c=='\t')
            c=fgetc(p1);
        while (c != EOF)
        {
            if(c=='\t'){
                c = fgetc(p1);
                continue;
            }
            else if(c==' '){
                while(c==' ')
                    c=fgetc(p1);
                fputc(' ',p2);
                continue;
            }
            else if(c=='\n'){
                c=fgetc(p1);
                while(c==' ')
                    c=fgetc(p1);
                continue;
            }
            else if(c=='/'){
                tempC=fgetc(p1);
                if(tempC=='/'){
                    c=tempC;
                    while(c!='\n')
                        c=fgetc(p1);
                    continue;
                }
                else if(tempC=='*'){
                    tempC=fgetc(p1);
                    c=tempC;
                    for(;;){
                        if(c=='*'){
                            c=fgetc(p1);
                            if(c=='/'){
                                c=fgetc(p1);
                                break;
                            }
                        }
                        c=fgetc(p1);
                    }
                    while(c==' '|| c=='\t')
                        c=fgetc(p1);
                    continue;
                }
                else{
                    fputc(c,p2);
                    c=tempC;
                    continue;
                }
            }
            else if(c=='"'){
                fputc(c,p2);
                while((c=fgetc(p1))!='"'){
                    fputc(c,p2);
                }
            }
            fputc(c,p2);
            c = fgetc(p1);
        }
    }
    fclose(p1);
    fclose(p2);
    printf("Output File:\n------------\n");
    p2 = fopen("assignment1_output.txt","r");
    while((c=fgetc(p2))!=EOF)
		printf("%c",c);
    fclose(p2);

    printf("\n\nInput File:\n-----------\n");
    p1 = fopen("assignment1_input.c","r");
    while((c=fgetc(p1))!=EOF)
		printf("%c",c);
    fclose(p1);

    return 0;
}
