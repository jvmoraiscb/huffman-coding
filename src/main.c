#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/binaryTree.h"
#include "../include/list-binaryTree.h"
#include "../include/dictionary.h"

void start_encoder(char *file);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("ERRO!\n");
        return 1;
    }

    if (!strcmp(argv[1], "-encoder"))
    {
        start_encoder(argv[2]);
    }
    else if (!strcmp(argv[1], "-decoder"))
    {
        printf("decodificador\n");
    }
    else
    {
        printf("ERRO!\n");
        return 1;
    }
    /*
    bitmap *bm = bitmapInit(16);
    printf("size=%d bits\n", bitmapGetMaxSize(bm));
    bitmapAppendLeastSignificantBit(bm, 0);
    bitmapAppendLeastSignificantBit(bm, 1);
    bitmapAppendLeastSignificantBit(bm, 1);
    bitmapAppendLeastSignificantBit(bm, 0);
    bitmapAppendLeastSignificantBit(bm, 0);
    bitmapAppendLeastSignificantBit(bm, 0);
    bitmapAppendLeastSignificantBit(bm, 0);
    bitmapAppendLeastSignificantBit(bm, 1);

    bitmapAppendLeastSignificantBit(bm, 0);
    bitmapAppendLeastSignificantBit(bm, 1);
    bitmapAppendLeastSignificantBit(bm, 1);
    bitmapAppendLeastSignificantBit(bm, 0);
    bitmapAppendLeastSignificantBit(bm, 0);
    bitmapAppendLeastSignificantBit(bm, 0);
    bitmapAppendLeastSignificantBit(bm, 1);
    bitmapAppendLeastSignificantBit(bm, 0);

    printf("%0c\n", bitmapGetContents(bm)[0]);
    printf("%c\n", bitmapGetContents(bm)[1]);
    printf("length=%0d\n", bitmapGetLength(bm));

    int i;
    for (i = 0; i < bitmapGetLength(bm); i++)
    {
        printf("bit #%d = %0xh\n", i, bitmapGetBit(bm, i));
    }

    bitmapLibera(bm);
    */

    /*
    BinaryTree *a = Constructor_binaryTreeLeaf(1, 'a'), *b = Constructor_binaryTreeLeaf(2, 'b'), *c = Constructor_binaryTreeLeaf(3, 'c'), *d = Constructor_binaryTreeLeaf(4, 'd'), *e = Constructor_binaryTreeLeaf(5, 'e'), *f = Constructor_binaryTreeLeaf(6, 'f');

    List *list = constructor_list();
    list = insert_list(list, c);
    list = insert_list(list, e);
    list = insert_list(list, b);
    list = insert_list(list, f);
    list = insert_list(list, d);
    list = insert_list(list, a);

    print_list(list);
    printf("\n");

    list = remove_list(list, f);
    list = remove_list(list, c);
    list = remove_list(list, a);

    print_list(list);
    printf("\n");

    list = insert_list(list, f);
    list = insert_list(list, c);
    list = insert_list(list, a);

    ascendingOrder_list(list);
    print_list(list);
    printf("\n");

    destructor_list(list);
    Destructor_binaryTree(a);
    Destructor_binaryTree(b);
    Destructor_binaryTree(c);
    Destructor_binaryTree(d);
    Destructor_binaryTree(e);
    Destructor_binaryTree(f);
    */

    return 0;
}

static void addBinCharPad(char c, bitmap *bitmap)
{
    for (int i = 7; i >= 0; --i)
    {
        putchar((c & (1 << i)) ? '1' : '0');
    }
}

void start_encoder(char *file)
{
    int i, j;
    char fileType[10], fileName[100];

    char fileTemp[100];
    strcpy(fileTemp, file);
    char *pt;
    pt = strtok(fileTemp, ".");
    strcpy(fileName, pt);
    strcat(fileName, ".comp");
    pt = strtok(NULL, ".");
    strcpy(fileType, pt);

    // printf("%s\n%s\n", fileName, fileType);

    Dictionary *dictionary = constructor_dictionary(file, fileType);
    // printDictionary(dictionary);
    int size = getBitmapSize(dictionary) / 8;
    // printf("%d", size);
    FILE *file_target = fopen(fileName, "a");
    printChar(dictionary, file_target);
    fclose(file_target);
}
