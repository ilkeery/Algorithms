#include <stdio.h>
#include <stdlib.h>
using namespace std;

struct node
{
    int key;
    int freq;
    struct node *left, *right;
};

int main()
{
    struct node keyFreq[8];
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

    for (i = 0; i < lineC; i++)
    {

        printf("%d. Key:%d, Frekans:%d \n", i + 1, keyFreq[i].key, keyFreq[i].freq);
    }
    fclose(fptr);
}
