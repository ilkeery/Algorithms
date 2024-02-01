#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

// Node Definition
struct Node
{
    int key;
    int freq;
    struct Node *left;
    struct Node *right;
};

// Function Declarations
struct Node *newNode(int key);
struct Node *leftRotate(struct Node *node);
struct Node *rightRotate(struct Node *node);
struct Node *insertNode(struct Node *node, int key);
struct Node *search(struct Node *root, int key);
void printPreOrder(struct Node *root);

int main(int argc, char *argv[])
{
    // root of the tree
    struct Node *root = NULL;

    // read input.txt
    FILE *file;
    file = fopen(argv[1], "r");
    // file = fopen("input.txt", "r");
    int i = 0, key, freq;

    while (!feof(file))
    {
        fscanf(file, "%d", &key);
        root = insertNode(root, key);
        i++;
    }
    fclose(file);

    /*TERMINAL APP */
    printf("Pre-order traversal of constructed tree : ");
    printPreOrder(root);
    printf("\n");
    int search_number;
    // max number has 13 digit in the BST.
    char search_char[13];
    bool not_a_number = false;
    do
    {
        printf("Enter a value to search (non-number to exit): ");
        scanf("%12s", search_char);
        int len_string = strlen(search_char);

        // Check if there is any non-number.
        int i;
        for (i = 0; i < len_string; i++)
        {
            if (!isdigit(search_char[i]))
            {
                not_a_number = true;
            }
        }

        if (!not_a_number)
        {
            // Data type convertion string to integer.
            int search_number = atoi(search_char);
            root = search(root, search_number);
            printf("Pre-order traversal of constructed tree : ");
            printPreOrder(root);
            printf("\n");
        }
        else
        {
            printf("You chose to exit the program.");
            break;
        }

    } while (true);

    return 0;
}

// Create a node
struct Node *newNode(int key)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->freq = 0;
    return (node);
}
// Function to perform left rotation
struct Node *leftRotate(struct Node *node)

{
    struct Node *left_node = node->right;
    node->right = left_node->left;
    left_node->left = node;
    return left_node;
}
// Function to perform right rotation
struct Node *rightRotate(struct Node *node)
{
    struct Node *right_node = node->left;
    node->left = right_node->right;
    right_node->right = node;
    return right_node;
}
// Insert node
struct Node *insertNode(struct Node *node, int key)
{
    if (node == NULL)
        return (newNode(key));

    if (key < node->key)
        node->left = insertNode(node->left, key);
    else if (key > node->key)
        node->right = insertNode(node->right, key);

    return node;
}
// Search Function
struct Node *search(struct Node *root, int key)

{
    if (root == NULL)
    {
        printf("This key is not in the tree.\n");
        return root;
    }

    if (key == root->key)
    {
        // increase the searched key's frequency by 1
        root->freq++;
    }
    else if (key < root->key)
    {
        // Recursively search in the left subtree
        root->left = search(root->left, key);
    }
    else
    {
        // Recursively search in the right subtree
        root->right = search(root->right, key);
    }

    /*
    Check left and right nodes if their frequencies are greater than their parent node.
    If necessary do right or left rotation.
    */
    if (root->left != NULL && root->left->freq > root->freq)
    {

        root = rightRotate(root);
    }
    else if (root->right != NULL && root->right->freq > root->freq)
    {

        root = leftRotate(root);
    }

    return root;
}
// Print the tree
void printPreOrder(struct Node *root)
{
    if (root != NULL)
    {
        printf("(%d, %d) ", root->key, root->freq);
        printPreOrder(root->left);
        printPreOrder(root->right);
    }
}