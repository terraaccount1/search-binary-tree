#include "data.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int generate_random = 1;

void insert_from_console(Book *book)
{
    if (book != NULL)
    {
        book->key = (char *)malloc(4);
        if (book->key == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }

        snprintf(book->key, 4, "%d", rand() % 1000);

        getchar(); // Clear the newline character from the input buffer
        printf("Enter book title: ");
        fgets(book->title, sizeof(book->title), stdin);
        book->title[strcspn(book->title, "\n")] = '\0'; // Remove newline character

        printf("Enter author name: ");
        fgets(book->author, sizeof(book->author), stdin);
        book->author[strcspn(book->author, "\n")] = '\0'; // Remove newline character

        printf("Enter year of publication: ");
        scanf("%u", &book->year);

        printf("Enter number of pages: ");
        scanf("%u", &book->pages);

        printf("Enter quantity: ");
        scanf("%u", &book->quantity);

        printf("Enter price: ");
        scanf("%lf", &book->price);
    }
}

void insert_random(Book *book)
{
    if (book != NULL)
    {
        book->key = (char *)malloc(4);
        if (book->key == NULL)
        {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }

        snprintf(book->key, 4, "%d", rand() % 1000);
        snprintf(book->title, STRING_SIZE, "Book %u", rand() % 1000);
        snprintf(book->author, STRING_SIZE, "Author %u", rand() % 1000);
        book->year = 1900 + (rand() % 123);           // Random year between 1900 and 2022
        book->pages = 50 + (rand() % 951);            // Random pages between 50 and 1000
        book->quantity = 1 + (rand() % 20);           // Random quantity between 1 and 20
        book->price = (double)(rand() % 10000) / 100; // Random price between $0.00 and $99.99
    }

    print_data(book);
}

void set_random_mode(int mode)
{
    generate_random = mode;
}

void insert_data(Book *book)
{
    if (generate_random)
        insert_random(book);
    else
        insert_from_console(book);
}

void *new_data()
{
    Book *book = (Book *)calloc(1, sizeof(Book));
    if (book == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    insert_data(book);
    return (void*)book;
}

void *new_data_key()
{
    Book *book = calloc(1, sizeof(Book));
    printf("Enter book key: ");
    getc(stdin);
    string key;
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';

    book->key = strdup(key);
    if (book->key == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        free(book);
        exit(EXIT_FAILURE);
    }

    return (void*)book;
}

void *free_data(void *data)
{
    if (data != NULL)
    {
        free(data);
    }
    return NULL;
}

void print_data(void *data)
{
    Book *book = (Book *)data;
    if (book != NULL)
    {
        printf("Key: %s\n", book->key);
        printf("Title: %s\n", book->title);
        printf("Author: %s\n", book->author);
        printf("Year: %u\n", book->year);
        printf("Pages: %u\n", book->pages);
        printf("Quantity: %u\n", book->quantity);
        printf("Price: %.2f\n", book->price);
    }
    else
    {
        printf("Book is NULL\n");
    }
}

int compare(void *a, void *b)
{
    Book *bookA = (Book *)a;
    Book *bookB = (Book *)b;
    return strcmp(bookA->key, bookB->key);
}

void save_data(void *data, FILE *file)
{
    Book *book = (Book *)data;
    if (book != NULL && file != NULL)
    {
        fprintf(file, "%s\n%s\n%s\n%u\n%u\n%u\n%.2f\n",
                book->key,
                book->title,
                book->author,
                book->year,
                book->pages,
                book->quantity,
                book->price);
    }
}