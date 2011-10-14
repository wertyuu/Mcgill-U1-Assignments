#include <stdio.h>
#include <stdlib.h>

void getInputUser(void);

char Matrix[50][50];

int main(void)
{
    printf("MAIN MENU\n");
    printf("=========\n");
    printf("1. Input text\n2. Encrypt\n3. Decrypt\n4. Exit\nSelection: ");

    puts("");
    char a = '\n';
    char b = '\n';
    if(a==b)puts("yen");
    
    while(1){
        char line[50];
        gets(line);
        printf("%s", line);
        int i;
        for(i=0;i<50;i++) {
            if(line[i]=='\0') {
                break;
            }
        }
    }
    return 0;
}
