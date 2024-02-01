#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

// Define Node structure for the binary search tree
struct Node
{
    int key;
    int freq;
    Node *left;
    Node *right;

    Node(int k) : key(k), freq(0), left(nullptr), right(nullptr) {}
};

// Function to perform left rotation
Node *leftRotate(Node *x)
{
    Node *y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

// Function to perform right rotation
Node *rightRotate(Node *y)
{
    Node *x = y->left;
    y->left = x->right;
    x->right = y;
    return x;
}

// Function to update the frequency and perform rotations if needed
Node *searchAndUpdate(Node *root, int key)
{
    if (root == nullptr)
    {
        return new Node(key);
    }

    if (key == root->key)
    {
        root->freq++;
    }
    else if (key < root->key)
    {
        root->left = searchAndUpdate(root->left, key);
    }
    else
    {
        root->right = searchAndUpdate(root->right, key);
    }

    // Check for rotation based on frequency
    if (root->left != nullptr && root->left->freq > root->freq)
    {
        root = rightRotate(root);
    }
    else if (root->right != nullptr && root->right->freq > root->freq)
    {
        root = leftRotate(root);
    }

    return root;
}

// Function to perform pre-order traversal and print the nodes
void preOrderTraversal(Node *root)
{
    if (root != nullptr)
    {
        cout << "(" << root->key << ", " << root->freq << ") ";
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}

int main()
{
    char search_char[13];
    printf("Enter a value to search (x to exit): ");
    scanf("%12s", search_char);
    int len_string = strlen(search_char);
    for (int i = 0; i < len_string; i++)
    {
        if (search_char[i] == ' ')
        {
            printf("SADJSAPODJSAKLDJAS");
            break;
        }
        bool b = isdigit(search_char[i]);
        printf("Bu bir sayıdır: %d", b);
    }
    int search_number = atoi(search_char);
    printf("\nSAYIMIZZZZZ: %d", search_number);
    // Free memory and exit
    return 0;
}
