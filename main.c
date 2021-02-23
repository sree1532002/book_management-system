#include "book_management.h"
#include "book_functions.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#define USER_MAX 50


char fileuser_name[] = "user.txt";

//function that gets the username and password required for logging in

User login()
{
    char user_name[25];
    char password[10];
    User lg;
    printf("Enter Username: ");
    scanf("%[^\n]", user_name);
    getchar();
    strcpy(lg.user_name, user_name);
    printf("Enter Password: ");
    scanf("%[^\n]", password);
    getchar();
    strcpy(lg.password, password);

    return lg;
}

// function that writes the user-details into a file

void writeToFile(User u)
{

    FILE *fw = fopen(fileuser_name, "a+");
    fwrite(&u, sizeof(User), 1, fw);

    fclose(fw);
}

//Function that checks whether a particular user exists in the directory

int exist(User *u)
{
    int i;
    FILE *fp = fopen(fileuser_name, "r");
    User temp;
    while (1)
    {


        if (!fread(&temp, sizeof(User), 1, fp))
            break;

        if (0 == strcmp(temp.user_name, u->user_name) && 0 == strcmp(temp.password, u->password))
        {
            u->borrows = temp.borrows;
            strcpy(u->name, temp.name);
            strcpy(u->email, temp.email);
            strcpy(u->book, temp.book);
            return 1;
        }
    }
  
    return -1;
}

//Function to register a new user

void registerUser()
{
    char name[26];
    char email[26];
    char user_name[26];
    char password[26];
    User user;
    FILE *fp = fopen(fileuser_name, "r");
    User temp;
    int i;
    int count = 0, pcount = 0, c1 = 0, c2 = 0;
    printf("Enter your name(max 25): ");
    scanf("%[^\n]", name);
    getchar();
    if (strlen(name) > 25)
    {
        printf("Invalid name\n");
        exit(0);
    }
    strcpy(user.name, name);

    printf("Enter your email id: ");
    scanf("%[^\n]", email);
    getchar();
    for (i = 0; i < strlen(email); i++)
    {
        if (email[i] == '@')
        {
            count++;
        }
        if (email[i] == '.')
        {
                count++;
        }
    }
    if (count < 2)
    {
        printf("Invalid email id\n");
        exit(0);
    }
    strcpy(user.email, email);

    printf("Enter your user name (without spaces, max length 25): ");
    scanf("%[^\n]", user_name);
    getchar();
    if (strlen(user_name) > 25)
    {
        printf("Invalid user name\n");
        exit(0);
    }
    strcpy(user.user_name, user_name);

    while (1)
    {

        if (!fread(&temp, sizeof(User), 1, fp))
            break;

        if (0 == strcmp(temp.user_name, user.user_name))
        {
            printf("USER ALREADY EXIST\n");
            return;
        }
    }

   
    printf("Enter your password containing only alphanumeric characters with atleast one uppercase and atleast one special character(max 25): ");
    scanf("%[^\n]", password);
    getchar();
    for (i = 0; i < strlen(password); i++)
    {
        if (isupper(password[i]))
        {
            c1++;
        }
        if (!isalnum(password[i]))
        {
            c2++;
        }
    }
    if (strlen(password) > 25)
    {
        printf("Invalid password\n");
    }
    else
    {
        if (c1 < 1 || c2 < 1)
        {
            printf("Enter a stronger password: ");
            scanf("%[^\n]", password);
            getchar();
        }
    }
    strcpy(user.password, password);
    user.borrows=0;
    writeToFile(user);
}

//Driver Function

int main()
{

    FILE *fp = fopen(fileuser_name, "r");
    int i = 0;
    User u;
    if (NULL == fp)
    {
        printf("FILE NOT FOUND\n");
        return -1;
    }
    int choice = 0;
    printf("Welcome To The Library! \n");
    printf("1. Register(new user)\n");
    printf("2. User Login\n");
    printf("3. Admin Login\n");
    printf("0. To Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();
    if (choice == 1)
    {
        registerUser();
    }
    else if (choice == 2)
    {
        u = login();
        if (1 == exist(&u))
        {
            int c = 0;
            printf("Logged in Successfully\n");
            printf("\nHello %s\n", u.name);
            if(u.borrows==1){
                printf("You have borrowed the book: %s\n\n", u.book );
            }
            while (1)
            {
                printf("\n1. Borrow Books\n");
                printf("2. Return Books\n");
                printf("0. To Exit\n");
                printf("Enter your choice: ");
                scanf("%d", &c);
                getchar();
                printf("\n");
                if (c == 1)
                {
                    if(borrow_a_book(u)){
                        exist(&u);
                        continue;
                    }
                    
                }
                else if (c == 2)
                {
                    if(return_the_book(u))
                        exist(&u);
                        continue;
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            printf("Wrong username or password/Please register before logging in\n");
        }
    }
    else if (choice == 3)
    {
        int c = 0;
        char adus[40];
        char adp[40];
        printf("Enter Admin Username: ");
        scanf("%[^\n]", adus);
        getchar();
        printf("Enter Password: ");
        scanf("%[^\n]", adp);
        getchar();
        if ((strcmp(adus, "admin") == 0) && (strcmp(adp, "admin") == 0))
        {
            printf("Login Successful!\n");
            while (1)
            {
                printf("\n1. Add Books\n");
                printf("2. Remove Books\n");
                printf("3. Load All The Books\n");
                printf("0. To Exit \n");
                printf("Enter your choice: ");
                scanf("%d", &c);
                getchar();
                printf("\n");
                if (c == 1)
                {
                    FILE *file = fopen("bookstore.txt", "a+");
                    if (!file)
                    {
                        fprintf(stderr, "Error opening file\n");
                    }
                    if(store_books(file)){
                        printf("Book Added\n");
                    }
                    fclose(file);
                }else if(c==2){
                     
                    remove_the_book();
                    
                }
                else if (c == 3)
                {
                    FILE *file = fopen("bookstore.txt", "r");
                    if (!file)
                    {
                        fprintf(stderr, "\nError opening file\n");
                    }
                    load_books(file);
                    fclose(file);
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            printf("Invalid Admin Credentials\n");
        }
    }
    return 0;
}