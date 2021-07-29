/****************************************************************/
/* CSE 4130 : Spring 2020 Final Project ID: 170104124 */
/****************************************************************/
/* To run this program,input.c file needs to be created*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define size 10000
int ind=1,isId=0,isLocal=0,kwCount=0,idCount=0,sepCount=0,previousToken=-1,duplicateFound=0,stop=0;
char idT[20],val[20],scope[20]="global",str[20],kw[15],id[20],opr[3],seperator[2],anotherKw[15],s[40],top=-1,ifElseTop=-1;
int parenthesisBalanced=1,ifElseBalanced=1;
char keywords[32][15] = {"int","double","float","char","auto","break","case","const",
    "continue","default","do","else",
    "enum","extern","for","goto","if",
    "long","register","return","short",
    "signed","sizeof","static","struct","switch",
    "typedef","union","unsigned","void","volatile",
    "while","main"};
char operators[24][3]={"=","+","-","/","*","==","%","++","--","+=","-=",">","<",">=","<=","!=","!","&&","||","&","|","^","<<",">>"};
char seperators[8][2]={",",";","(",")","{","}","[","]"};
FILE *p1,*p2,*p3;
char c,tempC,lex[1000],parenthesis[2],ifElseStack[40][5],ifElse[5];
int i=0,temp=1,spaceCount=0,ln=1,counter=0;

struct pair{
    int slNo;
    char name[20],idType[20],dataType[20],scope[20],value[20];
};
struct pair hash_table[size];

void display(struct pair ar[]){
    printf("\nSLNo.\tName\tIdType\tDataType\tScope\tValue\n");
    for(int j=1;j<ind;j++){
        printf("%d\t%s\t%s\t%s\t\t%s\t%s\n",ar[j].slNo,ar[j].name,ar[j].idType,ar[j].dataType,ar[j].scope,ar[j].value);
    }
}
void update(struct pair ar[],int updatedIndex){
    strcpy(ar[updatedIndex].value,val);
}
void insert(struct pair ar[]){
    ar[ind].slNo=ind;
    strcpy(ar[ind].dataType,kw);
    strcpy(ar[ind].name,id);
    if(strcmp(idT,"func")==0){
        strcpy(ar[ind].scope,"global");
        strcpy(scope,id);
        isLocal=1;
    }
    else
        strcpy(ar[ind].scope,scope);
    strcpy(ar[ind].idType,idT);
    if(strlen(val)>0)
        strcpy(ar[ind].value,val);
    ++ind;
}
void search(struct pair ar[]){
    int j=1,isUpdated=0;
    for(;j<ind;j++){
        if(strcmp(ar[j].name,id)==0 && strcmp(scope,ar[j].scope)==0){
            if(strlen(kw)==0 && strlen(val)>0)
                isUpdated=1;
            else if(strlen(kw)>0)
                isUpdated=-1;
            break;
        }
    }
    if(isUpdated==1)
        update(ar,j);
    else if(isUpdated==-1)
        fprintf(p3,"At line number %d: Duplicate token\n",ln-1);
    else if(strlen(kw)>0 && strlen(id)>0)
        insert(ar);
    idCount=0;
    kwCount=0;
    counter=0;
    strcpy(kw,"");
    strcpy(id,"");
    strcpy(idT,"");
    strcpy(val,"");
}


void checkIfNewLine(){
    if(c!='\n' && temp==1){
        ln++;
        i=0;
        idCount=0;
        kwCount=0;
        parenthesisBalanced=1;
        ifElseBalanced=1;
        previousToken=-1;
        stop=0;
        duplicateFound=0;
        spaceCount++;
        temp=0;
    }
    else if(c=='\n' && temp==0){
        temp=1;
    }
    else if(c=='\n' && temp==1){
        ln++;
        i=0;
        idCount=0;
        kwCount=0;
        parenthesisBalanced=1;
        ifElseBalanced=1;
        duplicateFound=0;
        previousToken=-1;
        stop=0;
        spaceCount++;
    }
}
int keyword(char lexeme[]){
    int found=0,j=0;
    for(;j<32;j++){
        if((strcmp(lexeme,keywords[j]))==0){
            found=1;
            break;
        }
    }
    if(found==1){
        if(j>=0 && j<=3){
            strcpy(kw,lexeme);
            kwCount++;
        }
        else
            strcpy(anotherKw,lexeme);
        fprintf(p2," [kw %s]",lexeme);
    }
    return found;
}
int op(char lexeme[]){
    int found=0;
    for(int j=0;j<24;j++){
        if((strcmp(lexeme,operators[j]))==0){
            found=1;
            break;
        }
    }
    if(found==1){
        strcpy(opr,lexeme);
        fprintf(p2," [op %s]",lexeme);
    }
    return found;
}
int identifier(char lexeme[]){
    int found=0;
    if(lexeme[0]=='_' || isalpha(lexeme[0])){
        found=1;
        for(int j=1;j<strlen(lexeme);j++){
            if(isalpha(lexeme[j]) || lexeme[j]=='_' || isdigit(lexeme[j])){
                continue;
            }
            else{
                found=0;
                break;
            }
        }
    }
    if(found==1){
        strcpy(id,lexeme);
        idCount++;
        fprintf(p2," [id %s]",lexeme);
    }
    return found;
}
int sep(char lex[]){
    int found=0;
    for(int j=0;j<8;j++){
        if((strcmp(lex,seperators[j]))==0){
            found=1;
            break;
        }
    }
    if(found==1){
        strcpy(seperator,lex);
        fprintf(p2," [sep %s]",lex);
    }
    return found;
}
int charLiteral(char lex[]){
    int found=0;
    if(lex[0]=='\'' && strlen(lex)==3 && lex[strlen(lex)-1]=='\''){
        found=1;
    }
    if(found==1){
        strcpy(val,lex);
        fprintf(p2," [ch %s]",lex);
    }
    return found;
}
int numLiteral(char lex[]){
    int j=0, l=strlen(lex), s;
    if(isdigit(lex[j])) {
        s=1;
        j++;
    }
    else if(lex[j]=='.') {
        s=2;
        j++;
    }
    else s=0;
    if(s==1)
        for( ; j<l; j++){
            if(isdigit(lex[j]))
                s=1;
            else
                if(lex[j]=='.') {
                    s=2;
                    j++;
                    break;
                }
                else {
                    s=0;
                    break;
                }
        }
    if(s==2)
        if(isdigit(lex[j])) {
            s=3;
            j++;
        }
        else
            s=0;
    if(s==3)
    for(; j<l; j++) {
        if(isdigit(lex[j]))
            s=3;
        else {
            s=0;
            break;
        }
    }
    if(s==1){
        strcpy(val,lex);
        fprintf(p2," [in %s]",lex);
    }
    else if(s==3){
        strcpy(val,lex);
        fprintf(p2," [fn %s]",lex);
        s=1;
    }
    return s;
}
int areParenthesisBalanced(char expr){
    if(expr == '(' || expr == '['|| expr == '{')
        s[++top]=expr;
    else if(top!=-1){
        char x;
        if(expr==')'){
            x = s[top--];
            if (x == '{' || x == '[')
                return 0;
            else
                return 1;
        }
        else if(expr=='}'){
            x = s[top--];
            if (x == '(' || x == '[')
                return 0;
            else
                return 1;
        }
        else if(expr==']'){
            x = s[top--];
            if (x == '(' || x == '{')
                return 0;
            else
                return 1;
        }
    }
    else if(top==-1)
        return 0;
    return 1;
}
int areIfElseBalanced(char expr[]){
    if(strcmp(expr,"if")==0)
        strcpy(ifElseStack[++ifElseTop],expr);
    else if(ifElseTop!=-1){
        char x[5];
        if(strcmp(expr,"else")==0){
            strcpy(x,ifElseStack[ifElseTop--]);
            if (strcmp(x,"if")==0)
                return 1;
            else
                return 0;
        }
    }
    else if(ifElseTop==-1)
        return 0;
    return 1;
}
void tokenizer(){
    lex[i]='\0';
    i=0;
    if(strlen(lex)>0){
        int found=0;
        if(found==0){
            found=sep(lex);
            if(previousToken==0 && duplicateFound==0 &&(strcmp(lex,",")==0 || strcmp(lex,";")==0))
                duplicateFound=1;
            else
                previousToken=0;
            if(strcmp(lex,"for")==0){
                int colon=0;
                while((c=fgetc(p1))!=')'){
                    if(c==';')
                        colon++;
                }
                if(colon!=2)
                    fprintf(p3,"At line number %d: Declaration of for loop not correct\n",ln-1);
                c=fgetc(p1);
                colon=0;
            }
            if(strcmp(lex,"(")==0)
                parenthesisBalanced=areParenthesisBalanced('(');
            else if(strcmp(lex,")")==0)
                parenthesisBalanced=areParenthesisBalanced(')');
            else if(strcmp(lex,"{")==0)
                parenthesisBalanced=areParenthesisBalanced('{');
            else if(strcmp(lex,"}")==0)
                parenthesisBalanced=areParenthesisBalanced('}');
            if(strcmp(lex,"(")==0 ||strcmp(lex,")")==0 ||strcmp(lex,"{")==0 ||strcmp(lex,"}")==0){
                if(parenthesisBalanced==0){
                    strcpy(parenthesis,lex);
                    duplicateFound=1;
                }
            }
        }
        if(found==0){
            found=op(lex);
            if(previousToken==1 && duplicateFound==0)
                duplicateFound=1;
            else
                previousToken=1;
        }
        if(found==0){
            found=keyword(lex);
            if(previousToken==2 && duplicateFound==0)
                duplicateFound=1;
            else
                previousToken=2;
            if(strcmp(lex,"if")==0)
                ifElseBalanced=areIfElseBalanced(lex);
            else if(strcmp(lex,"else")==0)
                ifElseBalanced=areIfElseBalanced(lex);
            if(strcmp(lex,"if")==0 ||strcmp(lex,"else")==0){
                if(ifElseBalanced==0){
                    strcpy(ifElse,lex);
                    duplicateFound=1;
                }
            }
        }
        if(found==0){
            found=identifier(lex);
            if(previousToken==3 && duplicateFound==0)
                duplicateFound=1;
            else
                previousToken=3;
        }
        if(found==0){
            found=charLiteral(lex);
            if(previousToken==4 && duplicateFound==0)
                duplicateFound=1;
            else
                previousToken=4;
        }
        if(found==0){
            found=numLiteral(lex);
            if(previousToken==5 && duplicateFound==0)
                duplicateFound=1;
            else
                previousToken=5;
        }
        if(found==0){
            fprintf(p2," [unkn %s]",lex);
        }
    }
    if(duplicateFound==0){
        if(counter==2 && idCount<=1 && kwCount<=1 && strlen(val)>0){
            search(hash_table);
        }
        else if(counter==1 && idCount<=1 && kwCount<=1){
            if(strcmp(lex,"=")==0){
                strcpy(idT,"var");
                counter++;
            }
            else if(strcmp(lex,"(")!=0){
                strcpy(idT,"var");
                search(hash_table);
            }
            else{
                strcpy(idT,"func");
                search(hash_table);
            }
        }
        else if(counter==1 || counter==2){
            fprintf(p3,"Duplicate token at line %d,",ln-1);
            counter=0;
            idCount=0;
            kwCount=0;
            strcpy(kw,"");
            strcpy(id,"");
            strcpy(idT,"");
            strcpy(val,"");
        }
        else if(strlen(id)>0)
            counter++;
    }
    else if(duplicateFound==1 && parenthesisBalanced==0 && stop==0){
        fprintf(p3,"At line number %d: Misplaced \'%s\'\n",ln-1,parenthesis);
        stop=1;
    }
    else if(duplicateFound==1 && ifElseBalanced==0 && stop==0){
        fprintf(p3,"At line number %d: Unmatched \'%s\'\n",ln-1,ifElse);
        stop=1;
    }
    else if(duplicateFound==1 && stop==0){
        fprintf(p3,"At line number %d: Duplicate token\n",ln-1);
        stop=1;
    }
}
void findErrors(){
    p1 = fopen("input.c", "r");
    p2=fopen("tokens.txt","w");
    p3 = fopen("report_170104124.txt","a");
    fprintf(p3,"\n\nErrors:\n\n");
    if(!p1)
        printf("\nFile can't be opened, Please create a file named \'input.c\'!");
    else
    {
      	c = fgetc(p1);
      	while(c==' '||c=='\n'||c=='\t'){
            checkIfNewLine();
            c=fgetc(p1);
      	}
        while (c != EOF)
        {
            if(c=='\t'){
                c = fgetc(p1);
                continue;
            }
            else if(c==' '){
                while(c==' ')
                    c=fgetc(p1);
                tokenizer();
                spaceCount++;
                continue;
            }
            else if(c=='\n'){
                tokenizer();
                checkIfNewLine();
                c=fgetc(p1);
                while(c==' ')
                    c=fgetc(p1);

                continue;
            }
            else if(c=='/'){
                checkIfNewLine();
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
                        checkIfNewLine();
                        c=fgetc(p1);
                    }
                    while(c==' '|| c=='\t'){
                        checkIfNewLine();
                        c=fgetc(p1);
                    }
                    continue;
                }
                else{
                    lex[i++]=c;
                    c=tempC;
                    continue;
                }
            }
            else if(c=='"'){
                while((c=fgetc(p1))!='"'){
                    checkIfNewLine();
                }
            }
            else if(c==';'||c==','||c=='+'||c=='-'||c=='*'||c=='/'||c=='='||
            c=='('||c==')' || c=='>' || c=='<' || c=='&' || c=='|' ||
            c=='^' || c=='!'|| c=='{' || c=='}'){
                checkIfNewLine();
                if(spaceCount==0)
                    tokenizer();
                lex[i++]=c;
                if((c=fgetc(p1))!=' ' && c!='\n'){
                    spaceCount++;
                    tokenizer();
                }
                else
                    spaceCount=0;
                continue;
            }
            checkIfNewLine();
            lex[i++]=c;
            c = fgetc(p1);
            spaceCount=0;
        }
    }
    fclose(p1);
    fclose(p2);
    fclose(p3);
    ln=1;
}
void sourceCodeWithLineNo(){
    p1 = fopen("input.c", "r");
    p3=fopen("report_170104124.txt","w");
    if(!p1)
        printf("\nFile can't be opened, Please create a file named \'input.c\'!");
    else{
        fprintf(p3,"Source code with line number:\n\n%d.",ln);
        while((c=fgetc(p1))!=EOF){
            if(c=='\n')
                fprintf(p3,"\n%d.",++ln);
            else
                fputc(c,p3);
        }
    }
    fclose(p1);
    fclose(p3);
    ln=1;
}
void HeaderFiles(){
    p1 = fopen("input.c", "r");
    p2=fopen("report_170104124.txt","a");
    int inc=0;
    fprintf(p2,"\nHeader Files: ");
    if(!p1)
        printf("\nFile can't be opened, Please create a file named \'input.c\'!");
    else{
        while((c=fgetc(p1))!=EOF){
            if(c=='#'){
                while((c=fgetc(p1))!='<' && c!='\n'){
                    continue;
                }
                if(c=='<'){
                    if(inc==1)
                        fputc(',',p2);
                    else if(inc==0)
                        inc=1;
                    while((c=fgetc(p1))!='>'){
                        if(c!=' ' || c!='\t' || c!='\n')
                            fputc(c,p2);
                    }
                }
            }
        }
    }
    fclose(p1);
    fclose(p2);
}
void findKeywordsOrIdentifiers(char str[]){
    p1 = fopen("tokens.txt", "r");
    p2=fopen("report_170104124.txt","a");
    int inc=0,index=0;
    char f[20];
    if(strcmp(str,"kw")==0)
        fprintf(p2,"\n\nKeywords: ");
    else
        fprintf(p2,"\n\nIdentifiers: ");
    if(!p1)
        printf("\nFile can't be opened!");
    else{
        while((c=fgetc(p1))!=EOF){
            if(c=='['){
                while((c=fgetc(p1))!=' '){
                    f[index++]=c;
                }
                f[index]='\0';
                if(strcmp(f,str)==0){
                    if(inc==1)
                        fputc(',',p2);
                    else if(inc==0)
                        inc=1;
                    while((c=fgetc(p1))!=']'){
                        fputc(c,p2);
                    }
                }
                index=0;
                f[index]='\0';
            }
        }
    }
    fclose(p1);
    fclose(p2);
}
void findFunctions(struct pair ar[]){
    p2=fopen("report_170104124.txt","a");
    fprintf(p2,"\n\nFunctions: ");
    int inc=0;
    for(int j=1;j<ind;j++){
        if(strcmp(ar[j].idType,"func")==0){
            if(inc==1)
                fputc(',',p2);
            else if(inc==0)
                inc=1;
            fprintf(p2,"%s",ar[j].name);
        }
    }
    fclose(p2);
}
int main(){
    sourceCodeWithLineNo();
    findErrors();
    HeaderFiles();
    findKeywordsOrIdentifiers("id");
    findKeywordsOrIdentifiers("kw");
    findFunctions(hash_table);
    p2 = fopen("report_170104124.txt","r");
    while((c=fgetc(p2))!=EOF)
		printf("%c",c);
    fclose(p2);
    printf("\n");
    return 0;
}
