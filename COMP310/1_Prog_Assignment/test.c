#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<unistd.h>
#include<string.h>

typedef struct stackD {
    char * string;
    
    struct stackD * prev;
} Stack;

char * popStack(void);
void pushStack(char * string);
int hasEqual(char * nameval);

Stack * directoryStack = NULL; //= (Stack *)malloc(sizeof(Stack));
//directoryStack->prev = NULL;

int main(void)
{

    char * tester1 = "NAME=hello";
    char * tester2 = "NICECATCH";
    char * tester3 = "WELOCEM TO HELL";
    char * tester4 = "This is a val =";

    printf("tester1 has %d equal\n", hasEqual(tester1));
    printf("tester2 has %d equal\n", hasEqual(tester2));
    printf("tester3 has %d equal\n", hasEqual(tester3));
    printf("tester4 has %d equal\n", hasEqual(tester4));
    /*
    pushStack("1/home/jfokka");
    pushStack("2/home/hell");
    pushStack("3/piss/off");
    printf("%s\n", popStack());
    printf("%s\n", popStack());
    pushStack("4/sick");
    printf("%s\n", popStack());
    printf("%s\n", popStack());
    */

    /*

    typedef struct history {
        char * command;
        
        struct history * next;
    }HISTORY;

    HISTORY * commandHist = (HISTORY *)malloc(sizeof(HISTORY));
    HISTORY * current = commandHist;

    current->command = "Hello";
    printf("%s\n", commandHist->command);
    current->next = (HISTORY *)malloc(sizeof(HISTORY));
    current = current->next;

    //current->next = (HISTORY *)malloc(sizeof(HISTORY));
    
    current->command = "World";
    printf("%s\n", commandHist->next->command);
    current = current->next;
    current = NULL;
    
    printf("printing all arguments\n");

    HISTORY * currentprinting = commandHist;

    while (currentprinting != NULL) {
        printf("inside loop");
        printf("%s\n", currentprinting->command);
        currentprinting = currentprinting->next;
    }

    */

    /*

    char string[100];// = "hello world > this that <& hell";
    char * string_array[100];
    int i;

    scanf("%[^\n]s", string);
    printf(" string : %s\n", string);
    string[strlen(string)] ='\0';

    char * token = strtok(string, " ");
    int string_arrayLength = 0;
    string_array[string_arrayLength] = token;

    while( (token = strtok(NULL, " ")) ) {
        ++string_arrayLength;
        string_array[string_arrayLength] = token;
    }
    string_array[string_arrayLength+1] = '\0';
    for (i = 0; string_array[i]!= '\0';++i) {
        printf("String %d: %s\n", i, string_array[i]);
    }

    */

    exit(0);
}

void pushStack(char * string)
{
    Stack * new = (Stack *)malloc(sizeof(Stack));

    new->string = strdup(string);

    new->prev = directoryStack;

    directoryStack = new;
}

char * popStack(void)
{
    if ( directoryStack != NULL ) {
        char * command = strdup(directoryStack->string);

        Stack * toBeFreed = directoryStack;

        directoryStack = directoryStack->prev;

        free(toBeFreed);

        return command;
    }

    return "Empty Stack; no more directories\n";
}

int hasEqual(char * nameval)
{
    int result = 0;
    int i;
    for ( i = 0; *(nameval+i) != 0; i++) {
        if ( *(nameval+i) == '=' ) {
            result = 1;
            return result;
        }
    }

    return result;
}
