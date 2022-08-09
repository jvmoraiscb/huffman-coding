#include "../include/binaryTree.h"
#include <stdio.h>
#include <stdlib.h>

static void printTree(BinaryTree *tree);

struct binaryTree
{
    int value;
    char c;
    struct binaryTree *right;
    struct binaryTree *left;
};

BinaryTree *Constructor_binaryTreeLeaf(int value, char c)
{
    BinaryTree *new = malloc(sizeof(BinaryTree));
    new->value = value;
    new->c = c;
    new->right = NULL;
    new->left = NULL;
    return new;
}
BinaryTree *Constructor_binaryTree(int value, BinaryTree *left, BinaryTree *right)
{
    BinaryTree *new = malloc(sizeof(BinaryTree));
    new->value = value;
    new->c = 'c';
    new->right = right;
    new->left = left;
    return new;
}
BinaryTree *Destructor_binaryTree(BinaryTree *tree)
{
    if (tree != NULL)
    {
        if (tree->left != NULL)
            Destructor_binaryTree(tree->left);
        if (tree->right != NULL)
            Destructor_binaryTree(tree->right);
        free(tree);
    }
    return NULL;
}

// imprime as informações dos nós da árvore
void print_binaryTree(BinaryTree *tree)
{
    if (tree != NULL)
    {
        if (tree->right == NULL && tree->left == NULL)
            printf("%c\n", tree->c);

        if (tree->left != NULL)
            printf("0");
        print_binaryTree(tree->left);
        if (tree->right != NULL)
            printf("1");
        print_binaryTree(tree->right);
    }
}

void printGraph_binaryTree(BinaryTree *tree)
{
    printf("\nstrict graph{\n");
    printTree(tree);
    printf("}\n");
    return;
}

static void printTree(BinaryTree *tree)
{

    if (tree != NULL)
    {
        if (tree->left != NULL)
        {
            printf("%c -- %c\n", tree->c, tree->left->c);
        }
        if (tree->right != NULL)
        {
            printf("%c -- %c\n", tree->c, tree->right->c);
        }
        printTree(tree->left);
        printTree(tree->right);
    }
}

int getValue_binaryTree(BinaryTree *tree)
{
    return tree->value;
}

char getChar_binaryTree(BinaryTree *tree)
{
    return tree->c;
}

BinaryTree *getLeft_binaryTree(BinaryTree *tree)
{
    return tree->left;
}

BinaryTree *getRight_binaryTree(BinaryTree *tree)
{
    return tree->right;
}