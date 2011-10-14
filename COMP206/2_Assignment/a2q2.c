#include <stdio.h>
#include <stdlib.h>

void getInputUser(void);
void initMatrix(void);

char matrix[50][50];

int main(void)
{
    initMatrix();
    printf("MAIN MENU\n");
    printf("=========\n");
    printf("1. Input text\n2. Encrypt\n3. Decrypt\n4. Exit\nSelection: ");

    getInputUser();
    printf("out of loop");
}

void getInputUser(void)
{
    initMatrix();
    int j = 0;
    while(1) {
        char line[50];
        gets(line);

        if(line[0]=='\n') {
            printf("empty line");
            break;
        }

        printf("%s",line);
        
        int i;
        for (i = 0; line[i] != '\n' && i < 49; i++) {
            matrix[i][j] = line[i];
        }
        matrix[i+1][j] = '\n';
        j = j+1;
    }

}

void initMatrix(void)
{
    int x,y;
    for (x = 0; x < 50; x++) {
        for (y = 0; y < 50; y++) {
            matrix[x][y] = ' ';
        }
    }
}
