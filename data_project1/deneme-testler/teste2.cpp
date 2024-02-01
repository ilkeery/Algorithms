#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int key;
    int frequency;
    struct Node *left;
    struct Node *right;
} Node;

Node *createNode(int key)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->key = key;
    newNode->frequency = 1; // Initialize frequency to 1 during node creation
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node *leftRotate(Node *x)
{
    Node *y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

Node *rightRotate(Node *y)
{
    Node *x = y->left;
    y->left = x->right;
    x->right = y;
    return x;
}

int height(Node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
}

int balanceFactor(Node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    return height(root->left) - height(root->right);
}

Node *searchAndUpdate(Node *root, int key)
{
    if (root == NULL)
    {
        return createNode(key);
    }

    if (key == root->key)
    {
        root->frequency++;
    }
    else if (key < root->key)
    {
        root->left = searchAndUpdate(root->left, key);
    }
    else
    {
        root->right = searchAndUpdate(root->right, key);
    }

    // Check for rotation based on balance factor
    int bf = balanceFactor(root);

    if (bf > 1 && key < root->left->key)
    {
        return rightRotate(root);
    }

    if (bf < -1 && key > root->right->key)
    {
        return leftRotate(root);
    }

    if (bf > 1 && key > root->left->key)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (bf < -1 && key < root->right->key)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void inorderTraversal(Node *root)
{
    if (root != NULL)
    {
        inorderTraversal(root->left);
        printf("Key: %d, Frequency: %d\n", root->key, root->frequency);
        inorderTraversal(root->right);
    }
}

void freeTree(Node *root)
{
    if (root != NULL)
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main()
{
    Node *root = NULL;
    int keys[] = {10, 5, 15, 3, 7, 12, 17};

    for (int i = 0; i < sizeof(keys) / sizeof(keys[0]); i++)
    {
        root = searchAndUpdate(root, keys[i]);
    }
    printf("Inorder Traversal:\n");
    inorderTraversal(root);

    root = searchAndUpdate(root, 15);
    root = searchAndUpdate(root, 15);
    root = searchAndUpdate(root, 10);
    root = searchAndUpdate(root, 10);
    printf("Inorder Traversal:\n");
    inorderTraversal(root);
    freeTree(root);

    return 0;
}
