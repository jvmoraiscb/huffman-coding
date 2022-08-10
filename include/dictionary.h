#if !defined(DICTIONARY)
#define DICTIONARY

typedef struct dictionary Dictionary;

Dictionary *constructor_dictionary(char *file);
void print_dictionary(Dictionary *dictionary);

#endif // DICTIONARY
