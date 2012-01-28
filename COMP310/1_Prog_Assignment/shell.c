#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>

/* Function Prototypes */
char * getDirectory(void);
void cd(char * directory);
void set(char * envs[], char * envChange);
void history(void);
char * popStack(void);
void pushStack(char * string);
void unset(char * string);
int hasEqual(char * nameval);
int hasOutRedirect(char * nameval);
int hasInRedirect(char * nameval);
int hasPipe(char * nameval);
void printExecErrors(int err);

/* data structures */

// For History
typedef struct linked {
    char * string;
    
    struct linked * next;
}LinkedList;

// For pushd and popd
typedef struct stackD {
    char * string;
    
    struct stackD * prev;
} Stack;

/* Global Variables */

char *path, hostname[20], *user, *cwd, *cwd_dir, user_commands[128], *com_tokenized[128], *newEnv[128];
int string_arrayLength, newEnv_len;

LinkedList * com_history, * current_com;
Stack * directoryStack = NULL;

int main(int argc, char **argv, char** envp)
{
    // read the environment variables and determine PATH
    path        = getenv("PATH");
    gethostname(hostname, sizeof(hostname));
    user        = getenv("USER");
    cwd         = getcwd(NULL, 0);
    cwd_dir     = getDirectory();

    printf("\nPATH=\"%s\"\n", path);
    printf("HOSTNAME=\"%s\"\n", hostname);
    printf("USER=\"%s\"\n", user);
    printf("cwd:%s\n\n", cwd);

    com_history = (LinkedList *)malloc(sizeof(LinkedList));
    current_com = com_history;
    
    int pidChild;
    newEnv_len = 0;

    int loop = 1;
    while(loop){

        //updateCwd(cwd);
        cwd_dir     = getDirectory();

        printf("[%s@%s %s]$ ", user, hostname, cwd_dir);
        scanf("%[^\n]s", user_commands);
        printf("user_commands: %s\n", user_commands);

        int junk;
        while ((junk = getchar()) != '\n' && junk != EOF);

        /* For history-----------------------------------------------------------------*/
        current_com->next = (LinkedList *)malloc(sizeof(LinkedList));
        current_com->string = strdup(user_commands);

        current_com = current_com->next;
        current_com->string = "\n";
        current_com->next = NULL;




        /* To tokenize the command with delimiter space */
        char * token = strtok(user_commands, " ");
        
        string_arrayLength = 0;
        com_tokenized[string_arrayLength] = token;
        while( (token = strtok(NULL, " ")) ) {
            ++string_arrayLength;
            com_tokenized[string_arrayLength] = token;
        }
        com_tokenized[string_arrayLength+1] = '\0';


        /*************************************** Debugging purposes *******************************************/
        int i;
        for (i = 0; com_tokenized[i] != '\0'; ++i) {
            printf("Argument %d: %s\n", i, com_tokenized[i]);
        }


        if (strcmp(com_tokenized[0], "echo") == 0) {
            // echo
            printf("echo\n");
            for (i = 1; com_tokenized[i] != '\0'; ++i) {
                printf("%s ", com_tokenized[i]);
            }
            printf("\n");
            //printf("%s\n", com_tokenized[1]);
        } else if (strcmp(com_tokenized[0], "cd") == 0) {
            printf("cd\n");
            cd(com_tokenized[1]);
        } else if (strcmp(com_tokenized[0], "pwd") == 0) {
            printf("pwd\n");
            printf("%s\n", cwd);

        } else if (strcmp(com_tokenized[0], "history") == 0) {
            printf("history\n");
            history();

        } else if (strcmp(com_tokenized[0], "set") == 0) {
            printf("set\n");
            set(envp, com_tokenized[1]);
        } else if (strcmp(com_tokenized[0], "env") == 0) {
            printf("env");

            if ( hasEqual(com_tokenized[1]) ) {
                set(envp, com_tokenized[1]);
                /* Execute External command */

                /* END */

                char * string = strdup(com_tokenized[1]);
                char *name;
                name = strtok(string, "=");
                //Debug
                printf("name=%s;\n", name);
                unset(name);
            }

        } else if (strcmp(com_tokenized[0], "unset") == 0) {
            printf("unset\n");
            unset(com_tokenized[1]);
        } else if (strcmp(com_tokenized[0], "pushd") == 0) {
            printf("pushd\n");
            pushStack(cwd);
            cd(com_tokenized[1]);
        } else if (strcmp(com_tokenized[0], "popd") == 0) {
            printf("popd\n");
            char * directoryPop = popStack();
            cd(directoryPop);
        } else if (strcmp(com_tokenized[0], "exit") == 0) {
            printf("exit\n");
            exit(0);
        } else {
            // handle external commands
            printf("external\n");
            
            int j;
            int z;
            char* execArguments[128];
            for ( j = 0, z = 1; com_tokenized[z] != '\0';j++, z++ ) {
                execArguments[j] = com_tokenized[z];
            }
            execArguments[j] = NULL;

            if ( (pidChild = fork()) == 0 ) {
                if (execvp(com_tokenized[0], execArguments) == -1) {
                    // Handle Error
                    printf("error\n");
                    int errsv = errno;
                    printExecErrors(errsv);
                }
                printf("Hello this should not print \n");
            }

            while(pidChild != wait(0)); /* ignore return code*/
        }
    }
    exit(0);
}

