#include <stdio.h>
#include <stdlib.h>

static void getText(int *ascii, char *directory);

void start(char* directory){
    int ascii[128] = {0};
    getText(ascii, directory);

    int i = 0;
    for(int i = 0; i < 128; i++){
        if(ascii[i] > 0)
            printf("%c ", i);
    }
}

static void getText(int *ascii, char *directory){
    FILE *text = fopen(directory, "r");
    char c;
    while(fscanf(text, "%c", &c) == 1){
        ascii[(int)c]++;
    }
    fclose(text);
}