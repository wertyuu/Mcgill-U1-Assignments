#include <stdio.h>

int main(void)
{
    char tester;
    int repeat = 1;
    char junk;
    printf("Welcome to ASCII:\n");

    while(repeat){
        printf("----> ");
        scanf("%c", & tester);
        printf("ascii: %d\n", tester);
        while((junk = getchar())!=EOF && junk != '\n');
        if(tester == '0'){
            repeat = 0;
        }
    }
}
