#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

#include "cipher.h"
extern void encryptMatrix();
extern void decryptMatrix();
extern void printMatrix();
extern void initMatrix();

void delete(char *username);
void add(char *username, char *password, char *type);
int edit(char *username, char *password, char *type, char *username_2, char *password_2, char *type_2);
int verify(char *username, char *password);
void view();
void loadFile(char buf[50][50]);
void writeFile(char buf[50][50]);
void printUsage();

#include "menu.h"
extern int menu();

int main(int argc, char *argv[])
{
    // For debugging
    //printf("Number arguments: %d\n", argc);

    if ( argc == 1 ) {
        printUsage();
    }

    int i;
    for ( i = 1; i < argc; i++ ) {
        if ( strcmp(*(argv + i), "-menu") == 0 ) {
            // MENU stuff here!
            // in menu.c
            puts("MENU");
            if ( menu() == 0 ) {
                return EXIT_SUCCESS;
            } else return EXIT_FAILURE;
        }
        if ( strcmp(*(argv + i), "-add") == 0 ) {
            // ADD stuff here
            // can be done in place
            puts("ADD");
            int i;
            int counter = 0;
            char *username;
            char *password;
            char *type;
            for ( i = 1; i < argc; i++ ) {
                if ( strcmp(*(argv + i), "-del") == 0 ||
                        strcmp(*(argv + i), "-edit") == 0 ||
                        strcmp(*(argv + i), "-verify") == 0 ||
                        strcmp(*(argv + i), "-menu") == 0 ) {
                    // Error occured using with other arguments.
                    printUsage();
                } else if ( strcmp(*(argv + i), "-add") != 0 ) {
                    if(counter == 0) {
                        username = strdup(*(argv+i));
                        // handle error
                        if( username == NULL ) {
                            printf("ERROR reading username.");
                            return;
                        }
                        counter = counter + 1;
                        continue;
                    }
                    if ( counter == 1) {
                        password = strdup(*(argv+i));
                        if ( password == NULL ) {
                            printf("ERROR reading password.");
                            return;
                        }
                        counter = counter + 1;
                        continue;
                    }
                    if ( counter == 2 ) {
                        type = strdup(*(argv+i));
                        if( type == NULL ) {
                            printf("ERROR reading type.");
                            return;
                        }
                        counter + 1;
                        continue;
                    }
                    if( counter == 3 ) {
                        break;
                    }
                }
            }
            add(username, password, type);
        }
        if ( strcmp(*(argv + i), "-del") == 0 ) {
            // DEL stuff here
            // can be done in place
            // decryption through cipher
            puts("DEL");
            char *username_del;
            int i;
            for ( i = 1; i < argc; i++ ) {
                if ( strcmp(*(argv + i), "-add") == 0 ||
                        strcmp(*(argv + i), "-edit") == 0 ||
                        strcmp(*(argv + i), "-verify") == 0 ||
                        strcmp(*(argv + i), "-menu") == 0 ) {
                    // Error occured using with other arguments.
                    printUsage();
                } else if ( strcmp(*(argv + i), "-del") != 0) {
                    // Save the string to use later
                    username_del = strdup(*(argv + i));
                    printf("user to be deleted : %s\n",username_del);
                    if(username_del == NULL) {
                        printf("Error getting username in delete()\n");
                        return;
                    }
                    
                    break;
                }
            }
            delete(username_del);
            return EXIT_SUCCESS;
        }
        if ( strcmp(*(argv + i), "-edit") == 0 ) {
            // EDIT stuff here
            // can be done in place
            puts("EDIT");

            int i;
            int counter = 0;
            char *username;
            char *password;
            char *type;
            char *username_2;
            char *password_2;
            char *type_2;
            if ( argc != 8 ) {
                puts("ERROR:\n\tincorrect arguments\n");
                printUsage();
                return;
            }
            for ( i = 2; i < argc; i++ ) {
                if ( strcmp(*(argv + i), "-del") == 0 ||
                        strcmp(*(argv + i), "-add") == 0 ||
                        strcmp(*(argv + i), "-verify") == 0 ||
                        strcmp(*(argv + i), "-menu") == 0 ) {
                    // Error occured using with other arguments.
                    printUsage();
                    return;
                } else if ( strcmp(*(argv + i), "-edit") != 0 ) {
                    if(counter == 0) {
                        username = strdup(*(argv+i));
                        // handle error
                        if( username == NULL ) {
                            printf("ERROR reading username.");
                            return;
                        }
                        counter = counter + 1;
                        continue;
                    }
                    if ( counter == 1) {
                        password = strdup(*(argv+i));
                        if ( password == NULL ) {
                            printf("ERROR reading password.");
                            return;
                        }
                        counter = counter + 1;
                        continue;
                    }
                    if ( counter == 2 ) {
                        type = strdup(*(argv+i));
                        if( type == NULL ) {
                            printf("ERROR reading type.");
                            return;
                        }
                        counter = counter + 1;
                        continue;
                    }
                    if ( counter == 3 ) {
                        username_2 = strdup(*(argv+i));
                        if( username_2 == NULL ) {
                            printf("ERROR reading new username.");
                            return;
                        }
                        counter = counter + 1;
                        continue;
                    }
                    if ( counter == 4 ) {
                        password_2 = strdup(*(argv+i));
                        if( password_2 == NULL ) {
                            printf("ERROR reading new password.");
                            return;
                        }
                        counter = counter + 1;
                        continue;
                    }
                    if ( counter == 5 ) {
                        type_2 = strdup(*(argv+i));
                        if( type_2 == NULL ) {
                            printf("ERROR reading new type.");
                            return;
                        }
                        counter = counter + 1;
                        continue;
                    }
                    if( counter == 6 ) {
                        break;
                    }
                }
            }
            // For debugging
            printf("Old username: %s\n", username);
            printf("Old password: %s\n", password);
            printf("Old type: %s\n", type);
            printf("New username: %s\n", username_2);
            printf("New password: %s\n", password_2);
            printf("New type: %s\n", type_2);
            
            if ( edit(username, password, type, username_2, password_2, type_2) == 0 ) {
                return EXIT_SUCCESS;
            } else {
                printf("No matching username and password found.\n");
                return EXIT_FAILURE; 
            }
        }
        if ( strcmp(*(argv + i), "-verify") == 0 ) {
            // VERIFY stuff here
            // uses the cipher
            puts("VERIFY");
            int i;
            int counter = 0;
            char *username;
            char *password;
            for ( i = 1; i < argc; i++ ) {
                if ( strcmp(*(argv + i), "-del") == 0 ||
                        strcmp(*(argv + i), "-edit") == 0 ||
                        strcmp(*(argv + i), "-add") == 0 ||
                        strcmp(*(argv + i), "-menu") == 0 ) {
                    // Error occured using with other arguments.
                    printUsage();
                    return EXIT_FAILURE;
                } else if ( strcmp(*(argv + i), "-verify") != 0 ) {
                    if(counter == 0) {
                        username = strdup(*(argv+i));
                        // handle error
                        if( username == NULL ) {
                            printf("ERROR reading username.");
                            return;
                        }
                        counter = counter + 1;
                        continue;
                    }
                    if ( counter == 1) {
                        password = strdup(*(argv+i));
                        if ( password == NULL ) {
                            printf("ERROR reading password.");
                            return;
                        }
                        counter = counter + 1;
                        continue;
                    }
                    if( counter == 2 ) {
                        break;
                    }
                }
            }

            printf("username:%s\n",username);
            printf("password:%s\n",password);

            if ( verify(username, password) == 0 ) {
                printf("VALID\nusername and password verified.\n");
                return EXIT_SUCCESS;
            } else {
                printf("INVALID\nusername and password did not match any of our records.\n");
                return EXIT_FAILURE;
            }
        }
        if ( strcmp(*(argv + i), "-view") == 0 ) {
            // secret unsecure backdoor
            // This backdoor is specially for you Mr TA.
            // Is not handled as an error if used with other arguments
            // because it is assumed the user knows what s/he is doing
            // when using -view
            view();
            return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;

}

void delete(char *username_del)
{
    //puts("Inside delete();");

    //Do stuff with the string
    char matrix[50][50];
    loadFile(matrix);
    //printMatrix(matrix);

    int j;
    for (j = 0; matrix[0][j] != '\0'; j++) {
        int i = 0;
        char record[50];

        int z;
        // Copy over username of record
        for (z = 0; matrix[z][j] != ','; z++) {
            record[z] = matrix[z][j];
        }
        record[z] = '\0';
        
        if ( strcmp(record, username_del) == 0 ) {
            // Copy over the lower records up to cover 
            // over the record to be deleted.
            //puts("They are equal");
            int y = j;
            int x;
            if(matrix[0][y+1] == '\0') {
                matrix[0][y] = '\0';
            }
            for (; matrix[0][y+1] != '\0' ; y++) {
                for (x = 0; matrix[x][y+1] != '\0'; x++) {
                    matrix[x][y] = matrix[x][y+1];
                    if(matrix[0][y+1] == '\0') {
                        matrix[0][y] = '\0';
                    }
                }
                // Add null terminating char
                matrix[x][y] = '\0';
            }
            // Add null terminating character
            matrix[0][y] = '\0';
            break;
        }
    }
    //printMatrix(matrix);
    writeFile(matrix);

}

void add(char *username, char *password, char *type)
{
    //puts("inside of add");
    
    char matrix[50][50];
    loadFile(matrix);
    //printMatrix(matrix);
    
    // CHECK if the username already exists
    int y;
    for ( y = 0; matrix[0][y] != '\0'; y++ ) {
        int z;
        char record_user[50];
        for ( z = 0; matrix[z][y] != ','; z++ ) {
            record_user[z] = matrix[z][y];
        }
        record_user[z] = '\0';

        if ( strcmp(record_user, username) == 0 ) {
            printf("ERROR\n\tThe username already exists in our records. Please choose another one.\n");
            return;
        }
    }

    int j = 0;
    while ( matrix[0][j] != '\0') {
        j++;
    }

    int i;
    for (i = 0; *(username + i) != '\0'; i++) {
        matrix[i][j] = *(username + i);
    }
    // Add the comma and space
    matrix[i][j] = ',';
    i = i + 1;
    matrix[i][j] = ' ';
    i = i + 1;

    int password_count;
    for ( password_count = 0;*(password + password_count) != '\0'; i++, password_count++) {
        matrix[i][j] = *(password + password_count);
    }
    // Add the comma and space
    matrix[i][j] = ',';
    i = i + 1;
    matrix[i][j] = ' ';
    i = i + 1;
    
    int type_count;
    for (type_count = 0; *(type + type_count) != '\0'; i++, type_count++) {
        matrix[i][j] = *(type + type_count);
    }
    // Add newline
    matrix[i][j] = '\n';
    i = i+1;
    // Add null terminating char at end of line
    matrix[i][j] = '\0';

    // Add null terminating char on first of next line
    j = j+1;
    matrix[0][j] = '\0';
    //printMatrix(matrix);

    writeFile(matrix);


}

int edit(char *username, char *password, char *type, char *username_2, char *password_2, char *type_2)
{
    /*
     * returns 0 if successful
     * else
     * returns -1
     * */
    char matrix[50][50];
    loadFile(matrix);

    int j;
    for (j = 0; matrix[0][j] != '\0'; j++) {
        int i = 0;
        char record_user[50];
        char record_pass[50];
        char record_type[50];

        int z = 0;
        int cnt;    // counter for the new strings
        // Copy over username of record
        for (; matrix[z][j] != ','; z++) {
            record_user[z] = matrix[z][j];
        }
        record_user[z] = '\0';
        z = z + 2;
        for (cnt = 0; matrix[z][j] != ','; z++, cnt++) {
            record_pass[cnt] = matrix[z][j];
        }
        record_pass[cnt] = '\0';
        z = z + 2;
        for (cnt = 0; matrix[z][j] != '\0'; z++, cnt++) {
            record_type[cnt] = matrix[z][j];
        }
        record_type[cnt] = '\0';

        // For debugging
        //printf("User compared:%s\n",record_user);
        //printf("Pass compared:%s\n",record_pass);
        //printf("Type compared:%s\n",record_type);
        
        if ( strcmp(record_user, username) == 0 && strcmp(record_pass, password) == 0 ) {
            puts("Found matching username and password");
            z = 0;
            int counter = 0; // to know which argument we are copying over to the array.
            cnt = 0;        // reuse the counter for individual arguments.
            for (; counter < 3; z++, cnt++) {
                if ( counter == 0 ) {
                    if ( *(username_2 + cnt) == '\0' ) {
                        matrix[z][j] = ',';
                        z = z + 1;
                        matrix[z][j] = ' ';
                        z = z + 1;
                        cnt = 0;                // reset the individual counter
                        counter = counter + 1;  // update the arguments counter
                    } else {
                        matrix[z][j] = *(username_2 + cnt);
                    }
                }
                if ( counter == 1 ) {
                    if ( *(password_2 + cnt) == '\0' ) {
                        matrix[z][j] = ',';
                        z = z + 1;
                        matrix[z][j] = ' ';
                        z = z + 1;
                        cnt = 0;                // reset the individual counter
                        counter = counter + 1;  // update the arguments counter
                    } else {
                        matrix[z][j] = *(password_2 + cnt);
                    }
                }
                if ( counter == 2 ) {
                    if ( *(type_2 + cnt) == '\0' ) {
                        counter = counter + 1;  // update the arguments counter
                        // Add newline and  null terminating char to the end of the row
                        matrix[z][j] = '\n';
                        z = z + 1;
                        matrix[z][j] = '\0';
                    } else {
                        matrix[z][j] = *(type_2 + cnt);
                    }
                }
            }

            //printMatrix(matrix);
            writeFile(matrix);
            return 0;
        }
    }
    // If no username and password combination matches
    return -1;
}

int verify(char *username, char *password)
{
    /*
     * returns 0 if the username and password matches a record
     * returns -1 else
     * */
    char matrix[50][50];
    loadFile(matrix);

    int j;
    for (j = 0; matrix[0][j] != '\0'; j++) {
        char record_user[50];
        char record_pass[50];

        int z = 0;
        int cnt;    // counter for the new strings
        // Copy over username of record
        for (; matrix[z][j] != ','; z++) {
            record_user[z] = matrix[z][j];
        }
        record_user[z] = '\0';
        z = z + 2;
        for (cnt = 0; matrix[z][j] != ','; z++, cnt++) {
            record_pass[cnt] = matrix[z][j];
        }
        record_pass[cnt] = '\0';

        // For debugging
        //printf("User compared:%s\n",record_user);
        //printf("Pass compared:%s\n",record_pass);
        if ( strcmp(username, record_user) == 0 && strcmp(password, record_pass) == 0 ) {
            return 0;
        }
    }
    return -1;
}

void view(void)
{
    char matrix[50][50];
    loadFile(matrix);
    printMatrix(matrix);
}

void loadFile(char buf[50][50])
{
    initMatrix(buf);
    FILE *passwords;
    passwords = fopen("./password.csv", "r");
    if ( passwords == NULL ) {
        //printf("Error in loadfile(). Null file\n");
        return;
    }

    int i = 0;
    char line[50];
    while( fgets(line, 49, passwords) && i < 50 ) {

        int j;
        for (j = 0; line[j]!='\0' && i < 49; j++) {
            buf[j][i] = line[j];
        }
        //Add null terminating character
        buf[j][i] = '\0';
        i = i+1;

    }

    // Add null terminating character
    buf[0][i] = '\0';

    if ( !feof(passwords) ) {
        printf("Only part of the file was read. Please increase limit of matrix beyond 50.\n");
    }

    // Decrypt stuff
    decryptMatrix(buf);
    //printMatrix(buf);
    fclose(passwords);

}

void writeFile(char buf[50][50])
{
    FILE *passwords;
    passwords = fopen("./password.csv", "w+");
    if ( passwords == NULL ) {
        printf("ERROR in writeFile(). file not loaded\n");
        return;
    }

    encryptMatrix(buf);

    int j;
    for (j = 0; buf[0][j] != '\0'; j++) {
        int i;
        for (i = 0; buf[i][j] != '\0'; i++) {
            fputc(buf[i][j], passwords);
        }
    }

    fclose(passwords);
    return;
}


void printUsage()
{
    puts("USAGE");
    puts("passweb -menu -add -del -edit -verify username password type user_2 pass_2 type_2\n");
    puts("OPTIONS");
    puts("-menu,\n\tignores all other parameters and puts the program into menu mode.\n");
    puts("-add,\n\tadds a new username/password/type tuple to the password file. \
Other switches must not be used in conjunction\n\te.g passweb -add username password type\n");
    puts("-del,\n\tdeletes one record from the password file\n\te.g passweb -del username\n");
    puts("-edit,\n\tedits the username, password, type with new combination provided.\n\te.g passweb -edit username password type user_2 pass_2 type_2\n");
    puts("-verify,\n\tverifies username and password arguments and outputs VALID or INVALID to stdout.\n\te.g passweb -verify username password\n");
    puts("-view,\n\tA super secret backdoor that should be removed some time if seriously used.\
It unencrypts the file and prints it with extra spaces for clear viewing.\n\te.g passweb -view");
}
