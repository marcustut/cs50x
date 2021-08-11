// Implements a dictionary's functionality

#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Dictionary size
unsigned int dictSize = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Get the index by hashing
    int index = hash(word);

    node *head = table[index];
    node *temp = head;

    // Traverse the linked list from the head
    while (temp != NULL)
    {
        // Check for the condition
        if (strcasecmp(temp->word, word) == 0)
        {
            return true;
        }

        // Go to next node
        temp = temp->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Iterate from 'a' to 'z'
    for (int i = 97; i <= 122; i++)
    {
        // Check if the first alphabet in lowercase
        if (tolower(word[0]) == i)
        {
            return i - 97;
        }
    }

    return 0;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    // Read strings from file one at a time
    char *word = malloc(sizeof(char) * (LENGTH + 1));
    while (fscanf(dict, "%s", word) != EOF)
    {
        // Create a new node for each word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        // Copy the word from dictionary into the node
        strcpy(n->word, word);
        n->next = NULL;

        // Hash word to obtain a hash value
        int index = hash(n->word);

        // If the head is empty
        if (table[index] == NULL)
        {
            // Set the head to n
            table[index] = n;
        }
        else
        {
            node *head = table[index];

            // Point n to next node of head
            n->next = head->next;

            // Point head to n
            head->next = n;
        }

        // Increment the size
        dictSize++;
    }

    free(word);
    fclose(dict);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // Returns the dictionary size
    return dictSize;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Iterate through each buckets of the hash table
    for (int i = 0; i < N; i++)
    {
        // Create a cursor at i-th bucket
        node *cursor = table[i];

        // Traverse through the linked list at i-th
        while (cursor != NULL)
        {
            // Create a temp cursor
            node *tmp = cursor;

            // Points cursor to the next node
            cursor = cursor->next;

            // Free the current node
            free(tmp);
        }
    }

    return true;
}
