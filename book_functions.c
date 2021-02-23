#include "book_management.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define n 50
int m;

/*
    A structure to store user details.
*/
typedef struct
{
    char name[26];
    char user_name[26];
    char email[26];
    char password[26];
    int borrows;
    char book[40];
} User;

//A helping function to add the details of a book to the library
int add_book(struct Book *book)
{
    printf("Enter the book title: ");
    scanf("%[^\n]", book->title);
    getchar();
    printf("Enter the list of authors as comma separated values: ");
    scanf("%[^\n]", book->authors);
    getchar();
    printf("Enter the year of publication: ");
    scanf("%u", &(book->year));
    printf("Enter the number of copies: ");
    scanf("%u", &(book->copies));

    return 1;
}

//Function that writes the given book into the library using file stream
int store_books(FILE *file)
{
    struct Book book;
    if(add_book(&book))
        if(fwrite(&book, sizeof(struct Book), 1, file))
            return 1;

    return 0;
}

//Function that reads the list of books from the library using file stream

int load_books(FILE *file)
{
    char string[100];
    struct Book book;
    int i=0;
    while (1)
    {
        if (!fread(&book, sizeof(struct Book), 1, file))
            break;

        printf("\nBook No.: %d\nTitle: %s\nAuthor: %s\n",++i, book.title, book.authors);
        printf("Year: %u\nCopies: %u\n", book.year, book.copies);
    }
}

//A function that returns a list of books that contains the given string as substring in its title

struct BookArray find_book_by_title(const char *title)
{
    bool found = false;
    char string[100];
    int i = 0;
    struct BookArray BA;
    struct Book *a = (struct Book *) malloc(n* sizeof(struct Book));
    BA.array = a;
    FILE *file = fopen("bookstore.txt", "a+");
    if (!file)
    {
        fprintf(stderr, "\nError opening file\n");
    }
    struct Book book;
    while (1)
    {
        if (!fread(&book, sizeof(struct Book), 1, file))
            break;
        if (strstr(book.title, title) != NULL)
        {
            found = true;
            strcpy(a[i].title, book.title);
            strcpy(a[i].authors, book.authors);
            a[i].year = book.year;
            a[i].copies = book.copies;
            i++;
        }
    }
    BA.length = i;
    return BA;
}

//A function that returns a list of books that contains the given string as substring in its list of authors

struct BookArray find_book_by_author(const char *author)
{
    char string[100];
    int i = 0;
    struct BookArray BA;
    struct Book *a = (struct Book *) malloc(n* sizeof(struct Book));
    BA.array = a;
    FILE *file = fopen("bookstore.txt", "a+");
    if (!file)
    {
        fprintf(stderr, "\nError opening file\n");
    }
    struct Book book;
    while (1)
    {
        if (!fread(&book, sizeof(struct Book), 1, file))
            break;
        if (strstr(book.authors, author) != NULL)
        {
            strcpy(a[i].title, book.title);
            strcpy(a[i].authors, book.authors);
            a[i].year = book.year;
            a[i].copies = book.copies;
            i++;
        }
    }
    BA.length = i;
    return BA;
}

//A function that returns a list of books that were published in the given year

struct BookArray find_book_by_year (unsigned int year){
    char string[100];
    int i = 0;
    struct BookArray BA;
    struct Book *a = (struct Book *) malloc(n* sizeof(struct Book));
    BA.array = a;
     FILE *file = fopen("bookstore.txt","a+");
    if(!file){
        fprintf(stderr, "\nError opening file\n"); 
    }
    struct Book book;
    while(1){ 
        if(!fread(&book, sizeof(struct Book), 1, file))
            break;   
        if(year == book.year){
            strcpy(a[i].title,book.title);
            strcpy(a[i].authors,book.authors);
            a[i].year  = book.year;
            a[i].copies = book.copies;
            i++;
        }
    }
    BA.length = i;
    return BA;
}

// A function to rewrite the list of books iinto the file 

int rewrite(struct BookArray books)
{
    int i;
    FILE *file = fopen("tempbooks.txt", "a+");
    if (!file)
    {
        fprintf(stderr, "\nError opening file\n");
    }
    for ( i = 0; i < books.length; i++)
    {
        if (!fwrite(&books.array[i], sizeof(struct Book), 1, file))
        {
            fprintf(stderr, "\nError writing file\n");
            return 0;
        }
    }
    fclose(file);

    if (remove("bookstore.txt") == 0)
    {
        rename("tempbooks.txt", "bookstore.txt");
        return 1;
    }
    return 0;
}

