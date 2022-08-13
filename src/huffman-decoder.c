#include "../include/huffman-decoder.h"
#include "../include/bitmap.h"
#include "../include/binaryTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static bitmap *addBinCharPad(char c);
static int getIntFromBits(bitmap *bitmap, unsigned int start, unsigned int bits);
static void addBits(bitmap *map, bitmap *overflow, bitmap *c);

void huffman_decoder(char *file)
{
    int i, j;
    char fileType[10], fileName[100];

    char fileTemp[100];
    strcpy(fileTemp, file);
    char *pt;
    pt = strtok(fileTemp, ".");
    strcpy(fileName, pt);
    pt = strtok(NULL, ".");

    bitmap *map = bitmapInit(pow(2, 20)); // at least 1mb to read
    bitmap *overflow = bitmapInit(50);

    FILE *file_comp = fopen(file, "r");

    int sizeLeafs;
    char c;

    bitmap *dictionarySize = bitmapInit(16);
    for (i = 0; i < 2; i++)
    {
        fscanf(file_comp, "%c", &c);
        bitmap *c_bits = addBinCharPad(c);
        addBits(dictionarySize, NULL, c_bits);
        bitmapLibera(c_bits);
    }
    int dictionarySizeInt = getIntFromBits(dictionarySize, 0, 16);
    bitmap *dictionary = bitmapInit(dictionarySizeInt - 16);
    printf("--%d--\n", bitmapGetMaxSize(dictionary));
    for (i = 0; i < (dictionarySizeInt - 16) / 8; i++)
    {
        fscanf(file_comp, "%c", &c);
        bitmap *c_bits = addBinCharPad(c);
        addBits(dictionary, NULL, c_bits);
        bitmapLibera(c_bits);
    }

    BinaryTree *tree = Constructor_binaryTree(0, NULL, NULL);
    BinaryTree *tree_aux = tree;
    int treeSizeInt = getIntFromBits(dictionary, 0, 8);
    printf("%d\n", treeSizeInt);
    int position = 8;

    for (i = 0; i < treeSizeInt; i++)
    {
        position++;
        int sizeBits = getIntFromBits(dictionary, position, 5);
        position += 5;
        tree_aux = tree;
        for (j = 0; j < sizeBits; j++)
        {
            position++;
            if (bitmapGetBit(dictionary, position) == 1)
            {
                if (j == sizeBits - 1)
                {
                    // position++;
                    setRight_binaryTree(tree_aux, Constructor_binaryTreeLeaf(1, getIntFromBits(dictionary, position, 8)));
                    position += 8;
                }
                else
                {
                    setRight_binaryTree(tree_aux, Constructor_binaryTree(0, NULL, NULL));
                    tree_aux = getRight_binaryTree(tree_aux);
                }
            }
            else
            {
                if (j == sizeBits - 1)
                {
                    // position++;
                    setLeft_binaryTree(tree_aux, Constructor_binaryTreeLeaf(1, getIntFromBits(dictionary, position, 8)));
                    position += 8;
                }
                else
                {
                    setLeft_binaryTree(tree_aux, Constructor_binaryTree(0, NULL, NULL));
                    tree_aux = getLeft_binaryTree(tree_aux);
                }
            }
        }
        printf("%d\n", position);
    }
    print_binaryTree(tree);

    while (fscanf(file_comp, "%c", &c) == 1)
    {
        bitmap *c_bits = addBinCharPad(c);
        addBits(map, overflow, c_bits);
        bitmapLibera(c_bits);

        if (bitmapGetLength(map) == bitmapGetMaxSize(map))
        {
            bitmapLibera(map);
            map = bitmapInit(pow(2, 20));
            int i;
            for (i = 0; i < bitmapGetLength(overflow); i++)
            {
                bitmapAppendLeastSignificantBit(map, bitmapGetBit(overflow, i));
            }
            bitmapLibera(overflow);
            overflow = bitmapInit(50);
        }
    }
    fclose(file_comp);
}

static bitmap *addBinCharPad(char c)
{
    bitmap *bitmap = bitmapInit(8);
    for (int i = 7; i >= 0; --i)
    {
        (c & (1 << i)) ? bitmapAppendLeastSignificantBit(bitmap, 1) : bitmapAppendLeastSignificantBit(bitmap, 0);
    }
    return bitmap;
}

static void addBits(bitmap *map, bitmap *overflow, bitmap *c)
{
    int i;
    for (i = 0; i < bitmapGetLength(c); i++)
    {
        if (bitmapGetLength(map) < bitmapGetMaxSize(map))
            bitmapAppendLeastSignificantBit(map, bitmapGetBit(c, i));
        else
            bitmapAppendLeastSignificantBit(overflow, bitmapGetBit(c, i));
    }
}

static int getIntFromBits(bitmap *bitmap, unsigned int start, unsigned int bits)
{
    int count = 0, i = 0, j = 0;
    for (i = bits - 1; i >= 0; i--)
    {
        if (bitmapGetBit(bitmap, j + start) == 1)
        {
            count = count + pow(2, i);
        }
        j++;
    }
    return count;
}