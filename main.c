#include "book_management.h"
#include "book_functions.c"
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
#define USER_MAX 50
// This system can store up to number of users

typedef struct
{
    char name[26];
    char user_name[26];
    char email[26];
    char password[26];
} User;
// definition of the structure of a user storing

User list[USER_MAX];
// define a global array, type User, size is USER_MAX

char* fileuser_name = "user.txt";
// user.txt need to create a file in your application directory


// Log function
User login()
{
    char user_name[25];
    char password[10];
    User lg;
    printf("enter user_name:");
    scanf("%s",user_name);
    strcpy(lg.user_name , user_name);
    printf("enter password:");
    scanf("%s",password);
    strcpy(lg.password,password);
    return lg;
}

// write txt file, there is a row for each user
void writeToFile(User u)
{
    FILE *fw = fopen(fileuser_name,"a+");
    fprintf(fw,u.user_name);
    fprintf(fw,"\t");
    fprintf(fw,u.password);
    fprintf(fw,"\n");
}

// determine whether the user exists
int exist(User u)
{
    int i;
    for(i=0; i<USER_MAX; i++)
    {
        if(0==strcmp(list[i].user_name ,u.user_name) && 0==strcmp(list[i].password ,u.password))
        {
            return 1;
        }
    }
    return -1;
}

//registered user
void registerUser()
{
    char name[26];
    char email[26];
    char user_name[26];
    char password[26];
    User user;
    int i;
    int count=0,pcount=0,c1=0,c2=0;
    printf("Enter your name(max 25):");
    scanf("%s",name);
    if(strlen(name) > 25){
        printf("Invalid name\n");
        exit(0);
    }
    strcpy(user.name , name);

    printf("Enter your email id:");
    scanf("%s",email);
    for(i=0;i<strlen(email);i++){
        if(email[i] == '@'){
            count++;
        }
        if(email[i] == '.'){
            if(email[i+1] == 'c' && email[i+2] == 'o' && email[i+3] == 'm' && email[i+4] == '\0')
                count++;
        }
    }
    if(count != 2){
        printf("Invalid email id\n");
        exit(0);
    }
    strcpy(user.email , email);

    printf("Enter your user name(max 25):");
    scanf("%s",user_name);
    if(strlen(user_name) > 25){
        printf("Invalid user name\n");
        exit(0);
    }
    strcpy(user.user_name , user_name);

    // determine whether there has been a registered user
    for(i=0; i<USER_MAX; i++)
    {
        if(0==strcmp(list[i].user_name ,user_name))
        {
            printf("USER ALREADY EXIST");
            return;
        }
    }
    printf("Enter your password containing only alphanumeric characters with atleast one uppercase and atleast one special character(max 25):");
    scanf("%s",password);
    for(i=0;i<strlen(password);i++){
        if(isupper(password[i])){
            c1++;
        }
        if(!isalnum(password[i])){
            c2++;
        }
    }
    if(strlen(password) > 25){
        printf("Invalid password\n");
    }
    else{
        if(c1 < 1 || c2 < 1){
            printf("Enter a stronger password: ");
            scanf("%s",password);
        }
    }
    strcpy(user.password , password);
    writeToFile(user);
}

int menu()
{
    int choice;
    printf("1.login\n");
    printf("2.register\n");
    printf("#.exit\n");
    printf("3.Store\n");
    printf("enter your choice:");
    scanf("%d",&choice);
    return choice;
}




int main()
{
    User test[USER_MAX];
    FILE *fp = fopen(fileuser_name,"r");
    int i=0;
    User u;
    if(NULL == fp)
    {
        printf("FILE NOT FOUND");
        return -1;
    }
    for(i=0; i<USER_MAX; i++)
    {
        char uuser_name[10];
        char upassword[10];
        fscanf(fp,"%s%s",uuser_name,upassword);

        strcpy(list[i].user_name , uuser_name);
        strcpy(list[i].password , upassword);
    }

    int choice = menu();
    if(1 == choice)
    {
        u=login();
        if(1 == exist(u))
        {
            printf("Success");
        }
        else
        {
            printf("Wrong username or password/Please register before logging in");
        }

    }
    else if(2 == choice)
    {
        registerUser();
    }
    else if(3 == choice){
        FILE *file = fopen("bookstore.txt","a+");
    store_books(file);
    }
    else
    {
        return 0;
    }


}

