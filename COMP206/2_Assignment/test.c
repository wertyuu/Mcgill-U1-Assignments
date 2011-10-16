#include <stdio.h>
#include <stdlib.h>


char Matrix[50][50];

int main(void)
{
    printf("\nMAIN MENU\n");
    printf("=========\n");
    printf("1. Input text\n2. Encrypt\n3. Decrypt\n4. Exit\nSelection: ");

    puts("");
    int a = 'z';
    char b = 'z';

    int in = 100;
    //while (in > 26) {
     //   in = in-26;
    //}
    a = a+in;

    while (a > 'z'){
        a = a-('z'-'a'+1);
    }
    
    b= b+25;
    putchar(a);
    puts("");
    
    return 0;
}
