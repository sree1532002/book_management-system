#include "book_management.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define n 50
int m;

typedef struct
{
    char name[26];
    char user_name[26];
    char email[26];
    char password[26];
    int borrows;
    char book[40];
} User;

int add_book(struct Book *book)
{
    printf("Enter the book title: ");
    scanf("%s", book->title);
    printf("Enter the list of authors as comma separated values: ");
    scanf("%s", book->authors);
    printf("Enter the year of publication: ");
    scanf("%u", &(book->year));
    printf("Enter the number of copies: ");
    scanf("%u", &(book->copies));
}
int store_books(FILE *file)
{
    struct Book book;
    /*
    char title[26], authors[26];
    book.title = title;
    book.authors=authors;
*/
    add_book(&book);

    /*
    sprintf((char *)&book.year, "%d", book.year);
    sprintf((char *)&book.copies, "%d", book.copies);
*/
    fprintf(file, "%s", book.title);
    fprintf(file, "\n");
    fprintf(file, "%s", book.authors);
    fprintf(file, "\n");
    fprintf(file, "%u", book.year);
    fprintf(file, "\n");
    fprintf(file, "%u", book.copies);
    fprintf(file, "\n");
}
/*
int stored_books(FILE *file)
{
    int i = 0, choice = 1;
    struct Book book[n];
    //struct BookArray BA;
    // BA.array = book;
    while (choice)
    {
        printf("Enter the book records(1 to continue , 0 to stop)\n");
        scanf("%d", &choice);
        if (choice == 1)
        {
            printf("Enter the book title: ");
            scanf("%s", &book[i].title);
            printf("Enter the list of authors as comma separated values: ");
            scanf("%s", &book[i].authors);
            printf("Enter the year of publication: ");
            scanf("%u", &book[i].year);
            printf("Enter the number of copies: ");
            scanf("%u", &book[i].copies);
            i++;
        }
    }
    m = i;
    
    for (i = 0; i < m; i++)
    {
        printf("%s", &book[i].title);
        printf("%s", &book[i].authors);
        printf("%u", book[i].year);
        printf("%u", book[i].copies);
    }
    
    for (i = 0; i < m; i++)
    {
        sprintf((char *)&book[i].year, "%d", book[i].year);
        sprintf((char *)&book[i].copies, "%d", book[i].copies);

        fprintf(file, (char *)&book[i].title);
        fprintf(file, "\t");
        fprintf(file, (char *)&book[i].authors);
        fprintf(file, "\t");
        fprintf(file, (char *)&book[i].year);
        fprintf(file, "\t");
        fprintf(file, (char *)&book[i].copies);
        fprintf(file, "\t\n");
    }
    return 0;
}
*/
int write_books(FILE *file)
{
    struct Book book;
    /*
    char title[26], authors[26];
    book.title = title;
    book.authors=authors;
*/
    add_book(&book);
    fwrite(&book, sizeof(struct Book), 1, file);
}

int load_books(FILE *file)
{
    char string[100];
    struct Book book;
    /*
    char title[100], authors[100];
    book.title = title;
    book.authors=authors;
    */
    while (1)
    {

        //fscanf(file,"%s%s%u%u",book.title,book.authors, &book.year, &book.copies);

        printf("\n");

        if (!fread(&book, sizeof(struct Book), 1, file))
            break;

        printf("Title: %s\nAuthor: %s\n", book.title, book.authors);
        printf("Year: %u\nCopies: %u\n", book.year, book.copies);
    }
}
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
        if (strcmp(book.title, title) == 0)
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
    /*
    printf("%u\n", BA.length);
    printf("%s", BA.array[i - 1].title);

    if(found==true){
    int ch;
    printf(" : \n1. BORROW\n2.DELETE\n#.NOthing\n");
    scanf("%d", &ch);
    if (ch == 2)
        remove_book(BA.array[i - 1]);
    else if (ch == 1)
        borrow_book(BA.array[i - 1]);
    }
    */
    return BA;
}
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
        if (strcmp(book.authors, author) == 0)
        {
            strcpy(a[i].title, book.title);
            strcpy(a[i].authors, book.authors);
            a[i].year = book.year;
            a[i].copies = book.copies;
            i++;
        }
    }
    BA.length = i;
    //printf("%u\n", BA.length);
    return BA;
}

