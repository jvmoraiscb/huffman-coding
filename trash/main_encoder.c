#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/huffman-encoder.h"
#include "../include/huffman-decoder.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("ERRO!\n");
        return 1;
    }
    printf("%s\n", argv[1]);
    huffman_encoder(argv[1]);

    return 0;
}