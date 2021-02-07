#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(){
    FILE *p1,*p2;
    char c;
    p1 = fopen("s3_input.txt", "r");
    p2=fopen("output.txt","w");
    if(!p1)
        printf("\nFile can't be opened!");
    else{
        c=fgetc(p1);
        while(c!=EOF){
            char str[20];
            int i=0;
            while(c!=' ' && c!=EOF){
                str[i++]=c;
                c=fgetc(p1);
            }
            str[i]='\0';
            if(str[0]=='[' && str[1]!='i' && str[2]!='d'){
                fprintf(p2,"[");
            }
            else{
                fprintf(p2,"%s ",str);
            }
            c=fgetc(p1);
        }
    }
    fclose(p1);
    fclose(p2);
    printf("\nInput File:\n------------\n");
    p1 = fopen("s3_input.txt","r");
    while((c=fgetc(p1))!=EOF)
		printf("%c",c);
    fclose(p1);
    printf("\n\nOutput File:\n------------\n");
    p2 = fopen("output.txt","r");
    while((c=fgetc(p2))!=EOF)
		printf("%c",c);
    fclose(p2);
    printf("\n");
}
