#include <stdio.h>
#include <stdlib.h>

void getInputUser(void);
void initMatrix(void);
void encryptMatrix(int shift_N);
void decryptMatrix(int shift_N);
void printMatrix(void);
void countMatrixDimensions(void);
void printMatrixTranspose(void);

char matrix[50][50];

//Length and height of matrix with input in
//excluding the null terminating character
int x_matrix = 0;
int y_matrix = 0;

int main(void)
{
    initMatrix();
    int done = 1;
    char userCommand[10];
    char junk;
    int shift_N = 0;

    while(done) {
        printf("MAIN MENU\n");
        printf("=========\n");
        printf("1. Input Text\n2. Encrypt\n3. Decrypt\n4. Exit\nSelection: ");
        scanf("%s",userCommand);
        
        switch(userCommand[0]) {
            case '1':
                while((junk = getchar())!= EOF && junk != '\n');
                puts("Enter Input:");
                getInputUser();
                countMatrixDimensions();
                puts("----Input stored----\n");
                break;
            case '2':
                printf("Enter an integer: ");
                while((junk = getchar())!= EOF && junk != '\n');
                scanf("%d", & shift_N);
                while((junk = getchar())!= EOF && junk != '\n');

                encryptMatrix(shift_N);
                printMatrixTranspose();
                puts("");
                break;
            case '3':
                printf("Enter an integer: ");
                while((junk = getchar())!= EOF && junk != '\n');
                scanf("%d", & shift_N);
                while((junk = getchar())!= EOF && junk != '\n');
                decryptMatrix(shift_N);
                printMatrix();
                puts("");
                break;
            case '4':
                done = 0;
                break;
            default:
                puts("***********************************************");
                puts("* Please enter a number 1 to 4 to use program *");
                puts("***********************************************");
                break;
        }
    }
    return 0;
}

void getInputUser(void)
{
    initMatrix();
    int j = 0;
    while(1) {
        char line[50];
        gets(line);

        //printf("%s",line);
        
        int i;
        for (i = 0; line[i]!='\0' && i < 49; i++) {
            matrix[i][j] = line[i];
        }
        //Add null terminating character
        matrix[i][j] = '\0';
        j = j+1;
        
        //Test for blank line
        if(line[0]=='\0') {
            //printf("empty line\n");
            break;
        }
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

void encryptMatrix(int shift_N)
{
    int j;
    for (j = 0; j < y_matrix; j++) {
        int i;
        for (i = 0; i < x_matrix;i++) {
            int character = matrix[i][j];
            if(matrix[i][j] >= 'A' && matrix[i][j] <= 'Z') {
                character = character + shift_N;
                while (character > 'Z') {
                    character = character - ('Z' - 'A' + 1);
                }
                matrix[i][j] = character;
            } else if(matrix[i][j] >= 'a' && matrix[i][j] <= 'z') {
                character = character + shift_N;
                while(character > 'z') {
                    character = character - ('z' - 'a' + 1);
                }
                matrix[i][j] = character;
            }
        }
    }
}

void decryptMatrix(int shift_N)
{
    int j;
    for (j = 0; j < y_matrix; j++) {
        int i;
        for (i = 0; i < x_matrix;i++) {
            int character = matrix[i][j];
            if(matrix[i][j] >= 'A' && matrix[i][j] <= 'Z') {
                character = character - shift_N;
                while (character < 'A') {
                    character = character + ('Z' - 'A' + 1);
                }
                matrix[i][j] = character;
            } else if(matrix[i][j] >= 'a' && matrix[i][j] <= 'z') {
                character = character - shift_N;
                while(character < 'a') {
                    character = character + ('z'-'a'+1);
                }
                matrix[i][j] = character;
            }
        }
    }
}

void printMatrix(void)
{
    //for debugging purposes
    int j = 0;
    while(matrix[0][j] != '\0') {
        int i = 0;
        while (matrix[i][j]!='\0') {
            putchar(matrix[i][j]);
            i = i+1;
        }
        j = j + 1;
        putchar('\n');
    }
}

void countMatrixDimensions(void)
{
    int j = 0;
    while(matrix[0][j] != '\0') {
        int i = 0;
        while (matrix[i][j]!='\0') {
            if(i > x_matrix) {
                x_matrix = i;
            }

            i = i+1;
        }
        y_matrix = j;
        j = j + 1;
    }

    x_matrix = x_matrix + 1;
    y_matrix = y_matrix + 1;
}

void printMatrixTranspose(void)
{
    int i;
    for (i = 0; i < x_matrix; i++) {
        int j;
        for (j = 0; j < y_matrix; j++) {
            if(matrix[i][j] == '\0') {
                putchar(' ');
            } else {
                putchar(matrix[i][j]);
            }
        }
    }
    putchar('\n');
}
