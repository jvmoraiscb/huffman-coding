#if !defined(BINARY_TREE)
#define BINARY_TREE

typedef struct binaryTree BinaryTree;

BinaryTree *Constructor_binaryTreeLeaf(int value, char c);
BinaryTree *Destructor_binaryTree(BinaryTree *tree);

#endif // BINARY_TREE
