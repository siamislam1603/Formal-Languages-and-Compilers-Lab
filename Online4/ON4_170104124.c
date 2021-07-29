#include<stdio.h>

int main()
{
    FILE *f1;
    char c,st[100];
    int ln=1, top=0;

    f1=fopen("input.txt","r");

    while((c=fgetc(f1))!=-1){
        if(c=='/'){
            while((c=fgetc(f1))!='\n');
        }
        if(c=='\n')
            ln++;
        if(c=='(' || c=='{'){
            top++;
            st[top]=c;
        }
        else if(c==')' || c=='}'){
            if(c==')'){
                if(st[top]!='(' || top==-1){
                    printf("Misplaced Parenthesis at Line Number %d\n",ln);
                }
                top--;
            }
            else{
                if(st[top]!='{' || top==-1){
                    printf("Misplaced Curly Brace at Line Number %d\n",ln);
                }
                top--;
            }
        }
    }

    return 0;
}
