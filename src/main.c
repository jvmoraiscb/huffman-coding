#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/binaryTree.h"
#include "../include/huffman-encoder.h"

int main(int argc, char *argv[]){
    if(argc != 3){
        printf("ERRO!\n");
        return 1;
    }
    if(!strcmp(argv[1], "-encoder")){
        printf("codificador\n");
        start(argv[2]);
    }
    else if(!strcmp(argv[1], "-decoder")){
        printf("decodificador\n");
    }
    else{
        printf("ERRO!\n");
        return 1;
    }

    return 0;
}