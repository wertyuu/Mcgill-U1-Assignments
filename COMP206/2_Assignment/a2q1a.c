#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

int main(void)
{
    printf("Welcome to divide!\n");

    
    int secondNumber = 0;
    int firstNumber = 0;
    int quotient = 0;
    int remainder = 0;
    int repeat = TRUE;
    char repeatCommand[20];
    int junk;

    while(repeat){
        printf("First number: ");
        scanf("%d", & firstNumber);

        while ((junk = getchar()) != EOF && junk != '\n') ;

        printf("Second number: ");
        scanf("%d", & secondNumber);

        while ((junk = getchar()) != EOF && junk != '\n') ;

        if(secondNumber > firstNumber) {
            printf("The first number must be larger than the second number. I am switching the numbers for you.\n");
            int temp = firstNumber;
            firstNumber = secondNumber;
            secondNumber = temp;
        }
        
        int i;
        int x = firstNumber;
        int y = secondNumber;
        for (i = 0;x >= y;i++) {
            x = x - y;
            remainder = x;
        }
        quotient = i;

        printf("You input %d and %d which gives %d with remainder %d\n",firstNumber, secondNumber, quotient, remainder);
        printf("Would you like to try this again? ");
        scanf("%s",repeatCommand);

        //printf("%d\n",strcasecmp(repeatCommand,"yes"));
        //printf("%d",strcasecmp(repeatCommand,"y"));

        if(strcasecmp(repeatCommand, "yes") == 0 || strcasecmp(repeatCommand, "y") == 0);
        else {
            repeat = FALSE;
        }
    }
    return 0;
}