// A function that removes a particular book from the library

int remove_book(struct Book book)
{
    struct BookArray books;
    struct Book elems[n], temp;
    int i = 0;
    books.array = elems;
    books.length = 0;
    FILE *file = fopen("bookstore.txt", "a+");
    if (!file)
    {
        fprintf(stderr, "\nError opening file\n");
    }

    while (1)
    {
        if (!fread(&temp, sizeof(struct Book), 1, file))
            break;

        if ((strcmp(book.title, temp.title) == 0) && (strcmp(book.authors, temp.authors) == 0) && (book.year == temp.year))
        {          
            continue;
        }
        else
        {
            strcpy(elems[i].title, temp.title);
            strcpy(elems[i].authors, temp.authors);
            elems[i].year = temp.year;
            elems[i].copies = temp.copies;
            i++;
            books.length = i;
        }
    }
    fclose(file);
    if (rewrite(books))
    {
        return 1;
    }

    return 0;
}


// A function that is used to borrow a given book and reflect the changes in the library 

int borrow_book(struct Book book)
{
    bool borrowed = false;
    struct BookArray books;
    struct Book elems[n], temp;
    int i = 0;
    books.array = elems;
    books.length = 0;
    FILE *file = fopen("bookstore.txt", "a+");
    if (!file)
    {
        fprintf(stderr, "\nError opening file\n");
        return 0;
    }

    while (1)
    {
        if (!fread(&temp, sizeof(struct Book), 1, file))
            break;

        if ((strcmp(book.title, temp.title) == 0) && (strcmp(book.authors, temp.authors) == 0) && (book.year == temp.year))
        {
            temp.copies -= 1;
            borrowed = true;
        }
        strcpy(elems[i].title, temp.title);
        strcpy(elems[i].authors, temp.authors);
        elems[i].year = temp.year;
        elems[i].copies = temp.copies;
        i++;
        books.length = i;
    }
    fclose(file);
    if (borrowed == true)
    {
        
    if (rewrite(books))
    {
        printf("\n%s book has been borrowed.\n", book.title);
        return 1;
    }
    }
    return 0;
}

// A function that is used to return a particular book and reflect the changes in the library

int return_book(struct Book book)
{
    bool returned = false;
    struct BookArray books;
    struct Book elems[n], temp;
    int i = 0;
    books.array = elems;
    books.length = 0;
    FILE *file = fopen("bookstore.txt", "a+");
    if (!file)
    {
        fprintf(stderr, "\nError opening file\n");
    }

    while (1)
    {
        if (!fread(&temp, sizeof(struct Book), 1, file))
            break;

        if ((strcmp(book.title, temp.title) == 0) && (strcmp(book.authors, temp.authors) == 0) && (book.year == temp.year))
        {
            temp.copies += 1;
            returned = true;
        }
        strcpy(elems[i].title, temp.title);
        strcpy(elems[i].authors, temp.authors);
        elems[i].year = temp.year;
        elems[i].copies = temp.copies;
        i++;
        books.length = i;
    }
    fclose(file);
    if (returned == true)
    {
        printf("%s book has been returned.\n", book.title);
    }

    if (rewrite(books))
    {
        return 1;
    }

    return 0;
}

// A function to update the details of the given user in the user's list

int rewrite_users(User u){
    FILE *fr = fopen("user.txt", "r");
     FILE *fw = fopen("tempusers.txt", "a+");
    if (!fw)
    {
        fprintf(stderr, "\nFile write error opening file\n");
        return 0;
    }
    if (!fr)
    {
        fprintf(stderr, "\nFile read error opening file\n");
        return 0;
    }

    fseek(fr, 0L, SEEK_END);
    long int final = ftell(fr);
    int usernos = final/sizeof(User);
    fclose(fr);

    fr=fopen("user.txt", "r");
    if (!fr)
    {
        fprintf(stderr, "\nFile read error opening file\n");
        return 0;
    }

    User *arr = (User *) malloc(usernos * sizeof(User));

    if(!arr){
        printf("Malloc error \n");
        return 0;
    }
    int i;
    

   
    for( i=0; i<usernos; i++){
        fread(&arr[i], sizeof(User), 1, fr);
        if(strcmp(arr[i].user_name, u.user_name)==0){
            arr[i].borrows = u.borrows;
            strcpy(arr[i].book, u.book);
        }
        
    }

    for(i=0; i<usernos; i++){
        fwrite(&arr[i], sizeof(User), 1, fw);
    }
    
    fclose(fw);
    fclose(fr);

     if (remove("user.txt") == 0)
    {
        if(rename("tempusers.txt", "user.txt")==0){
            
            return 1;
        }else{
           
            return 0;
        }
        
    }

   return 0;
}