int ls(void)
{
    // implemented with readdir, opendir, scandir
}

void cd(char* directory)
{
    char * dir = directory;
    /* attempting to modify cd to handle escape and quotes */
    if ( string_arrayLength > 1 ) {
        //if ( *()) {
        
        //}
    } else {
        if ( (string_arrayLength == 0 && strcmp( com_tokenized[0], "cd") == 0) || *(directory) == '~' ) {
            dir = getenv("HOME");
        }
    }

    // Implemented with chdir
    if (chdir(dir) == -1) {
        int errsv = errno;
        printf("cd failed on: %s\n", dir);
        if ( errsv == ENOENT) {
            printf("The file does not exist\n");
        }
    }
    //printf("%s\n", getcwd(NULL, 0));
    
    free(cwd);
    cwd = getcwd(NULL, 0);

    return;


}

void set(char * envs[], char * envChange)
{
    if ( strcmp(com_tokenized[0], "set") == 0 && string_arrayLength == 0 ) {
        printf("Printing all ENVs\n");
        char ** env = envs;
        for (; *env != '\0'; env++) {
            printf("%s\n", *env);
        }
        int i;
        for ( i = 0; i < newEnv_len; i++) {
            printf("%s\n", newEnv[i]);
        }
    } else {
        char * string = strdup(envChange);
        char *name, *value;
        name = strtok(string, "=");
        if( (value = strtok(NULL, "=")) == NULL ) {
            printf("Incorrect syntax to set environment variable; call set on name=value\n");
            return;
        }
        printf("name=%s; value=%s", name, value);
        if (setenv(name, value, 1) == -1) {
            int errsv = errno;
            if ( errsv == EINVAL) {
                printf("name is NULL, points to a string of length 0, or contains an '=' character");
            } else if ( errsv == ENOMEM) {
                printf("Insufficient memory to add new variable to the environment.");
            }
            return;
        }
        newEnv[newEnv_len] = strdup(com_tokenized[1]);
        newEnv_len++;
        return;
    }
}

void history(void)
{
    LinkedList * currentPrinting = com_history;
    printf("printing history\n");
    while ( currentPrinting != NULL ) {
        printf("insideLoop\n");
        printf("%s\n", currentPrinting->string);
        currentPrinting = currentPrinting->next;
    }
}

char* getDirectory(void)
{
    // Returns the name of current directory
    char * cwdToBeProcessed = strdup(cwd);
    char * token = strtok(cwdToBeProcessed, "/");
    char * curDir;
    while (token) {
        if ( (token = strtok(NULL, "/")) == NULL ){
            break;
        }
        curDir = strdup(token);
    }
    free(cwdToBeProcessed);
    return curDir;
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
        printf("%s\n", command);
        return command;
    }
    printf("Empty Stack; no more directories\n");
    return ".";
}

