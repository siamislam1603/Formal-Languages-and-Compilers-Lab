// Lab Exercise-2
#include<stdio.h>
#include<string.h>

char str[100];
int f,l,i=0;
void Factor()
{
    if(isdigit(str[i]) || (str[i] >= 'a' && str[i] <= 'e'))
    {
        i++;
        f = 1;
        return;
    }
    else if (str[i] == '(')
    {
        i++;
        Exp();
        if(str[++i] == ')')
        {
            f = 1;
            return;
        }
    }
}
void Term()
{
    Factor();
    if(i<l-1)
    {
        if(str[i] == '*' || str[i] == '/')
        {
             i++;
             Factor();
        }
    }
    else if(f == 1)
        return;
}
void Exp()
{
    Term();
    if(i<l-1)
    {
        if(str[i] == '+' || str[i] == '-')
        {
             i++;
             Term();
        }
    }
    else if(f == 1)
        return;

}
int main(void)
{
    printf("Enter simple arithmetic expressions: ");
    scanf("%s", str);
    l = strlen(str);
    if(l>=1)
        Exp();
    else
        printf("Empty!\n");
    if(i == l && f == 1)
        printf("Valid Expression\n");
    else
        printf("Invalid Expression\n");

    return 0;
}
