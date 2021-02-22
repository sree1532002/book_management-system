#include "book_management.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define n 50
int m;
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
struct BookArray find_book_by_title (const char *title){
    char string[100];
    int i=0;
    struct BookArray BA;
    struct Book a[n];
    BA.array = a;
    FILE *file = fopen("bookstore.txt","a+");
    if(!file){
        fprintf(stderr, "\nError opening file\n"); 
    }
    struct Book book;
    while(1){ 
        if(!fread(&book, sizeof(struct Book), 1, file))
            break;   
        if(strcmp(book.title, title) == 0){
            strcpy(a[i].title,book.title);
            strcpy(a[i].authors,book.authors);
            a[i].year  = book.year;
            a[i].copies = book.copies;
            i++;
        }
    }
    BA.length = i;
    printf("%u\n",BA.length);
    printf("%s",BA.array[i-1].title);
   
   int ch;
   printf(" : \n1. BORROW\n2.DELETE\n#.NOthing\n");
   scanf("%d", &ch);
   if(ch==2)
    remove_book(BA.array[i-1]);
    else if(ch==1)
    borrow_book(BA.array[i-1]);

    return BA;
}
struct BookArray find_book_by_author (const char *author){
    char string[100];
    int i=0;
    struct BookArray BA;
    struct Book a[n];
    BA.array = a;
    FILE *file = fopen("bookstore.txt","a+");
    if(!file){
        fprintf(stderr, "\nError opening file\n"); 
    }
    struct Book book;
    while(1){ 
        if(!fread(&book, sizeof(struct Book), 1, file))
            break;   
        if(strcmp(book.authors, author) == 0){
            strcpy(a[i].title,book.title);
            strcpy(a[i].authors,book.authors);
            a[i].year  = book.year;
            a[i].copies = book.copies;
            i++;
        }
    }
    BA.length = i;
    printf("%u\n",BA.length);
    return BA;
}
struct BookArray find_book_by_year (unsigned int year){
    char string[100];
    int i=0;
    struct BookArray BA;
    struct Book a[n];
    BA.array = a;
    printf("%s",BA.array[i-1].authors);

    return BA;
}

int rewrite(struct BookArray books){
    FILE *file = fopen("tempbooks.txt","a+");
    if(!file){
        fprintf(stderr, "\nError opening file\n"); 
    }
    for(int i=0; i<books.length; i++){
        if(!fwrite(&books.array[i], sizeof(struct Book), 1, file)){
            fprintf(stderr, "\nError writing file\n");
            return 0;
        }
    }

    if(remove("bookstore.txt")==0){
        rename("tempbooks.txt", "bookstore.txt");
        return 1;
    }
    return 0;
}

//removes a book from the library
//returns 0 if the book could be successfully removed, or an error code otherwise.
int remove_book(struct Book book){
    struct BookArray books;
    struct Book elems[n], temp;
    int i = 0;
    books.array = elems;
    books.length = 0;
    FILE *file = fopen("bookstore.txt","a+");
    if(!file){
        fprintf(stderr, "\nError opening file\n"); 
    }

    while(1){ 
        //printf("\n");
        if(!fread(&temp, sizeof(struct Book), 1, file))
            break;   

        if((strcmp(book.title, temp.title) == 0) && (strcmp(book.authors, temp.authors) == 0) && (book.year == temp.year)){
            /*
            strcpy(a[i].title,book.title);
            strcpy(a[i].authors,book.authors);
            a[i].year  = book.year;
            a[i].copies = book.copies;
            i++;
            */
           continue;
        }else{
            strcpy(elems[i].title,temp.title);
            strcpy(elems[i].authors, temp.authors);
            elems[i].year  = temp.year;
            elems[i].copies = temp.copies;
            i++;
            books.length = i;
        }
    }
    fclose(file);
    if(rewrite(books)){
        return 1;
    }

    return 0;
}

int borrow_book(struct Book book){
    bool borrowed = false;
    struct BookArray books;
    struct Book elems[n], temp;
    int i = 0;
    books.array = elems;
    books.length = 0;
    FILE *file = fopen("bookstore.txt","a+");
    if(!file){
        fprintf(stderr, "\nError opening file\n"); 
    }

    while(1){ 
        //printf("\n");
        if(!fread(&temp, sizeof(struct Book), 1, file))
            break;   

        if((strcmp(book.title, temp.title) == 0) && (strcmp(book.authors, temp.authors) == 0) && (book.year == temp.year)){
            temp.copies-=1;
            borrowed = true;

        }
            strcpy(elems[i].title,temp.title);
            strcpy(elems[i].authors, temp.authors);
            elems[i].year  = temp.year;
            elems[i].copies = temp.copies;
            i++;
            books.length = i;
        
    }
    fclose(file);
    if(borrowed == true){
        printf("\n%s book has been borrowed.\n", book.title);
    }

    if(rewrite(books)){
        return 1;
    }

    return 0;
}

