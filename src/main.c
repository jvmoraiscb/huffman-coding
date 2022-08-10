#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/binaryTree.h"
#include "../include/list-binaryTree.h"
#include "../include/dictionary.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("ERRO!\n");
        return 1;
    }
    if (!strcmp(argv[1], "-encoder"))
    {
        Dictionary *dictionary = constructor_dictionary(argv[2]);
        print_dictionary(dictionary);
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