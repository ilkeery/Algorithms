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

    struct Node *rotate(struct Node * root)
    {

        // if left childs frequency is larger than node, right rotate
        if (root->left->freq > root->freq)
            return rightRotate(root);
        // if right childs frequency is larger than node, left rotate
        else if (root->right->freq > root->freq)
            return leftRotate(root);
    }
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
    root = rotate(root);
}

// Print the tree
void printPreOrder(struct Node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->key);
        printPreOrder(root->left);
        printPreOrder(root->right);
    }
}

int main()
{
    // reading input.txt
    FILE *fptr;
    fptr = fopen("input.txt", "r");
    int i = 0, _key, _freq;

    while (!feof(fptr))
    {
        fscanf(fptr, "%d %*c %d", &_key, &_freq);
        keyFreq[i].key = _key;
        keyFreq[i].freq = _freq;
        i++;
    }
    fclose(fptr);

    printf("Before Bubble Sort \n");

    bubbleSort(keyFreq, lineCount);
    printf("After Bubble Sort \n");
    for (i = 0; i < lineCount; i++)
    {

        printf("%d. Key:%d, Frekans:%d \n", i + 1, keyFreq[i].key, keyFreq[i].freq);
    }

    struct node *root = NULL;

    // Create the BST
    for (i = 0; i < lineCount; i++)
    {

        root = insert(root, keyFreq[i].key, keyFreq[i].freq);
    }

    printf("Pre-order Traversal: ");
    preorder(root);
}