#include "../include/dictionary.h"
#include "../include/list-binaryTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_WORDS 256

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
    bitmap *sizeFile;
    bitmap *bitmap;
};

static void getText(int *ascii, char *file);
//static void printBinCharPad(char c);
static void addBinCharPad(char c, bitmap *bitmap);
static void fillDictionary(BinaryTree *tree, Dictionary *dictionary);
static bitmap *fillSizeBits(unsigned int sizeBits, unsigned int bits);
static bitmap *fillBitmap(Dictionary *dictionary);

Dictionary *constructor_dictionary(char *file)
{
    Dictionary *dictionary = malloc(sizeof(Dictionary));

    int ascii[MAX_WORDS] = {0};
    getText(ascii, file);

    List *list = constructor_list();
    int i, lenght = 0;
    unsigned int numberChars = 0;
    for (i = 0; i < MAX_WORDS; i++)
    {
        dictionary->words[i].bits = NULL;
        dictionary->words[i].sizeBits = NULL;

        if (ascii[i] > 0)
        {
            list = insert_list(list, Constructor_binaryTreeLeaf(ascii[i], i));
            lenght++;
            numberChars = numberChars + ascii[i];
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
    dictionary->sizeWords = fillSizeBits(lenght, 8);
    dictionary->sizeFile = fillSizeBits(numberChars, 32);
    dictionary->bitmap = fillBitmap(dictionary);
    return dictionary;
}

void print_dictionary(Dictionary *dictionary)
{
    /*
    int i, j;
    for (j = 0; j < 32; j++)
    {
        printf("%0x", bitmapGetBit(dictionary->sizeFile, j));
    }
    printf("\n\n");
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
            printf(" ");
            printBinCharPad(dictionary->words[i].c);
        }
    }
    */
   int i;
   for(i=0; i<bitmapGetLength(dictionary->bitmap); i++){
       printf("%0x", bitmapGetBit(dictionary->bitmap, i));
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
            bitmap *sizeBits = fillSizeBits(bitmapGetLength(getBits_binaryTree(tree)), 5);
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

static bitmap *fillSizeBits(unsigned int sizeBits, unsigned int bits)
{
    bitmap *new = bitmapInit(bits);

    int i;
    for(i=bits-1; i >= 0; i--)
    {
        if (sizeBits >= pow(2, i))
        {
            bitmapAppendLeastSignificantBit(new, 1);
            sizeBits = sizeBits - pow(2, i);
        }
        else
            bitmapAppendLeastSignificantBit(new, 0);
    }

    return new;
}

static bitmap *fillBitmap(Dictionary *dictionary)
{
    int i, j, count = 0;

    for (i = 0; i < MAX_WORDS; i++)
    {
        if (dictionary->words[i].bits != NULL)
        {
            count = count + 5 + bitmapGetLength(dictionary->words[i].bits) + 8;
        }
    }

    bitmap* bitmap = bitmapInit(32 + 8 + count);

    for (j = 0; j < 32; j++)
    {
        bitmapAppendLeastSignificantBit(bitmap, bitmapGetBit(dictionary->sizeFile, j));
    }
    for (j = 0; j < 8; j++)
    {
        bitmapAppendLeastSignificantBit(bitmap, bitmapGetBit(dictionary->sizeWords, j));
    }
    for (i = 0; i < MAX_WORDS; i++)
    {
        if (dictionary->words[i].bits != NULL)
        {
            for (j = 0; j < 5; j++)
            {
                bitmapAppendLeastSignificantBit(bitmap, bitmapGetBit(dictionary->words[i].sizeBits, j));
            }
            for (j = 0; j < bitmapGetLength(dictionary->words[i].bits); j++)
            {
                bitmapAppendLeastSignificantBit(bitmap, bitmapGetBit(dictionary->words[i].bits, j));
            }
            addBinCharPad(dictionary->words[i].c, bitmap);
        }
    }
    return bitmap;
}
/*
static void printBinCharPad(char c)
{
    for (int i = 7; i >= 0; --i)
    {
        putchar((c & (1 << i)) ? '1' : '0');
    }
    putchar('\n');
}
*/

static void addBinCharPad(char c, bitmap* bitmap)
{
    for (int i = 7; i >= 0; --i)
    {
        (c & (1 << i)) ? bitmapAppendLeastSignificantBit(bitmap, 1) : bitmapAppendLeastSignificantBit(bitmap, 0);
    }
}