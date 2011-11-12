#include <stdio.h>
#include <stdlib.h>

/*
 * It is assumed that this program is run in 
 * the same directory as passweb.
 * */

int main()
{
    char junk;
    char username[20];
    char password[20];
    printf("Enter username: ");
    scanf("%s", username);
    while ( (junk = getchar()) != EOF && junk != '\n' );
    printf("Enter password: ");
    scanf("%s", password);

    char command[50] = "./passweb -verify ";
    int i = 18;
    int j;
    for ( j = 0; username[j] != '\0'; j++, i++ ) {
        command[i] = username[j];
    }
    command[i] = ' ';
    i = i + 1;
    for ( j = 0; password[j] != '\0'; j++, i++ ) {
        command[i] = password[j];
    }
    command[i] = '\0';

    printf("%s", command);

    system(command);

}
