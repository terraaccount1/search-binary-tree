#include "app.h"
#include "binary_tree/tree.h"
#include "data/data.h"
#include "print/color_print.h"
#include <stdlib.h>
#include <stdio.h>


void menu();
void menu_option(BinaryTree *, int);
void clear_console();
void start_app()
{
    BinaryTreeConfig *config = binary_tree_config_create(compare, free_data, print_data, new_data);
    BinaryTree *tree = binary_tree_create(config);
    set_random_mode(1);
    unsigned int option = 0;
    do
    {
        clear_console();
        menu();
        set_print(STYLE_BRIGHT, COLOR_RED);
        printf("Select option: ");
        scanf("%u", &option);
        reset_print();
        if (option == 0)
        {
            break;
        }
        clear_console();
        set_print(STYLE_BRIGHT, COLOR_YELLOW);
        menu_option(tree, option);

        getc(stdin);
        getc(stdin);
    } while (option != 0);

    binary_tree_destroy(tree);
}

void menu()
{
    set_print(STYLE_BRIGHT, COLOR_YELLOW);
    printf("Menu\n");
    printf("1. \tRead data\n");
    printf("2. \tPrint data\n");
    printf("3. \tSearch data\n");
    printf("4. \tInorder print\n");
    printf("5. \tPreorder print\n");
    printf("6. \tPostorder print\n");
    printf("7. \tDepth order print\n");
    printf("8. \tBreadth order print\n");
    printf("9. \tBalance tree\n");
    printf("10. \tMirror tree\n");
    printf("11. \tRemove data\n");
    printf("12. \tClear tree\n");
    printf("0. \tExit\n");
    reset_print();
}

void read_data(BinaryTree *);

void menu_option(BinaryTree *tree, int option)
{
    switch (option)
    {
    case 1:
        int n = 0;
        printf("Enter the number of data to insert: ");
        scanf("%d", &n);
        if (n <= 0)
        {
            printf("Invalid number\n");
            break;
        }

        for (int i = 0; i < n; i++)
        {
            read_data(tree);
            printf("\n");
        }
        break;

    case 2:
        set_print(STYLE_BRIGHT, COLOR_MAGENTA);
        binary_tree_print(tree, 0);
        reset_print();
        break;

    case 3:
        void *data = new_data_key();
        printf("Searching data...\n");
        Node *result = binary_tree_search(tree, data);
        
        if (result == NULL)
        {
            set_print(STYLE_BRIGHT, COLOR_RED);
            printf("Data not found\n");
            reset_print();
            break;
        }

        set_print(STYLE_BRIGHT, COLOR_GREEN);
        printf("Data found\n\n");
        print_data(result->data);
        reset_print();
        break;

    case 4:
        set_print(STYLE_BRIGHT, COLOR_MAGENTA);
        binary_tree_print(tree, 0);
        reset_print();
        break;

    case 5:
        set_print(STYLE_BRIGHT, COLOR_MAGENTA);
        binary_tree_print(tree, 1);
        reset_print();
        break;

    case 6:
        set_print(STYLE_BRIGHT, COLOR_MAGENTA);
        binary_tree_print(tree, 2);
        reset_print();
        break;

    case 7:
        set_print(STYLE_BRIGHT, COLOR_MAGENTA);
        binary_tree_print(tree, 3);
        reset_print();
        break;

    case 8:
        set_print(STYLE_BRIGHT, COLOR_MAGENTA);
        binary_tree_print(tree, 4);
        reset_print();
        break;

    case 9:
        set_print(STYLE_BRIGHT, COLOR_MAGENTA);
        printf("Balance tree\n");
        if(tree) {
            tree->root = binary_tree_balance(tree->root);
        }
        reset_print();
        break;

    case 10:
        set_print(STYLE_BRIGHT, COLOR_MAGENTA);
        printf("Mirror tree\n");
        if (tree)
        {
            tree->root = binary_tree_mirror(tree->root);
        }
        reset_print();
        break;

    case 11:
        set_print(STYLE_BRIGHT, COLOR_MAGENTA);
        printf("Remove data\n");
        binary_tree_clear(tree);
        tree->root = NULL;
        printf("Data removed\n");
        reset_print();
        break;

    case 12:
        set_print(STYLE_BRIGHT, COLOR_MAGENTA);
        printf("Clear tree\n");
        binary_tree_destroy(tree);
        reset_print();
        exit(0);
        break;

    default:
        printf("Invalid option\n");
    }
}

void read_data(BinaryTree *tree)
{
    set_print(STYLE_BRIGHT, COLOR_GREEN);
    
    binary_tree_insert(tree);
    reset_print();
}

void clear_console()
{
    system("cls||clear");
}