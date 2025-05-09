typedef struct Node {
    void *data;
    int left_height;
    int right_height;
    struct Node *left;
    struct Node *right;
} Node;

typedef int (*CompareFunc)(void *a, void *b);
typedef void *(*NewData)();
typedef void *(*FreeFunc)(void *data);
typedef void (*PrintFunc)(void *data);

typedef struct BinaryTreeConfig {
    CompareFunc compare;
    FreeFunc free_data;
    PrintFunc print_data;
    NewData new_data;
} BinaryTreeConfig;

typedef struct BinaryTree {
    BinaryTreeConfig *config;
    Node *root;
} BinaryTree;


BinaryTreeConfig *binary_tree_config_create(CompareFunc compare, FreeFunc free_data, PrintFunc print_data, NewData new_data);
void binary_tree_destroy_config(BinaryTreeConfig *config);
BinaryTree *binary_tree_create(BinaryTreeConfig *config);
void binary_tree_clear(BinaryTree *tree);
void binary_tree_destroy(BinaryTree *tree);
void binary_tree_insert(BinaryTree *tree);
Node *binary_tree_search(BinaryTree *tree, void *data);
void binary_tree_print(BinaryTree *tree, int option);
Node *binary_tree_balance(Node *node);
Node *binary_tree_mirror(Node *node);