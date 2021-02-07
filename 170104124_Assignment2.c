/*Suppose, we have a C source program scanned and filtered as it was done
in Session 1. We now take that modified file as input, and separate the lex-
emes first. We further recognize and mark the lexemes as different types of
tokens like keywords, identifiers, operators, separators, parenthesis, num-
bers, etc.*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char keywords[32][15] = {"auto","break","case","char","const",
    "continue","default","do","double","else",
    "enum","extern","float","for","goto","if",
    "int","long","register","return","short",
    "signed","sizeof","static","struct","switch",
    "typedef","union","unsigned","void","volatile",
    "while","main"};
char operators[24][3]={"+","-","/","*","=","==","%","++","--","+=","-=",">","<",">=","<=","!=","!","&&","||","&","|","^","<<",">>"};
char seperators[8][2]={",",";","(",")","[","]","{","}"};
FILE *p1,*p2,*p3;

int kw(char lexeme[]){
    int found=0;
    for(int i=0;i<32;i++){
        if((strcmp(lexeme,keywords[i]))==0){
            found=1;
            break;
        }
    }
    if(found==1)
        fprintf(p2,"[kw %s]",lexeme);
    return found;
}
int op(char lexeme[]){
    int found=0;
    for(int i=0;i<24;i++){
        if((strcmp(lexeme,operators[i]))==0){
            found=1;
            break;
        }
    }
    if(found==1)
        fprintf(p2,"[op %s]",lexeme);
    return found;
}
int id(char lexeme[]){
    int found=0;
    if(lexeme[0]=='_' || isalpha(lexeme[0])){
        found=1;
        for(int i=1;i<strlen(lexeme);i++){
            if(isalpha(lexeme[i]) || lexeme[i]=='_' || isdigit(lexeme[i])){
                continue;
            }
            else{
                found=0;
                break;
            }
        }
    }
    if(found==1)
        fprintf(p2,"[id %s]",lexeme);
    return found;
}
int sep(char lex[]){
    int found=0;
    for(int i=0;i<8;i++){
        if((strcmp(lex,seperators[i]))==0){
            found=1;
            break;
        }
    }
    if(found==1)
        fprintf(p2,"[sep %s]",lex);
    return found;
}
int charLiteral(char lex[]){
    int found=0;
    if(lex[0]=='\'' && strlen(lex)==3 && lex[strlen(lex)-1]=='\''){
        found=1;
    }
    if(found==1)
        fprintf(p2,"[ch %s]",lex);
    return found;
}
int numLiteral(char lex[]){
    int i=0, l=strlen(lex), s;
    if(isdigit(lex[i])) {
        s=1;
        i++;
    }
    else if(lex[i]=='.') {
        s=2;
        i++;
    }
    else s=0;
    if(s==1)
        for( ; i<l; i++){
            if(isdigit(lex[i]))
                s=1;
            else
                if(lex[i]=='.') {
                    s=2;
                    i++;
                    break;
                }
                else {
                    s=0;
                    break;
                }
        }
    if(s==2)
        if(isdigit(lex[i])) {
            s=3;
            i++;
        }
        else
            s=0;
    if(s==3)
    for(; i<l; i++) {
        if(isdigit(lex[i]))
            s=3;
        else {
            s=0;
            break;
        }
    }
    if(s==1){
        fprintf(p2,"[in %s]",lex);
    }
    else if(s==3){
        fprintf(p2,"[fn %s]",lex);
        s=1;
    }
    return s;
}
int main(){
    char c,tempC;
    p1 = fopen("s2_input.c", "r");
    p3=fopen("s2_lexemes.txt","w");
    if(!p1)
        printf("\nFile can't be opened!");
    else
    {
        c=fgetc(p1);
        while(c!=EOF){
            tempC=c;
            fputc(c,p3);
            c=fgetc(p1);
            if(c==';'||c==','||c=='+'||c=='-'||c=='*'||c=='/'||c=='='||
            c=='('||c==')' || c=='>' || c=='<' || c=='&' || c=='|' ||
            c=='^' || c=='!'|| c=='{'){
                if(tempC!=' ')
                    fprintf(p3," %c",c);
                else
                    fputc(c,p3);
                tempC=c;
                c=fgetc(p1);
                if(c!=' ' && c!=EOF && c!='=' && c!=tempC)
                    fputc(' ',p3);
                else if(c=='='||c==tempC){
                    fprintf(p3,"%c ",c);
                    c=fgetc(p1);
                }
            }
            else if(tempC==';'||tempC==','||tempC=='+'||tempC=='-'||tempC=='*'||tempC=='/'||tempC=='='||
            tempC=='('||tempC==')' || tempC=='>' || tempC=='<' || tempC=='&' || tempC=='|' ||
            tempC=='^' || tempC=='!'|| tempC=='{' || tempC=='}'){
                if(c!=' ')
                    fputc(' ',p3);
            }
        }
    }
    fclose(p1);
    fclose(p3);
    p3 = fopen("s2_lexemes.txt","r");
    p2=fopen("s2_e1_output.txt","w");
    while((c=fgetc(p3))!=EOF){
        char lex[1000];
        int i=0;
        for(;c!=' ' && c!='\n' && c!=EOF;i++){
            lex[i]=c;
            c=fgetc(p3);
        }
        if(strlen(lex)>0){
            lex[i]='\0';
            int found=0;
            if(found==0)
                found=sep(lex);
            if(found==0)
                found=op(lex);
            if(found==0)
                found=kw(lex);
            if(found==0)
                found=id(lex);
            if(found==0)
                found=charLiteral(lex);
            if(found==0)
                found=numLiteral(lex);
            if(found==0){
                fprintf(p2,"[unkn %s]",lex);
            }
        }
        if(c==EOF)
            break;
    }
    fclose(p3);
    fclose(p2);
    printf("\nInput File:\n-----------\n");
    p1 = fopen("s2_input.c","r");
    while((c=fgetc(p1))!=EOF)
		printf("%c",c);
    fclose(p1);
    printf("\nLexemes File:\n------------\n");
    p3 = fopen("s2_lexemes.txt","r");
    while((c=fgetc(p3))!=EOF)
		printf("%c",c);
    fclose(p3);
    printf("\nOutput File:\n------------\n");
    p2 = fopen("s2_e1_output.txt","r");
    while((c=fgetc(p2))!=EOF)
		printf("%c",c);
    fclose(p2);
    printf("\n");
    return 0;
}
