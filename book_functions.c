#include "book_management.h"
#include <stdio.h>
#include <string.h>
#define n 50
int m;
int add_book(struct Book *book){
    printf("Enter the book title: ");
    scanf("%s",book->title);
    printf("Enter the list of authors as comma separated values: ");
    scanf("%s", book->authors);
    printf("Enter the year of publication: ");
    scanf("%u", &(book->year));
    printf("Enter the number of copies: ");
    scanf("%u", &(book->copies));
}
int store_books(FILE *file){
    struct Book book;
    char title[26], authors[26];
    book.title = title;
    book.authors=authors;

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
int write_books(FILE *file){
    struct Book book;
    char title[26], authors[26];
    book.title = title;
    book.authors=authors;

    add_book(&book);
    fwrite (&book, sizeof(struct Book), 1, file); 
}

int load_books(FILE *file){
    char string[100];
    struct Book book;
    
    char title[100], authors[100];
    book.title = title;
    book.authors=authors;
    while(!feof(file)){
        
    fscanf(file,"%s%s%u%u",book.title,book.authors, &book.year, &book.copies);
    /*
   printf("\n");

   if(!fread(&book, sizeof(struct Book), 1, file))
        break;
        */
    printf("Title: %s\nAuthor: %s\n", book.title,book.authors);
    printf("Year: %u\nCopies: %u\n", book.year, book.copies);
    
    }
}
