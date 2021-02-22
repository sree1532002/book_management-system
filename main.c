#include "book_management.h"
#include "book_functions.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define USER_MAX 50

typedef struct
{
    char name[26];
    char user_name[26];
    char email[26];
    char password[26];
} User;

User list[USER_MAX];

char fileuser_name[] = "user.txt";

User login()
{
    char user_name[25];
    char password[10];
    User lg;
    printf("enter user_name:");
    scanf("%s", user_name);
    strcpy(lg.user_name, user_name);
    printf("enter password:");
    scanf("%s", password);
    strcpy(lg.password, password);
    return lg;
}

void writeToFile(User u)
{

    FILE *fw = fopen(fileuser_name, "a+");
    fwrite(&u, sizeof(User), 1, fw);

    /* fprintf(fw, "%s", u.user_name);

    fprintf(fw, "\t");
    fprintf(fw, "%s", u.password);

    fprintf(fw, "\n");*/
    fclose(fw);
}

int exist(User u)
{
    int i;
    FILE *fp = fopen(fileuser_name, "r");
    User temp;
    while (1)
    {

        //fscanf(file,"%s%s%u%u",book.title,book.authors, &book.year, &book.copies);

        printf("\n");

        if (!fread(&temp, sizeof(User), 1, fp))
            break;

        if (0 == strcmp(temp.user_name, u.user_name) && 0 == strcmp(temp.password, u.password))
        {
            return 1;
        }
    }
    /*for (i = 0; i < USER_MAX; i++)
    {
        if (0 == strcmp(list[i].user_name, u.user_name) && 0 == strcmp(list[i].password, u.password))
        {
            return 1;
        }
    }*/
    return -1;
}

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
    printf("Enter your name(max 25):");
    scanf("%s", name);
    if (strlen(name) > 25)
    {
        printf("Invalid name\n");
        exit(0);
    }
    strcpy(user.name, name);

    printf("Enter your email id:");
    scanf("%s", email);
    for (i = 0; i < strlen(email); i++)
    {
        if (email[i] == '@')
        {
            count++;
        }
        if (email[i] == '.')
        {
            if (email[i + 1] == 'c' && email[i + 2] == 'o' && email[i + 3] == 'm' && email[i + 4] == '\0')
                count++;
        }
    }
    if (count != 2)
    {
        printf("Invalid email id\n");
        exit(0);
    }
    strcpy(user.email, email);

    printf("Enter your user name(max 25):");
    scanf("%s", user_name);
    if (strlen(user_name) > 25)
    {
        printf("Invalid user name\n");
        exit(0);
    }
    strcpy(user.user_name, user_name);

    while (1)
    {

        printf("\n");

        if (!fread(&temp, sizeof(User), 1, fp))
            break;

        if (0 == strcmp(temp.user_name, user.user_name))
        {
            printf("USER ALREADY EXIST");
            return;
        }
    }

    /*for (i = 0; i < USER_MAX; i++)
    {
        if (0 == strcmp(list[i].user_name, user_name))
        {
            printf("USER ALREADY EXIST");
            return;
        }
    }*/
    printf("Enter your password containing only alphanumeric characters with atleast one uppercase and atleast one special character(max 25):");
    scanf("%s", password);
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
            scanf("%s", password);
        }
    }
    strcpy(user.password, password);
    writeToFile(user);
}

int menu()
{
    int choice;
    printf("1. Login\n");
    printf("2. Register\n");
    printf("3. Store\n");
    printf("4. Load\n");
    printf("5. Find book by title\n");
    printf("6. Find book by author\n");
    printf("7. Find book by year\n");
    printf("#. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}

int main()
{
    User test[USER_MAX];
    FILE *fp = fopen(fileuser_name, "r");
    int i = 0;
    User u;
    if (NULL == fp)
    {
        printf("FILE NOT FOUND");
        return -1;
    }
    /*while (1)
    {

        //fscanf(file,"%s%s%u%u",book.title,book.authors, &book.year, &book.copies);

        printf("\n");

        if (!fread(&u, sizeof(User), 1, fp))
            break;

        printf("Username: %s\n", u.user_name);
        printf("Password: %s\n", u.password);
    }*/
    /*for (i = 0; i < USER_MAX; i++)
    {
        char uuser_name[10];
        char upassword[10];
        
        fscanf(fp, "%s%s", uuser_name, upassword);

        strcpy(list[i].user_name, uuser_name);
        strcpy(list[i].password, upassword);
    }*/

    int choice = menu();
    if (1 == choice)
    {
        u = login();
        if (1 == exist(u))
        {
            printf("Success");
        }
        else
        {
            printf("Wrong username or password/Please register before logging in");
        }
    }
    else if (2 == choice)
    {
        registerUser();
    }
    else if (3 == choice)
    {
        FILE *file = fopen("bookstore.txt", "a+");
        if (!file)
        {
            fprintf(stderr, "\nError opening file\n");
        }
        write_books(file);
        fclose(file);
    }
    else if (4 == choice)
    {
        FILE *file = fopen("bookstore.txt", "r");
        if (!file)
        {
            fprintf(stderr, "\nError opening file\n");
        }
        load_books(file);
        fclose(file);
    }
    else if (choice == 5)
    {
        char title[50];
        printf("Enter the title: ");
        scanf("%s", title);
        find_book_by_title(title);
    }
    else if (choice == 6)
    {
        char author[50];
        printf("Enter the author: ");
        scanf("%s", author);
        find_book_by_author(author);
    }
    else if (choice == 7)
    {
        int year;
        printf("Enter the year of publication: ");
        scanf("%d", &year);
        find_book_by_year(year);
    }
    else
    {
        fclose(fp);
    }
    return 0;
}
