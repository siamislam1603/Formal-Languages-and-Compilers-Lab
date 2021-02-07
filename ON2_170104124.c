#include<stdio.h>
#include<string.h>

int main(void)
{
    char sentence[30];
    int i, length, valid=0,count=0;
    printf("Enter string: ");
    gets(sentence);
    length=strlen(sentence);
    for(i=0; i<length; i++){
        if(i==0 && sentence[i]=='c')
            valid=1;
        else if(i>0 && valid==0)
            break;
        else if(valid==1){
            if(sentence[i]=='_')
                for(int j=i+1;j<length;j++){
                    if(sentence[j]>='0' && sentence[j]<='9')
                        count++;
                    else{
                        count=0;
                        i=length-1;
                        break;
                    }
                }
            else if(sentence[i]>='a' && sentence[i]<='z')
                continue;
            else
                i=length-1;
        }
    }

    if(count>=2)
        printf("String follows the pattern");
    else
        printf("String does not follow the pattern");
    return 0;
}
