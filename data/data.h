#include <stdio.h>
#define STRING_SIZE 32

typedef char string[STRING_SIZE];

typedef struct
{
    char* key;
    string title;
    string author;
    unsigned int year;
    unsigned int pages;
    unsigned int quantity;
    double price;
} Book;

void *new_data();
void *new_data_key();
void *free_data(void *data);
void print_data(void *data);
int compare(void *a, void *b);
void save_data(void *data, FILE *file);
void set_random_mode(int mode);