struct BookArray find_book_by_year (unsigned int year){
    char string[100];
    int i = 0;
    struct BookArray BA;
    struct Book *a = (struct Book *) malloc(n* sizeof(struct Book));
    BA.array = a;
    //printf("%s",BA.array[i-1].authors);
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
    //printf("%u\n",BA.length);
    return BA;
}

int rewrite(struct BookArray books)
{
    FILE *file = fopen("tempbooks.txt", "a+");
    if (!file)
    {
        fprintf(stderr, "\nError opening file\n");
    }
    for (int i = 0; i < books.length; i++)
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

//removes a book from the library
//returns 0 if the book could be successfully removed, or an error code otherwise.
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
        //printf("\n");
        if (!fread(&temp, sizeof(struct Book), 1, file))
            break;

        if ((strcmp(book.title, temp.title) == 0) && (strcmp(book.authors, temp.authors) == 0) && (book.year == temp.year))
        {
            /*
            strcpy(a[i].title,book.title);
            strcpy(a[i].authors,book.authors);
            a[i].year  = book.year;
            a[i].copies = book.copies;
            i++;
            */
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
        //printf("\n");
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
        //printf("\n");
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
        printf("\n%s book has been returned.\n", book.title);
    }

    if (rewrite(books))
    {
        return 1;
    }

    return 0;
}

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
        printf("malloc error \n");
        return 0;
    }
    int i;
    

   
    for( i=0; i<usernos; i++){
        fread(&arr[i], sizeof(User), 1, fr);
         printf("%s, %s \n", arr[i].user_name, u.user_name);
        if(strcmp(arr[i].user_name, u.user_name)==0){
            //printf("\ndoing hssdfa\n");
            arr[i].borrows = u.borrows;
            strcpy(arr[i].book, u.book);
        }
        
    }
/*
    for(i=0; i<usernos; i++){
        printf("username = %s, borrows = %d, book = %s\n", arr[i].name, arr[i].borrows, arr[i].book);
    }
    */
    for(i=0; i<usernos; i++){
        fwrite(&arr[i], sizeof(User), 1, fw);
        //printf("%s, %s \n", arr[i].user_name, u.user_name);
        /*
         if(strcmp(arr[i].user_name, u.user_name)==0){
            printf("\n writing shit hssdfa\n");
         }
         */
        
    }
    
    fclose(fw);
    fclose(fr);

     if (remove("user.txt") == 0)
    {
        printf("removed\n");
        if(rename("tempusers.txt", "user.txt")==0){
            printf("\nRename successfully");
            return 1;
        }else{
            printf("\nnot renamed ");
            return 0;
        }
        
    }else{
        printf("not removed\n");
    }

    //printf("%d Usernos.\n", usernos);

    /*
    for ( i = 0; i < usernos; i++){
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
    */
   return 0;
}

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

         switch(ch){
            case 1: 
                printf("Enter the title: ");
                scanf("%s", string);
                books = find_book_by_title(string);
                break;

            case 2:
                printf("Enter the author: ");
                scanf("%s", string);
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
                printf("Book No. : %d\n", i+1);
                printf("Title: %s\nAuthor: %s\n", books.array[i].title, books.array[i].authors);
                printf("Year: %u\nCopies: %u\n", books.array[i].year, books.array[i].copies);
            }

            printf("Enter the book you want to borrow: ");
            scanf("%d", &bookno);

            if(books.array[bookno-1].copies>=1){
                if(borrow_book(books.array[bookno-1])){
                    u.borrows = 1;
                    strcpy(u.book, books.array[bookno-1].title);
                    if(rewrite_users(u)){
                        printf("\nUser details updated\n");
                        ch=0;
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
    return 0;
}

int return_the_book(User u){
    if(u.borrows == 0){
        printf("You have not borrowed any book to return. \n");
        return 0;
    }

    struct BookArray arr = find_book_by_title(u.book);
    printf("%d \n", arr.length);
    if(return_book(arr.array[0])){
        u.borrows=0;
        strcpy(u.book, "");
        if(rewrite_users(u)){
            printf("\nUser details updated\n");
            return 1;
        }
    }
    
    return 0;
}
