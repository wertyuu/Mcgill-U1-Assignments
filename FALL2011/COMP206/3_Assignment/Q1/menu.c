int menu()
{
    char junk;
    char input[10];
    char forward[10];
    while(1) {
        printf("Please Select a command:\n1. Add a new user\n2. Delete an existing user\n3. Edit an existing user\n\
4. Authenticate as an existing user\n5. EXIT\n");
        printf("input: ");
        scanf("%s",input);
        if ( input[0] == '1') {
            char username_menu[20];
            char password_menu[20];
            char type_menu[20];
            while ( (junk = getchar()) != '\n' && junk != EOF );
            printf("Enter new username: ");
            scanf("%s",username_menu);
            while ( (junk = getchar()) != '\n' && junk != EOF );
            printf("Enter new password: ");
            scanf("%s",password_menu);
            while ( (junk = getchar()) != '\n' && junk != EOF );
            printf("Enter new type: ");
            scanf("%s",type_menu);
            add(username_menu, password_menu, type_menu);
            while ( (junk = getchar()) != EOF && junk != '\n' );
            printf("Do you want to continue?");
            scanf("%s",forward);
            if ( forward[0] == 'y' || forward[0] == 'Y' ) {
                continue;
            } else {
                return 0;
            }
        }
        if ( input[0] == '2') {
            char username_menu[20];
            while ( (junk = getchar()) != EOF && junk != '\n' );
            printf("Enter username to be deleted: ");
            scanf("%s",username_menu);
            delete(username_menu);
            while ( (junk = getchar()) != EOF && junk != '\n' );
            printf("Do you want to continue?");
            scanf("%s",forward);
            if ( forward[0] == 'y' || forward[0] == 'Y' ) {
                continue;
            } else {
                return 0;
            }
        }
        if ( input[0] == '3') {
            char username_menu[20];
            char password_menu[20];
            char type_menu[20];
            char username_2_menu[20];
            char password_2_menu[20];
            char type_2_menu[20];
            while ( (junk = getchar()) != EOF && junk != '\n' );
            printf("Enter record to be replaced.\n");
            printf("Enter username: ");
            scanf("%s",username_menu);
            printf("Enter password: ");
            while ( (junk = getchar()) != EOF && junk != '\n' );
            scanf("%s",password_menu);
            printf("Enter type: ");
            while ( (junk = getchar()) != EOF && junk != '\n' );
            scanf("%s",type_menu);
            printf("Enter new details to replace old ones\n");
            printf("Enter username: ");
            while ( (junk = getchar()) != EOF && junk != '\n' );
            scanf("%s",username_2_menu);
            printf("Enter password: ");
            while ( (junk = getchar()) != EOF && junk != '\n' );
            scanf("%s",password_2_menu);
            printf("Enter type:");
            while ( (junk = getchar()) != EOF && junk != '\n' );
            scanf("%s",type_2_menu);

            edit(username_menu, password_menu, type_menu, username_2_menu, password_2_menu, type_2_menu);
            while ( (junk = getchar()) != EOF && junk != '\n' );
            printf("Do you want to continue?");
            scanf("%s",forward);
            if ( forward[0] == 'y' || forward[0] == 'Y' ) {
                continue;
            } else {
                return 0;
            }
        }
        if ( input[0] == '4') {
            char username_menu[20];
            char password_menu[20];
            while ( (junk = getchar()) != EOF && junk != '\n' );
            printf("Enter username: ");
            scanf("%s", username_menu);
            while ( (junk = getchar()) != EOF && junk != '\n' );
            printf("Enter password: ");
            scanf("%s", password_menu);

            if ( verify(username_menu, password_menu) == 0 ) {
                printf("VALID\nusername and password verified.\n");
            } else {
                printf("INVALID\nusername and password did not match any of our records.\n");
            }
            while ( (junk = getchar()) != EOF && junk != '\n' );
            printf("Do you want to continue?");
            scanf("%s",forward);
            if ( forward[0] == 'y' || forward[0] == 'Y' ) {
                continue;
            } else {
                return 0;
            }
        }
        if ( input[0] == '5') {
                return 0;
        }
        puts("***********************************************");
        puts("* Please enter a number 1 to 5 to use program *");
        puts("***********************************************");
    }
}
