
void encryptMatrix();
void decryptMatrix();
void printMatrix();
void initMatrix();

void encryptMatrix(char matrix[50][50])
{
    int j;
    for ( j = 0; matrix[0][j] != '\0';j++ ) {
        int i;
        for (i = 0; matrix[i][j] != '\n';i++ ) {
            int character = matrix[i][j];
            matrix[i][j] = character + 5;
        }
    }
    /*
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
    */
}

void decryptMatrix(char matrix[50][50])
{

    int j;
    for ( j = 0; matrix[0][j] != '\0';j++ ) {
        int i;
        for (i = 0; matrix[i][j] != '\n';i++ ) {
            int character = matrix[i][j];
            matrix[i][j] = character - 5;
        }
    }

    /*
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
    */
}

void printMatrix(char matrix[50][50])
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
        // newline used if no newline in the matrix.
        //putchar('\n');
    }
    putchar('\n');
}

void initMatrix(char matrix[50][50])
{
    int x,y;
    for (x = 0; x < 50; x++) {
        for (y = 0; y < 50; y++) {
            if ( x == 49 ) {
                matrix[x][y] = '\0';
            } else if (x == 0 && y == 0) {
                matrix[x][y] = '\0';
            } else if ( x == 49 ) {
                matrix[0][y] = '\0';
            } else {
                matrix[x][y] = ' ';
            }
        }
    }
}
