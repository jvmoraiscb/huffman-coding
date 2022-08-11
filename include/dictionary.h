#if !defined(DICTIONARY)
#define DICTIONARY

#include <stdio.h>

typedef struct dictionary Dictionary;

Dictionary *constructor_dictionary(char *file, char *type);
void printDictionary(Dictionary *dictionary);
int getBitmapSize(Dictionary *dictionary);
void printChar(Dictionary *dictionary, FILE *file);

#endif // DICTIONARY
