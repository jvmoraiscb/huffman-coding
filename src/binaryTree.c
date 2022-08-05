#include "../include/binaryTree.h"
#include <stdio.h>
#include <stdlib.h>

struct binaryTree {
    int value;
    char c;
    struct binaryTree *right;
    struct binaryTree *left;
};

BinaryTree *Constructor_binaryTreeLeaf(int value, char c){
    BinaryTree *new = malloc(sizeof(BinaryTree));
    new->value = value;
    new->c = c;
    new->right = NULL;
    new->left = NULL;
    return new;
}
BinaryTree *Destructor_binaryTree(BinaryTree *tree){
    if(tree != NULL){
        if(tree->left != NULL)
            Destructor_binaryTree(tree->left);
        if(tree->right != NULL)
            Destructor_binaryTree(tree->right);
        free(tree);
    }
    return NULL; 
}