#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int key;
    int freq;
    struct Node *left;
    struct Node *right;
};
// Function Declarations
struct Node *newNode(int _key, int _freq);
struct Node *insertNode(struct Node *node, int key, int freq);
void bubbleSort(struct Node a[], int array_size);
int countLines(char file_name[]);
void printPreOrder(struct Node *root);

int main(int argc, char *argv[])
{
    /*
    READING input.txt
    */
    FILE *fptr;
    fptr = fopen(argv[1], "r");
    int i = 0, _key, _freq, lineCount;

    // count how many lines we have
    lineCount = countLines(argv[1]);
    // creating a struct array to store key-frequency values to sort them.
    struct Node keyFreq[lineCount];
    while (!feof(fptr))
    {
        fscanf(fptr, "%d %*c %d", &_key, &_freq);
        keyFreq[i].key = _key;
        keyFreq[i].freq = _freq;
        i++;
    }
    fclose(fptr);
    /*
    sort the keys respect corresponding frequency values.
    any sorting algorithm can be chosen. selection,bubble etc.
    */
    bubbleSort(keyFreq, lineCount);

    // Create the BST with input.txt
    struct Node *root = NULL;
    for (i = 0; i < lineCount; i++)
    {
        root = insertNode(root, keyFreq[i].key, keyFreq[i].freq);
    }

    printf("Pre-order Traversal: ");
    printPreOrder(root);
}

// create a new node
struct Node *newNode(int _key, int _freq)
{
    struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
    temp->key = _key;
    temp->freq = _freq;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

// Preorder traverse the tree
void printPreOrder(struct Node *root)
{
    if (root != NULL)
    {

        printf("%d, ", root->key);
        printPreOrder(root->left);
        printPreOrder(root->right);
    }
}

// Insert a new node
struct Node *insertNode(struct Node *node, int key, int freq)
{
    // If the tree is empty create a new node as root.
    if (node == NULL)
        return newNode(key, freq);

    // Traverse the tree to place the new node
    if (key < node->key)
        node->left = insertNode(node->left, key, freq);
    else
        node->right = insertNode(node->right, key, freq);

    return node;
}

// bubble sorting algorithm for struct arrays
void bubbleSort(struct Node a[], int array_size)
{

    struct Temp1
    {
        int key;
        int freq;
    };
    struct Temp1 temp1;
    int i, j;
    for (i = 0; i < array_size - 1; i++)
    {
        for (j = 0; j < array_size - 1 - i; j++)
        {

            if (a[j].freq < a[j + 1].freq)
            {
                temp1.freq = a[j + 1].freq;
                temp1.key = a[j + 1].key;
                a[j + 1].freq = a[j].freq;
                a[j + 1].key = a[j].key;
                a[j].freq = temp1.freq;
                a[j].key = temp1.key;
            }
        }
    }
}

// counting how many lines text has so we can create a correct sized array
int countLines(char file_name[])
{

    char c;
    int count = 0;
    FILE *fp;
    fp = fopen(file_name, "r");
    // fp is the file pointer
    for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n') // Increment count if this character is newline
            count = count + 1;

    fclose(fp);
    return count;
}