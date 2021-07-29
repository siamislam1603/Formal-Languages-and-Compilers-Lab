//Lab exercise-1
#include<stdio.h>

char str[100];
int i=0,l,f;
void X() {
    if (str[i] == 'b' && (str[i+1] == 'b' || str[i+1]=='c')) {
        i+=2;
        f=1;
    }
    else {f=0; return;}
    if (i<l-1) X();
}
void A() {
    if (str[i++] == 'a'){
        if(i!=l-1)
            X();
        else if(str[i]=='d'){
            f=1;
            return;
        }
        if(f){
            if(str[i]!='d')
                f=0;
        }
    }
    return;
}

int main(){
    printf("Enter string: ");
    scanf("%s", str);
    l=strlen(str);
    A();
    if(f==1)
        printf("Valid\n");
    else
        printf("Invalid\n");
    return 0;
}
