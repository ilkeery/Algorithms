/*
    Yapılacaklar;
    Offline versiyon onlinedan kolay gözüküyor. İlk olarak offline tree yapılacak.
    input.txt file'dan veriler okunup saklanacak. İçerisinde key value olan- bizim durumumuzda
    key freq- bir map structı kullanılabilir. Bu structı içeren bir array tanımlarsak verileri
    key freq olarak tutabiliriz. [[key1, freq1], [key2,freq2]... ] buna benzer bir şey.
    Pythonda dictionary, C++ 'da map var fakat C'de bunlar yok biz kendimiz yapacağız.
    Verileri sakladıktan sonra frekanslarına göre büyükten küçüğe sıralayan bir algoritma kullanarak
    verileri sıralı bir şekilde başka bir yerde tutacağız. Bunu yapma sebebimiz en yüksek frekans root
    ondan sonraki gelenler de (frekans büyüklüğüne göre) key valuelarına göre sol çocuk ya da sağ çocuk
    olarak devam edecek. Algoritmayı ben böyle düşündüm. Sıralı array'de ilk gelen yani frekansı en büyük olan
    root bundan sonra gelenleri de 2li alıp karşılaştırarak sağ veya sol çocuk olarak dağıtırz.
    En sonda da Tree'nin Pre order traversal versiyonunu terminale yazdıracağız. Bunun algoritması her yerde var burası kolay kısım.
    Asıl yapmamız gereken Tree'yi construct eden algoritma olacak gibi.


*/

#include <stdio.h>
#include <stdlib.h>

struct node
{
    int key;
    int freq;
    struct node *left, *right;
};

/*

*/
struct node *newNode(int _key, int _freq)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->key = _key;
    temp->freq = _freq;
    temp->left = temp->right = NULL;
    return temp;
}

/*
Offline tree olduğu için böyle bir insertion olacak mı
emin değilim.
*/

// Insert a node
struct node *
insert(struct node *node, int key, int freq)
{
    // Return a new node if the tree is empty
    if (node == NULL)
        return newNode(key, freq);

    // Traverse to the right place and insert the node
    if (key < node->key)
        node->left = insert(node->left, key, freq);
    else
        node->right = insert(node->right, key, freq);

    return node;
}

// bubble sorting struct arrays
void bubbleSort(struct node a[], int array_size)
{

    struct temp1
    {
        int key;
        int freq;
    };
    struct temp1 temp1;
    int j, k;
    /*
    Buradaki for hiçbir zaman çalışmaz.
    j = 0 iken j> array_size-1 array size 5 olsa 0>5 çalışmaz!!
    Dolayısıyla içerdeki hiçbir kod da çalışmaz.
    */
    for (j = 0; j > array_size - 1; ++j)
    {
        for (k = 0; k < array_size - 1 - j; ++k)
        {

            if (a[k].freq > a[k + 1].freq)
            {
                temp1.freq = a[k + 1].freq;
                temp1.key = a[k + 1].key;
                a[k + 1].freq = a[k].freq;
                a[k + 1].key = a[k].key;
                a[k].freq = temp1.freq;
                a[k].key = temp1.key;
            }
        }
    }
}

int main()
{
    // 8 lenght struct array
    struct node keyFreq[8];
    // taking scanner input 8 times
    /*
    Offline versiyonda input.txt file'ı okuyup verileri alacağız.
    scanf ile terminalden tek tek veri alınmayacak.
    */

    int i, j;
    scanf("%d, %d\n", &i, &j);
    printf("sayi1: %d , sayi2: %d", i, j);
}