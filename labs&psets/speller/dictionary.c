// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#define min(a, b) ((a) < (b) ? (a) : (b))

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 300;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int num = hash(word);
    node *cursor = table[num];
    while (cursor != NULL)
    {
        char *dictionary = cursor->word;
        cursor = cursor->next;
        if (strcasecmp(dictionary, word) == 0)
        {
            return true;
        }
    }
    return false;
}

unsigned int hash(const char *word)
{
    unsigned int hash_value = 0;
    int num = min(3, strlen(word));

    for (int i = 0; i < num; i++)
    {
        hash_value = (hash_value << 2) ^ toupper(word[i]);
    }

    return hash_value % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    char word[LENGTH + 1];
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        printf("cannot open the dictionary");
        fclose(source);
        return false;
    }

    while (fscanf(source, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("cannot assign memory for a node");
            fclose(source);
            return false;
        }
        strcpy(n->word, word);
        int num = hash(n->word);

        n->next = table[num];
        table[num] = n;
    }
    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    int size = 0;

    for (int i = 0; i < N; i++)
    {
        node *ptr = table[i];
        while (ptr != NULL)
        {
            ptr = ptr->next;
            size++;
        }
    }
    return size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *ptr = table[i];
        while (ptr != NULL)
        {
            node *tmp = ptr->next;
            free(ptr);
            ptr = tmp;
        }
        table[i] = NULL;
        int is_success = 1;
        if (is_success != 1)
        {
            return false;
        }
    }
    return true;
}
