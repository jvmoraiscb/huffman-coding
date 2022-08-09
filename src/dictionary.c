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
static Word *create_word(char c, bitmap *bits);
static Dictionary *insert_word(Dictionary *dictionary, char c, bitmap *bits);

void start(char *file)
{
    int ascii[128] = {0};
    getText(ascii, file);

    List *list = constructor_list();
    int i, lenght = 0;
    for (i = 0; i < 128; i++)
    {
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

    Dictionary *dictionary;
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

static Word *create_word(char c, bitmap *bits)
{
    Word *newWord = malloc(sizeof(Word));
    newWord->c = c;
    newWord->bits = bits;

    return newWord;
}