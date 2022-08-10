#include "../include/dictionary.h"
#include "../include/list-binaryTree.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_WORDS 128

typedef struct word
{
    char c;
    bitmap *bits;
    bitmap *sizeBits;
} Word;

struct dictionary
{
    Word words[MAX_WORDS];
    bitmap *sizeWords;
};

static void getText(int *ascii, char *file);
static void fillDictionary(BinaryTree *tree, Dictionary *dictionary);
static bitmap *fillSizeBits(unsigned int sizeBits);
static bitmap *fillSizeWords(unsigned int sizeBits);

Dictionary *constructor_dictionary(char *file)
{
    Dictionary *dictionary = malloc(sizeof(Dictionary));

    int ascii[MAX_WORDS] = {0};
    getText(ascii, file);

    List *list = constructor_list();
    int i, lenght = 0;
    for (i = 0; i < MAX_WORDS; i++)
    {
        dictionary->words[i].bits = NULL;
        dictionary->words[i].sizeBits = NULL;

        if (ascii[i] > 0)
        {
            list = insert_list(list, Constructor_binaryTreeLeaf(ascii[i], i));
            lenght++;
        }
    }

    while (last_list(list) == 0)
    {
        ascendingOrder_list(list);

        BinaryTree *first = getTree_list(list);
        BinaryTree *second = getTree_list(getNext_list(list));

        BinaryTree *newTree = Constructor_binaryTree(getValue_binaryTree(first) + getValue_binaryTree(second), first, second);

        list = insert_list(list, newTree);
        list = remove_list(list, first);
        list = remove_list(list, second);
    }

    fillBits_binaryTree(getTree_list(list));
    fillDictionary(getTree_list(list), dictionary);
    dictionary->sizeWords = fillSizeWords(lenght);
    return dictionary;
}

void print_dictionary(Dictionary *dictionary)
{

    int i, j;
    for (j = 0; j < 8; j++)
    {
        printf("%0x", bitmapGetBit(dictionary->sizeWords, j));
    }
    printf("\n\n");
    for (i = 0; i < MAX_WORDS; i++)
    {
        if (dictionary->words[i].bits != NULL)
        {
            for (j = 0; j < 5; j++)
            {
                printf("%0x", bitmapGetBit(dictionary->words[i].sizeBits, j));
            }
            printf(" ");
            for (j = 0; j < bitmapGetLength(dictionary->words[i].bits); j++)
            {
                printf("%0x", bitmapGetBit(dictionary->words[i].bits, j));
            }
            printf(" '%c'\n", dictionary->words[i].c);
        }
    }
}

static void getText(int *ascii, char *file)
{
    FILE *text = fopen(file, "r");
    char c;
    while (fscanf(text, "%c", &c) == 1)
    {
        ascii[(int)c]++;
    }
    fclose(text);
}

static void fillDictionary(BinaryTree *tree, Dictionary *dictionary)
{
    if (tree != NULL)
    {
        if (getLeft_binaryTree(tree) == NULL && getRight_binaryTree(tree) == NULL)
        {
            bitmap *sizeBits = fillSizeBits(bitmapGetLength(getBits_binaryTree(tree)));
            dictionary->words[(int)getChar_binaryTree(tree)].sizeBits = sizeBits;
            dictionary->words[(int)getChar_binaryTree(tree)].c = getChar_binaryTree(tree);
            dictionary->words[(int)getChar_binaryTree(tree)].bits = getBits_binaryTree(tree);
        }
        if (getLeft_binaryTree(tree) != NULL)
        {
            fillDictionary(getLeft_binaryTree(tree), dictionary);
        }
        if (getRight_binaryTree(tree) != NULL)
        {
            fillDictionary(getRight_binaryTree(tree), dictionary);
        }
    }
}

static bitmap *fillSizeBits(unsigned int sizeBits)
{
    bitmap *new = bitmapInit(5);
    if (sizeBits >= 16)
    {
        bitmapAppendLeastSignificantBit(new, 1);
        sizeBits = sizeBits - 16;
    }
    else
        bitmapAppendLeastSignificantBit(new, 0);
    if (sizeBits >= 8)
    {
        bitmapAppendLeastSignificantBit(new, 1);
        sizeBits = sizeBits - 8;
    }
    else
        bitmapAppendLeastSignificantBit(new, 0);
    if (sizeBits >= 4)
    {
        bitmapAppendLeastSignificantBit(new, 1);
        sizeBits = sizeBits - 4;
    }
    else
        bitmapAppendLeastSignificantBit(new, 0);
    if (sizeBits >= 2)
    {
        bitmapAppendLeastSignificantBit(new, 1);
        sizeBits = sizeBits - 2;
    }
    else
        bitmapAppendLeastSignificantBit(new, 0);
    if (sizeBits >= 1)
    {
        bitmapAppendLeastSignificantBit(new, 1);
        sizeBits = sizeBits - 1;
    }
    else
        bitmapAppendLeastSignificantBit(new, 0);

    return new;
}

static bitmap *fillSizeWords(unsigned int sizeBits)
{
    bitmap *new = bitmapInit(8);
    if (sizeBits >= 128)
    {
        bitmapAppendLeastSignificantBit(new, 1);
        sizeBits = sizeBits - 128;
    }
    else
        bitmapAppendLeastSignificantBit(new, 0);
    if (sizeBits >= 64)
    {
        bitmapAppendLeastSignificantBit(new, 1);
        sizeBits = sizeBits - 64;
    }
    else
        bitmapAppendLeastSignificantBit(new, 0);
    if (sizeBits >= 32)
    {
        bitmapAppendLeastSignificantBit(new, 1);
        sizeBits = sizeBits - 32;
    }
    else
        bitmapAppendLeastSignificantBit(new, 0);
    if (sizeBits >= 16)
    {
        bitmapAppendLeastSignificantBit(new, 1);
        sizeBits = sizeBits - 16;
    }
    else
        bitmapAppendLeastSignificantBit(new, 0);
    if (sizeBits >= 8)
    {
        bitmapAppendLeastSignificantBit(new, 1);
        sizeBits = sizeBits - 8;
    }
    else
        bitmapAppendLeastSignificantBit(new, 0);
    if (sizeBits >= 4)
    {
        bitmapAppendLeastSignificantBit(new, 1);
        sizeBits = sizeBits - 4;
    }
    else
        bitmapAppendLeastSignificantBit(new, 0);
    if (sizeBits >= 2)
    {
        bitmapAppendLeastSignificantBit(new, 1);
        sizeBits = sizeBits - 2;
    }
    else
        bitmapAppendLeastSignificantBit(new, 0);
    if (sizeBits >= 1)
    {
        bitmapAppendLeastSignificantBit(new, 1);
        sizeBits = sizeBits - 1;
    }
    else
        bitmapAppendLeastSignificantBit(new, 0);

    return new;
}