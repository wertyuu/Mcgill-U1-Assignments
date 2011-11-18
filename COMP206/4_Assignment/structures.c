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
        
        //printf("%s\n%s\n%s", username, password, usertype);
        memcpy(record.username, username, strlen(username)+1);
        memcpy(record.password, password, strlen(password)+1);
        memcpy(record.usertype, usertype, strlen(usertype)+1);
        
        //printf("%s, %s, %s\n", record.username, record.password, record.usertype);
        passwordArray[i] = record;
        i++;
    }
    
    NODE head, *current;

    current = &head;
    int j;
    
    for ( j = i-1; j >= 0 ; j-- ) {
        printf("\n%s\n",passwordArray[j].username);
        current->user = passwordArray[j];
        printf("%s\n",current->user.username);
        if (j == 0) {
            current->next = NULL;
            break;
        }
        current->next = malloc(sizeof(PASSWORD_REC));
        current = current->next;
    }
    //printf("%s\n", head.user.username);
    
    //printf("%d\n", i);
    //printf("%s\n", passwordArray[0].username);
    //printf("%s, %s, %s", passwordArray[0].username, passwordArray[0].password, passwordArray[0].usertype);
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
    /*
    printf("%s, %s, %s", ncurrent->user.username, ncurrent->user.password, ncurrent->user.usertype);
    ncurrent = ncurrent->next;
    printf("%s, %s, %s", ncurrent->user.username, ncurrent->user.password, ncurrent->user.usertype);
    puts("");
    */

    puts("Contents of Linked List in Reverse Order");
    while ( 1 ) {
        printf("%s, %s, %s\n", ncurrent->user.username, ncurrent->user.password, ncurrent->user.usertype);
        if ( ncurrent->next == NULL ) {
            //printf("%s, %s, %s", ncurrent->next->user.username, ncurrent->next->user.password, ncurrent->next->user.usertype);
            break;
        }
        ncurrent = ncurrent->next;
    }

    fclose(bank);


}
