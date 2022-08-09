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

        List *first = list;
        List *second = getNext_list(list);

        BinaryTree *newTree = Constructor_binaryTree(getValue_binaryTree(getTree_list(first)) + getValue_binaryTree((getTree_list(second))), getTree_list(first), getTree_list(second));

        list = insert_list(list, newTree);
        list = remove_list(list, getTree_list(first));
        list = remove_list(list, getTree_list(second));
    }

    print_binaryTree(getTree_list(list));
    // printGraph_binaryTree(getTree_list(list));
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