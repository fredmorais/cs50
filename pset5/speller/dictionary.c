// Implements a dictionary's functionality

//Hash function from: https://cs50.stackexchange.com/questions/37209/pset5-speller-hash-function

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 65300;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{

    //Convert word into lowercase
    char tmp[strlen(word) + 1];
    strcpy(tmp, word);
    char *p = tmp;

    for ( ; *p; ++p) *p = tolower(*p);

    unsigned int i = hash(tmp);
    node *currentNode = table[i];

    while(currentNode != NULL)
    {
        if (strcmp(currentNode->word, tmp) == 0)
        {
            return true;
        }
        currentNode = currentNode->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash_value = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
         hash_value = (hash_value << 2) ^ word[i];
    }

    return (hash_value % N);
}

unsigned int words = 0;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //Open the file
    FILE *dictFile = fopen(dictionary, "r");

    if(!dictFile)
    {
        return false;
    }

    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    //Initiate variables
    char currentWord[LENGTH];

    while(fscanf(dictFile, "%s", currentWord) != EOF)
    {
        unsigned int i = hash(currentWord);

        //Create node
        node *currentNode = malloc(sizeof(struct node));
        strcpy(currentNode->word, currentWord);
        currentNode->next = NULL;

        if (table[i] != NULL)
        {
            currentNode->next = table[i];
        }

        table[i] = currentNode;

        words++;
    }

    return true;
    fclose(dictFile);

}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if(words)
    {
        return words;
    }

    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *currentNode = table[i];

        while (currentNode != NULL)
        {
            node *tmp = currentNode;
            currentNode = currentNode->next;
        }
    }
    return true;
}
