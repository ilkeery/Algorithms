#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "dictionary.h"
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#define N 26
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
//const unsigned int N = 26;

// Hash table
node *table[N];

//Count keys
unsigned int count = 0;


// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *fptr;

    // Open a file in read mode
    fptr = fopen(dictionary, "r");

    // Store the content of the file
    char word[LENGTH];

    // If the file exist
    if(fptr != NULL)
    {

        // Read the content and print it
        while((fscanf(fptr, "%s", word)) != EOF)
        {
            count++;
            unsigned int hash_key = hash(word);
            if(table[hash_key] == NULL)
            {
                table[hash_key] = (node *) malloc(sizeof(node));
                strcpy(table[hash_key]->word, word);
                table[hash_key]->next = NULL;

            }
            else
            {
                node *new_node = (node *) malloc(sizeof(node));
                new_node->next = table[hash_key]->next;
                table[hash_key]->next = new_node;
                strcpy(new_node->word, word);
            }
        }
        // Close the file
        fclose(fptr);
        return true;

    // If the file does not exist
    }
    else
    {
    printf("Not able to open the file.");
    return false;
    }

}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int hash_key = hash(word);
    node *head = table[hash_key];
    while(head != NULL)
    {
        if(strcasecmp(head->word, word) == 0)
        {
            return true;
        }
        head = head->next;
    }
    return false;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO


    for(int i = 0; i < N; i++)
    {
        node *current = table[i];
        while(current != NULL)
        {
            node *nextnode = current->next;
            free(current);
            current = nextnode;
        }

    }

    return true;
}


