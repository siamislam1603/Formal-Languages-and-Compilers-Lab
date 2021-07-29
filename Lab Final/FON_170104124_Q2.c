/* Name:Md. Siam Islam    ID:170104124    Lab Group:C1
Course No: CSE4130 Final Online Assessment, Spring 2020
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int f=1,l;
char str[100];

void A(){
    int i;
    for(i=1; i<l-1; i++){
        if(str[i]!='b'){
            f=0;
            return;
        }
    }
}

void E()
{
    if((str[0]=='a' || str[0]=='b') && (str[l-1]=='a' || str[l-1]=='b')){
        f=1;
        A();
    }
    else
        f=0;
}

int main(void)
{
    printf("Some valid input(ab,abba,bb,bba)\n");
    printf("Enter string: ");
    scanf("%s",str);
    l=strlen(str);
    E();
    if(f==1)
        printf("\nValid String");
    else
        printf("\nInvalid String");
    return 0;
}
