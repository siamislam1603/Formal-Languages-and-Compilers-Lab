//Assignment-5
#include<stdio.h>
#include<string.h>
#include <stdbool.h>
int f,i=0,l,s=0;
char str[100];
void stat();
void asgn_stat();
void dscn_stat();
void loop_stat();
bool relop();
void expn();
void extn();
void smpl_expn();
void Term();
void Factor();
int main()
{
    printf("Enter a string:\n");
    scanf("%s", str);
    l = strlen(str);
    printf("\nOutput: ");
    if (l>=1)
        stat();
    else
        printf("Invalid String\n");
    if (l == i && f )
        printf("Valid String\n");
    else
        printf("Invalid String\n");
    return 0;
}

void stat()
{
    asgn_stat();
    if(s==0)
        dscn_stat();
    else if(s==0)
        loop_stat();
}
void asgn_stat()
{
    if(i<l && (str[i]>='a' && str[i]<='e'))
    {
        if(str[++i]=='=')
        {
            i++;
            expn();
        }
        s=1;
    }
}
void expn()
{
    smpl_expn();
    if(f)
        extn();
}
bool relop()
{
    if(f && i<l && (str[i]=='=' || str[i]=='!' || str[i]=='<' || str[i]=='>'))
    {
        i++;
        if(i<l && str[i]=='=')
        {
            i++;
            return true;
        }
    }
    return false;
}
void extn()
{
    if(f && i<l && relop())
        smpl_expn();
}
void extn1()
{
    if(f && i+3<l && str[i]=='e' && str[i+1]=='l' && str[i+2]=='s' && str[i+3]=='e')
    {
        i=i+4;
        stat();
    }
}
void dscn_stat()
{
    if(i<l && str[i]=='i' && str[i+1]=='f')
    {
        i+=2;
        if(str[i]=='(')
        {
            i++;
            expn();
            if(f && i<l && str[i]==')')
            {
                i++;
                stat();
                if(f)
                    extn1();
            }
            else f=0;
        }
        else f=0;
    }
    s=1;
}
void loop_stat()
{
    if(i<l && str[i]=='w' && str[i+1]=='h' && str[i+2]=='i' && str[i+3]=='l' && str[i+4]=='e')
    {
        i+=5;
        if(str[i]=='(')
        {
            i++;
            expn();
            if(f && i<l && str[i]==')')
            {
                i++;
                stat();
            }
            else f=0;
        }
        else f=0;
    }
    else if(i<l && str[i]=='f' && str[i+1]=='o' && str[i+2]=='r')
    {
        i+=3;
        if(str[i]=='(')
        {
            i++;
            asgn_stat();
            if(f && i<l && str[i]==';')
            {
                i++;
                expn();
                if(f && i<l && str[i]==';')
                {
                    i++;
                    asgn_stat();
                    if(f && i<l && str[i]==')')
                    {
                        i++;
                        stat();
                    }
                    else f=0;
                }
                else f=0;
            }
            else f=0;
        }
        else f=0;
    }
}
void smpl_expn()
{
    Term();
    if(f && i<l &&(str[i]=='+' || str[i]=='-'))
    {
        i++;
        Term();
    }
}
void Term()
{
    Factor();
    if(f && i<l && (str[i]=='*' || str[i]=='/'))
    {
        i++;
        Factor();
    }
}
void Factor()
{
    if(i<l && str[i]=='(')
    {
        i++;
        f=1;
        smpl_expn();
        if(f && str[i]==')')
            i++;
        else
            f=0;
    }
    else if(i<l && ((str[i]>='a' && str[i]<='e')||isdigit(str[i])))
    {
        i++;
        f=1;
    }
    else f=0;
}
