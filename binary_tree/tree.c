#include "tree.h"
#include <stdlib.h>
#include <stdio.h>

int compare_state = 0;

void set_compare_state(int state)
{
    compare_state = state;
}

BinaryTreeConfig *binary_tree_config_create(CompareFunc compare, FreeFunc free_data, PrintFunc print_data, NewData new_data)
{
    BinaryTreeConfig *config = malloc(sizeof(BinaryTreeConfig));
    if (!config)
    {
        return NULL;
    }
    config->compare = compare;
    config->free_data = free_data;
    config->print_data = print_data;
    config->new_data = new_data;
    return config;
}

void binary_tree_destroy_config(BinaryTreeConfig *config)
{
    if (config)
    {
        free(config);
    }
}

BinaryTree *binary_tree_create(BinaryTreeConfig *config)
{
    BinaryTree *tree = malloc(sizeof(BinaryTree));
    if (!tree)
    {
        return NULL;
    }
    tree->config = config;
    tree->root = NULL;
    return tree;
}

void node_destroy(Node *node, FreeFunc free_data)
{
    if (node)
    {
        node_destroy(node->left, free_data);
        node_destroy(node->right, free_data);
        node->data = free_data(node->data);
        free(node);
        node = NULL;
    }
}

void binary_tree_clear(BinaryTree *tree)
{
    if (tree)
    {
        node_destroy(tree->root, tree->config->free_data);
    }
}

void binary_tree_destroy(BinaryTree *tree)
{
    if (tree)
    {
        binary_tree_clear(tree);
        free(tree->config);
        free(tree);
        tree = NULL;
    }
}

Node *create_node(void *data)
{
    Node *node = calloc(1, sizeof(Node));
    if (!node)
    {
        return NULL;
    }
    node->data = data;
    return node;
}

Node *add_node(Node *root, void *data, CompareFunc compare)
{
    if (!root)
    {
        return create_node(data);
    }

    if (!compare_state)
    {
        if (compare(data, root->data) < 0)
        {
            root->left = add_node(root->left, data, compare);
            return root;
        }

        root->right = add_node(root->right, data, compare);
        return root;
    }

    else
    {
        if (compare(data, root->data) < 0)
        {
            root->right = add_node(root->right, data, compare);
            return root;
        }

        root->left = add_node(root->left, data, compare);
        return root;
    }
}

void binary_tree_insert(BinaryTree *tree)
{
    if (tree)
    {
        if (tree->root)
        {
            tree->root = add_node(tree->root, tree->config->new_data(), tree->config->compare);
        }
        else
        {
            tree->root = create_node(tree->config->new_data());
            if (!tree->root)
            {
                return;
            }
        }
    }
}

Node *binary_tree_utility_search(Node *node, void *data, CompareFunc compare)
{
    if (!node || !data)
    {
        return NULL;
    }

    if (compare(data, node->data) == 0)
    {
        return node;
    }

    if (compare(data, node->data) < 0 && compare_state == 0 || compare(data, node->data) >= 0 && compare_state)
    {
        return binary_tree_utility_search(node->left, data, compare);
    }
    else
    {
        return binary_tree_utility_search(node->right, data, compare);
    }

    return NULL;
}

Node *binary_tree_search(BinaryTree *tree, void *data)
{
    if (!tree || !tree->root)
    {
        return NULL;
    }

    return binary_tree_utility_search(tree->root, data, tree->config->compare);
}

void in_order_print(Node *node, PrintFunc print_data)
{
    if (node)
    {
        in_order_print(node->left, print_data);
        print_data(node->data);
        printf("Left: %p\n", node->left);
        printf("Right: %p\n\n", node->right);
        in_order_print(node->right, print_data);
    }
}

void pre_order_print(Node *node, PrintFunc print_data)
{
    if (node)
    {
        print_data(node->data);
        printf("Left: %p\n", node->left);
        printf("Right: %p\n\n", node->right);
        pre_order_print(node->left, print_data);
        pre_order_print(node->right, print_data);
    }
}

void post_order_print(Node *node, PrintFunc print_data)
{
    if (node)
    {
        post_order_print(node->left, print_data);
        post_order_print(node->right, print_data);
        print_data(node->data);
        printf("Left: %p\n", node->left);
        printf("Right: %p\n\n", node->right);
    }
}

void depth_order_print(Node *node, PrintFunc print_data)
{
    if (node)
    {
        print_data(node->data);
        printf("Left: %p\n", node->left);
        printf("Right: %p\n\n", node->right);
        depth_order_print(node->left, print_data);
        depth_order_print(node->right, print_data);
    }
}

void breadth_order_print(Node *node, PrintFunc print_data, int level)
{
    if (node == NULL)
    {
        return;
    }

    if (level == 0)
    {
        print_data(node->data);
        printf("Left: %p\n", node->left);
        printf("Right: %p\n\n", node->right);
    }
    else if (level > 0)
    {
        breadth_order_print(node->left, print_data, level - 1);
        breadth_order_print(node->right, print_data, level - 1);
    }
    return;
}

int binary_tree_height(Node *node)
{
    if (node == NULL)
    {
        return -1;
    }
    int left_height = binary_tree_height(node->left);
    int right_height = binary_tree_height(node->right);
    return (left_height > right_height ? left_height : right_height) + 1;
}

void binary_tree_print(BinaryTree *tree, int option)
{
    if (!tree || !tree->root)
    {
        return;
    }
    switch (option)
    {
    case 0:
        in_order_print(tree->root, tree->config->print_data);
        break;
    case 1:
        pre_order_print(tree->root, tree->config->print_data);
        break;
    case 2:
        post_order_print(tree->root, tree->config->print_data);
        break;
    case 3:
        depth_order_print(tree->root, tree->config->print_data);
        break;
    case 4:
    {
        int height = binary_tree_height(tree->root);
        for (int i = 0; i <= height; i++)
        {
            printf("Level %d:\n", i);
            breadth_order_print(tree->root, tree->config->print_data, i);
        }
        break;
    }
    default:
        break;
    }
}

Node *rotate_left(Node *node)
{
    Node *new_root = node->right;
    node->right = new_root->left;
    new_root->left = node;
    return new_root;
}

Node *rotate_right(Node *node)
{
    Node *new_root = node->left;
    node->left = new_root->right;
    new_root->right = node;
    return new_root;
}

Node *binary_tree_balance(Node *node)
{
    if (!node)
    {
        return NULL;
    }


    int left_height = binary_tree_height(node->left);
    int right_height = binary_tree_height(node->right);

    if (left_height - right_height > 1)
    {
        if (binary_tree_height(node->left->left) < binary_tree_height(node->left->right))
        {
            node->left = rotate_left(node->left);
        }
        node = rotate_right(node);
    }
    else if (right_height - left_height > 1)
    {
        if (binary_tree_height(node->right->right) < binary_tree_height(node->right->left))
        {
            node->right = rotate_right(node->right);
        }
        node = rotate_left(node);
    }

    return node;
}

Node *binary_tree_mirror(Node *node)
{
    if (!node)
    {
        return NULL;
    }

    node->left = binary_tree_mirror(node->left);
    node->right = binary_tree_mirror(node->right);

    Node *temp = node->left;
    node->left = node->right;
    node->right = temp;

    return node;
}