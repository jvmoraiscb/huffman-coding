#include "../include/huffman-encoder.h"
#include "../include/list-binaryTree.h"
#include <stdio.h>
#include <stdlib.h>

static void getText(int *ascii, char *file);

void start(char *file)
{
    int ascii[128] = {0};
    getText(ascii, file);

    List *list = constructor_list();
    int i;
    for (i = 0; i < 128; i++)
    {
        if (ascii[i] > 0)
        {
            list = insert_list(list, Constructor_binaryTreeLeaf(ascii[i], i));
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