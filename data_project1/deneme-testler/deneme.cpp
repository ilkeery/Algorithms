#include <iostream>
#include <stdio.h>
#include <stdlib.h>

// Create Node
struct Node
{
    int key;
    int freq;
    struct Node *left;
    struct Node *right;
    int height;
};

// Create a node
struct Node *newNode(int key)
{
    struct Node *node = (struct Node *)
        malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    node->freq = 0;
    return (node);
}

// Right rotate
// Function to perform left rotation
struct Node *leftRotate(Node *node)
{
    Node *y = node->right;
    node->right = y->left;
    y->left = node;
    return y;
}

// Function to perform right rotation
struct Node *rightRotate(Node *y)
{
    Node *x = y->left;
    y->left = x->right;
    x->right = y;
    return x;
}

// Insert node
struct Node *insertNode(struct Node *node, int key)
{
    // Find the correct position to insertNode the node and insertNode it
    if (node == NULL)
        return (newNode(key));

    if (key < node->key)
        node->left = insertNode(node->left, key);
    else if (key > node->key)
        node->right = insertNode(node->right, key);

    return node;
}
struct Node *rotate(struct Node *root)
{
    printf("rotate çağırıldı.\n");
    if (root == NULL)
    {
        printf("1 çalıştı\n");
        return root;
    }

    // if left child's frequency is larger than node, right rotate
    if (root->left != NULL && (root->left->freq > root->freq))
    {
        printf("2 çalıştı\n");
        rightRotate(root);
    }

    // if right child's frequency is larger than node, left rotate
    else if (root->right != NULL && (root->right->freq > root->freq))
    {
        printf("2 çalıştı\n");
        leftRotate(root);
    }

    return root;
}
struct Node *search(struct Node *root, int key)
{
    // Base Cases: root is null or key is present at root
    if (root == NULL || root->key == key)
    {
        if (root != NULL) // Check if the node is not NULL before incrementing freq
        {
            // incrementing frequency by one
            root->freq++;
            rotate(root);
        }
        return root;
    }
    // Key is greater than root's key
    if (root->key < key)
    {
        return search(root->right, key);
    }
    // Key is smaller than root's key
    return search(root->left, key);
}
// Function to perform search operation and update frequencies, and perform rotations if needed

Node *searchAndUpdate(Node *root, int key)
{
    if (root == NULL)
    {
        // Key not found, create a new node
        printf("Key not found");
        return root;
    }

    if (key == root->key)
    {
        // Update frequency
        root->freq++;
    }
    else if (key < root->key)
    {
        // Recursively search in the left subtree
        root->left = searchAndUpdate(root->left, key);
    }
    else
    {
        // Recursively search in the right subtree
        root->right = searchAndUpdate(root->right, key);
    }

    // Check if rotation is needed
    if (root->left != NULL && root->left->freq > root->freq)
    {
        printf("Left rotation called for %d\n", root->key);
        root = leftRotate(root);
    }
    else if (root->right != NULL && root->right->freq > root->freq)
    {
        printf("Right rotation called for %d\n", root->key);
        root = rightRotate(root);
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

int main()
{
    // Create the tree with root = NULL
    struct Node *root = NULL;

    // reading input.txt
    FILE *fptr;
    fptr = fopen("input2.txt", "r");
    int i = 0, _key, _freq;

    while (!feof(fptr))
    {
        fscanf(fptr, "%d", &_key);
        printf("Key %d: %d \n", i, _key);
        root = insertNode(root, _key);
        printf("Root: %d: %d \n", i, root->key);
        i++;
    }
    fclose(fptr);

    // Create the BS

    printf("Pre-order Traversal: \n");
    printPreOrder(root);

    // Searching in a BST
    if (searchAndUpdate(root, 7) == NULL)
        printf("%d Bulunamadı\n", 8);
    else
        printf("%d Var\n", 8);

    printf("After 8 searched , Pre-order Traversal: \n");
    printPreOrder(root);
    return 0;
}