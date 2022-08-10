#include "../include/dictionary.h"
#include "../include/list-binaryTree.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct word
{
    char c;
    bitmap *bits;
} Word;

struct dictionary
{
    Word words[128];
};

static void getText(int *ascii, char *file);
static void fillDictionary(BinaryTree *tree, Dictionary *dictionary);

Dictionary *constructor_dictionary(char *file)
{
    Dictionary *dictionary = malloc(sizeof(Dictionary));

    int ascii[128] = {0};
    getText(ascii, file);

    List *list = constructor_list();
    int i, lenght = 0;
    for (i = 0; i < 128; i++)
    {
        dictionary->words[i].bits = NULL;

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

    return dictionary;
}

void print_dictionary(Dictionary *dictionary)
{

    int i, j;
    for (i = 0; i < 128; i++)
    {
        if (dictionary->words[i].bits != NULL)
        {
            for (j = 0; j < bitmapGetLength(dictionary->words[i].bits); j++)
            {
                printf("%0x", bitmapGetBit(dictionary->words[i].bits, j));
            }
            printf("%c\n");
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
            dictionary->words[getChar_binaryTree(tree)].c = getChar_binaryTree(tree);
            dictionary->words[getChar_binaryTree(tree)].bits = getBits_binaryTree(tree);
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