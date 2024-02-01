#include <stdio.h>
#include <stdlib.h>

// Create Node
struct Node
{
    int key;
    int freq = 0;
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
    return (node);
}

// Right rotate
struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    return x;
}

// Left rotate
struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    return y;
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
// Searching the key and incrementing the frequence by one
struct Node *search(struct Node *root, int key)
{
    // Base Cases: root is null or key is present at root
    if (root == NULL || root->key == key)
        return root;

    // Key is greater than root's key
    if (root->key < key)
        return search(root->right, key);

    // Key is smaller than root's key
    return search(root->left, key);
    // incrementing frequence by one
    root->freq++;
    // if left childs frequency is larger than node, right rotate
    if (root->left->freq > root->freq)
        return rightRotate(root);
    // if right childs frequency is larger than node, left rotate
    else if (root->right->freq > root->freq)
        return leftRotate(root);
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

    printf("Pre-order Traversal: ");
    printPreOrder(root);

    search(root, 16);
    printf("After 16 searched , Pre-order Traversal: ");
    printPreOrder(root);
    return 0;
}