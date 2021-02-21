#include "book_management.h"
#include <stdio.h>
#include <string.h>
#define n 50
int m;
int store_books(FILE *file)
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