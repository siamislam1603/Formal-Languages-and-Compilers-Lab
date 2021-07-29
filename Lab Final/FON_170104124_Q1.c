/* Name:Md. Siam Islam    ID:170104124    Lab Group:C1
Course No: CSE4130 Final Online Assessment, Spring 2020
*/
#include<stdio.h>
#include<string.h>
#include<stdbool.h>

bool isUserDefined(char str[])
{
    if(strcmp(str,"printf")==0)
        return false;
    else if(strcmp(str,"scanf")==0)
        return false;
    else
        return true;
}

int main()
{
    FILE *fp;
    char c;
    char str[100];
    int func_id[100];
    int line=1,i=0,found=0, value=0, k=0;

    memset(func_id,0,sizeof(func_id[0])*100);

    fp=fopen("input.c","r");

    while((c=fgetc(fp))!=-1){
        if(c=='\n')
            line++;
        else if((c>='a' && c<='z')||(c>='A' && c<='Z')||(c>='0' && c<='9')||(c=='_')){
            str[i]=c;
            i++;
        }
        else if(c=='('){
            str[i]='\0';
            i=0;

            if(str[0]>='a' && str[0]<='z'){
                if(isUserDefined(str)){
                    for(int j=0; j<strlen(str); j++){
                        value+=(j*(int)str[j]);
                    }

                    for(int j=0; j<=k; j++){
                        if(value==func_id[j]){
                            found=1;
                            break;
                        }
                    }

                    if(!found){
                        func_id[k]=value;
                        k++;
                        printf("%s Line No:  %d\n",str,line);
                    }
                    value=0;
                    found=0;
                }
            }
        }
        else{
            str[i]='\0';
            i=0;
        }
    }
    return 0;
}
