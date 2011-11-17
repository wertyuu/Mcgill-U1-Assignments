#include <stdio.h>
#include <stdlib.h>

struct PASSWORD_REC 
{
    char username[50];
    char password[50];
    char usertype[50];
};

struct NODE
{
    struct PASSWORD_REC user;
    struct NODE *next;
}

int main(void)
{
    FILE *bank;
    bank = fopen("password.csv","r");
    
}