void unset(char * string)
{
    if (string_arrayLength == 0 && strcmp(com_tokenized[0], "unset") == 0 ) {
        return;
    }
    if (unsetenv(string) == -1) {
        int errsv = errno;
        if ( errsv == EINVAL) {
            printf("name is NULL, points to a string of length 0, or contains an '=' character");
        } else if ( errsv == ENOMEM) {
            printf("Insufficient memory to add new variable to the environment.");
        }
    }
    
    return;
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

int hasOutRedirect(char * nameval)
{
    int result = 0;
    int i;
    for ( i = 0; *(nameval+i) != 0; i++) {
        if ( *(nameval+i) == '>' ) {
            result = 1;
            return result;
        }
    }
    return result;
}

int hasInRedirect(char * nameval)
{
    int result = 0;
    int i;
    for ( i = 0; *(nameval+i) != 0; i++) {
        if ( *(nameval+i) == '<' ) {
            result = 1;
            return result;
        }
    }
    return result;
}

int hasPipe(char * nameval)
{
    int result = 0;
    int i;
    for ( i = 0; *(nameval+i) != 0; i++) {
        if ( *(nameval+i) == '|' ) {
            result = 1;
            return result;
        }
    }
    return result;
}

void printExecErrors(int err)
{
       if ( err == E2BIG ) {
           printf ("The total number of bytes in the environment (envp) and argument list (argv) is too large.\n");
        } else if ( err == EACCES ) {
            printf("Search permission is denied on a component of the path prefix of filename or the name of a script interpreter.  (See also path_resolution(7).)\n");
        } else if ( err == EACCES ) {
            printf("The file or a script interpreter is not a regular file.\n");
        } else if ( err == EACCES ) {
            printf("Execute permission is denied for the file or a script or ELF interpreter.\n");
        } else if ( err == EACCES ) {
            printf("The file system is mounted noexec.\n");
        } else if ( err == EFAULT ) {
            printf("filename points outside your accessible address space.\n");
        } else if ( err == EINVAL ) {
            printf("An ELF executable had more than one PT_INTERP segment (i.e., tried to name more than one interpreter).\n");
        } else if ( err == EIO ) {
            printf("An I/O error occurred.\n");
        } else if ( err == EISDIR ){
            printf("An ELF interpreter was a directory.\n");
        } else if ( err == ELIBBAD) {
              printf("An ELF interpreter was not in a recognized format.\n");
        } else if ( err == ELOOP) {
            printf("Too many symbolic links were encountered in resolving filename or the name of a script or ELF interpreter.\n");
        } else if ( err == EMFILE ) {
            printf("The process has the maximum number of files open.\n");
        } else if ( err == ENAMETOOLONG ) {
            printf("filename is too long.\n");
        } else if ( err == ENFILE) {
            printf("The system limit on the total number of open files has been reached.\n");
        } else if ( err == ENOENT) {
            printf("The file filename or a script or ELF interpreter does not exist, or a shared library needed for file or interpreter cannot be found.\n");
        } else if ( err == ENOEXEC ) {
              printf("An executable is not in a recognized format, is for the wrong architecture, or has some other format error that means it cannot be executed.\n");
        } else if ( err == ENOMEM ) {
            printf("Insufficient kernel memory was available.\n");
        } else if ( err == ENOTDIR ) {
            printf("A component of the path prefix of filename or a script or ELF interpreter is not a directory.\n");
        } else if ( err == EPERM ) {
            printf("The file system is mounted nosuid, the user is not the superuser, and the file has the set-user-ID or set-group-ID bit set.\n");
        } else if ( err == EPERM ) {
            printf("The process is being traced, the user is not the superuser and the file has the set-user-ID or set-group-ID bit set.\n");
        } else if ( err == ETXTBSY) { 
            printf("Executable was open for writing by one or more processes.\n");
        } else {
            printf("Unknown Error\n");
        }
}
