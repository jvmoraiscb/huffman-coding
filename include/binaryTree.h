#if !defined(BINARY_TREE)
#define BINARY_TREE

#include "../include/bitmap.h"

typedef struct binaryTree BinaryTree;

BinaryTree *Constructor_binaryTreeLeaf(int value, char c);
BinaryTree *Constructor_binaryTree(int value, BinaryTree *left, BinaryTree *right);
BinaryTree *Destructor_binaryTree(BinaryTree *tree);
int getValue_binaryTree(BinaryTree *tree);
char getChar_binaryTree(BinaryTree *tree);
bitmap *getBits_binaryTree(BinaryTree *tree);
BinaryTree *getLeft_binaryTree(BinaryTree *tree);
BinaryTree *getRight_binaryTree(BinaryTree *tree);
void fillBits_binaryTree(BinaryTree *tree);

#endif // BINARY_TREE
