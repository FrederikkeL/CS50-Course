// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// size varible
int count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int index = hash(word);
    node *cursur = table[index];
    while (cursur != NULL)
    {
        if (strcasecmp(word, cursur->word) == 0)
        {
            return true;
        }
        else
        {
            cursur = cursur->next;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Improve this hash function

    return (toupper(word[0]) - 65);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO

    FILE *dic = fopen(dictionary, "r");
    if (dic == NULL)
    {
        return false;
    }
    char *word = malloc((LENGTH + 1) * sizeof(char));
    if (word == NULL)
    {
        free(word);
        return false;
    }
    // int scanResult = 0;
    while ((fscanf(dic, "%s", word)) != EOF)
    {

        // fscanf(dic, "%s", word);
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            free(n);
            return false;
        }
        strcpy(n->word, word);
        int index = hash(n->word);

        n->next = table[index];
        table[index] = n;
        count++;
    }
    free(word);
    fclose(dic);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (count > 0)
    {
        return count;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO

    for (int i = 0; i < N; i++)
    {
        node *pointer = table[i];
        while (pointer != NULL)
        {
            node *temp = pointer;
            pointer = pointer->next;
            free(temp);
        }
    }
    return true;
}