// A function which allows the user to search for a particular book and borrow it

int borrow_a_book(User u){
    if(u.borrows==1){
        printf("You have already borrowed the book %s, return the book to borrow another.\n", u.book);
        return 0;
    }

    int ch=0, temp;
    char string[40];
    struct BookArray books;
    do{
        printf("Search the book:\n");
         printf("1. Find book by title\n");
         printf("2. Find book by author\n");
         printf("3. Find book by year\n");
         printf("0.Exit\n");
         printf("Enter your choice(1-3): ");

         scanf("%d", &ch);
         getchar();

         switch(ch){
            case 1: 
                printf("Enter the title: ");
                scanf("%[^\n]", string);
                getchar();
                books = find_book_by_title(string);
                break;

            case 2:
                printf("Enter the author: ");
                scanf("%[^\n]", string);
                getchar();
                books = find_book_by_author(string);
                break;

            case 3:
                 printf("Enter the year of publication: ");
                scanf("%d", &temp);
                books = find_book_by_year(temp);
                break;

            default:
                break;
         }
         if(ch==0)
            break;

        if(books.length==0){
            printf("No books are found.\n");
            break;
        }else{
            int i=0;
            int bookno;
            for(i=0; i<books.length; i++){
                printf("\nBook No. : %d\n", i+1);
                printf("Title: %s\nAuthor: %s\n", books.array[i].title, books.array[i].authors);
                printf("Year: %u\nCopies: %u\n", books.array[i].year, books.array[i].copies);
            }

            printf("\nEnter the book you want to borrow: ");
            scanf("%d", &bookno);

            if(bookno==0)
                break;
            if(books.array[bookno-1].copies>=1){
                if(borrow_book(books.array[bookno-1])){
                    u.borrows = 1;
                    strcpy(u.book, books.array[bookno-1].title);
                    if(rewrite_users(u)){
                        printf("User details updated\n");
                        ch=0;
                        free(books.array);
                        return 1;
            
                    }else{
                        printf("\nBorrow details not changed in user page");
                    }
                }
            }else{
                printf("\n Not enough copies to borrow from the library.\n");
            }
        }

    }while(ch==1 || ch==2 || ch==3);

    free(books.array);
    return 0;
}

// A function which allows the user to return the book that they had borrowed

int return_the_book(User u){
    if(u.borrows == 0){
        printf("You have not borrowed any book to return. \n");
        return 0;
    }

    struct BookArray arr = find_book_by_title(u.book);
    if(return_book(arr.array[0])){
        u.borrows=0;
        strcpy(u.book, "");
        if(rewrite_users(u)){
            printf("User details updated\n");
            return 1;
        }
    }
    
    return 0;
}


int remove_the_book(){
    FILE *file = fopen("bookstore.txt", "a+");
    if (!file)
                    {
                        fprintf(stderr, "\nError opening file\n");
                    }

    struct BookArray arr = find_book_by_title("");
    int i;
    for(i=0; i<arr.length; i++){
        printf("\nBook No: %d", i+1);
        printf("\nTitle: %s\nAuthor: %s\n", arr.array[i].title, arr.array[i].authors);
         printf("Year: %u\nCopies: %u\n", arr.array[i].year, arr.array[i].copies);
    }

fclose(file);
    printf("\nEnter the book no. to be removed: ");
    int ch;
    scanf("%d", &ch);
    getchar();

    if(ch==0)
        return 0;

    
    if(remove_book(arr.array[ch-1])){
       
        FILE *file = fopen("bookstore.txt", "a+");
        if (!file)
                    {
                        fprintf(stderr, "\nError opening file\n");
                    }

        load_books(file);
        fclose(file);
         printf("\nThe book '%s' has been removed.\n", arr.array[ch-1].title);
        return 1;
    }

    
    return 0;
}