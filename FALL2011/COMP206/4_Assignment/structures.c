// Jonathan Fokkan
// 260447938
// Question 3
// Assignment 4

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct password_rec 
{
    char username[50];
    char password[50];
    char usertype[50];
}PASSWORD_REC;

typedef struct node
{
    PASSWORD_REC user;
    struct node *next;
} NODE;

int main(void)
{
    puts("Welcome to Reverse Password Print.");
    FILE *bank;
    bank = fopen("password.csv","r");
    if ( bank == NULL ) {
        puts("Could not find password.csv file.");
        return EXIT_FAILURE;
    }

    PASSWORD_REC passwordArray[50];
   
    int i = 0;
    char line[150];
    while ( fgets(line,149, bank) ) {
        PASSWORD_REC record;// = malloc(sizeof(PASSWORD_REC));
        char username[50];
        char password[50];
        char usertype[50];
        sscanf(line,"%s %s %s", username, password, usertype);
        //To remove the commas
        username[strlen(username)-1] = '\0';
        password[strlen(password)-1] = '\0';
        
        memcpy(record.username, username, strlen(username)+1);
        memcpy(record.password, password, strlen(password)+1);
        memcpy(record.usertype, usertype, strlen(usertype)+1);
        
        passwordArray[i] = record;
        i++;
    }
    
    NODE head, *current;

    current = &head;
    int j;
    
    // creating the linked list by linking them in reverse order as stated in assignment
    for ( j = i-1; j >= 0 ; j-- ) {
        current->user = passwordArray[j];
        if (j == 0) {
            current->next = NULL;
            break;
        }
        current->next = malloc(sizeof(PASSWORD_REC));
        current = current->next;
    }

    puts("");
    puts("Contents of CSV file");
    int z;
    for ( z = 0; z < i; z++ ) {
        printf("%s, %s, %s\n", passwordArray[z].username, passwordArray[z].password, passwordArray[z].usertype);
    }
    puts("");

    puts("Contents of Array in reverse order");
    for ( z = i-1; z >= 0; z-- ) {
        printf("%s, %s, %s\n", passwordArray[z].username, passwordArray[z].password, passwordArray[z].usertype);
    }

    NODE *ncurrent;
    ncurrent = &head;

    puts("");
    puts("Contents of Linked List in Reverse Order");
    while ( 1 ) {
        printf("%s, %s, %s\n", ncurrent->user.username, ncurrent->user.password, ncurrent->user.usertype);
        if ( ncurrent->next == NULL ) {
            break;
        }
        ncurrent = ncurrent->next;
    }

    fclose(bank);
    return EXIT_SUCCESS;
}
