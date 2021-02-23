/*We have all the lexemes marked as different types of tokens like keywords, identifiers, operators, separators, 
parentheses, numbers, etc. Now we generate a Symbol Table describing the features of the identifiers. Then, we generate 
a modified token stream in accordance with the Symbol Table for processing by the next phase, that is, Syntax Analysis.*/
#include<stdio.h>
#include<string.h>
#define size 10000
FILE *p1,*p2,*p3;
int ind=1,isId=0,isLocal=0,i=0;
char idT,val[20],scope[20],c,str[20];

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
void valueAssignToVar(struct pair ar[],int key){
    int j=0;
    while((c=fgetc(p2))!=']'){
        if(c!='[' && c!=' ')
            val[j++]=c;
    }
    val[j]='\0';
    strcpy(ar[key].value,val);
    fprintf(p3,"] [%s",val);
}
void update(struct pair ar[],int updatedIndex){
    if(idT=='='){
        valueAssignToVar(ar,updatedIndex);
    }
    isId=0;
}
void insert(struct pair ar[]){
    if(strcmp(str,"int")==0||strcmp(str,"double")==0||strcmp(str,"float")==0||strcmp(str,"char")==0){
        ar[ind].slNo=ind;
        strcpy(ar[ind].dataType,str);
    }
    else if(isId==1){
        strcpy(ar[ind].name,str);
        fprintf(p3," %d] [%c",ind,idT);
        if(strlen(scope)==0)
            strcpy(ar[ind].scope,"global");
        else
            strcpy(ar[ind].scope,scope);
        if(idT=='='){
            valueAssignToVar(ar,ind);
            strcpy(ar[ind].idType,"var");
        }
        else if(idT!='('){
            strcpy(ar[ind].idType,"var");
        }
        else{
            strcpy(ar[ind].idType,"func");
            strcpy(scope,str);
            isLocal=1;
        }
        ++ind;
        isId=0;
    }
}
void search(struct pair ar[]){
    int j=1,isUpdated=0;
    for(;j<ind;j++){
        if(strcmp(ar[j].name,str)==0 && strcmp(scope,ar[j].scope)==0){
            fprintf(p3," %d] [%c",j,idT);
            isUpdated=1;
            break;
        }
    }
    if(isUpdated==1)
        update(ar,j);
    else
        insert(ar);
}

void createTokenStream(){
    p1 = fopen("s3_input.txt", "r");
    p2=fopen("output.txt","w");
    if(!p1)
        printf("\nFile can't be opened!");
    else{
        c=fgetc(p1);
        while(c!=EOF){
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
    printf("\n\nStep-1:\n-------\n");
    p2 = fopen("output.txt","r");
    while((c=fgetc(p2))!=EOF)
		printf("%c",c);
    fclose(p2);
    printf("\n");
}
void checkIfToInsert(){
    fputc(c,p3);
    while((c=fgetc(p2))!=']'){
        if(c==' '){
            isId=1;
            i=0;
            str[i]='\0';
        }
        else
            str[i++]=c;
        if(isId!=1)
            fputc(c,p3);
    }

    str[i]='\0';
    if(strcmp(str,"int")==0||strcmp(str,"double")==0||strcmp(str,"float")==0||strcmp(str,"char")==0){
        insert(hash_table);
    }
    else if(isId==1){
        while((c=fgetc(p2))!=']'){
            if(c!='['){
                idT=c;
            }
        }
        search(hash_table);
    }
}
int main(){
    int j=0;
    createTokenStream();
    p2 = fopen("output.txt","r");
    p3=fopen("s3_output.txt","w");
    while((c=fgetc(p2))!=EOF){
        i=0;
        if(isLocal==1){
            while(c!='}' && c!=EOF){
                i=0;
                if(c=='[')
                    checkIfToInsert();
                if(strcmp(str,"}")==0){
                    break;
                }
                fputc(c,p3);
                str[0]='\0';
                c=fgetc(p2);
            }
            isLocal=0;
            scope[0]='\0';
        }
        else{
            if(c=='['){
                checkIfToInsert();
                str[0]='\0';
            }
        }
        fputc(c,p3);
    }
    fclose(p2);
    fclose(p3);
    printf("\nSymbol Table:\n");
    printf("-------------");
    display(hash_table);
    printf("\nSyntax analysis:\n");
    printf("----------------\n");
    p3=fopen("s3_output.txt","r");
    while((c=fgetc(p3))!=EOF)
		printf("%c",c);
    fclose(p3);
    printf("\n");
    return 0;
}
