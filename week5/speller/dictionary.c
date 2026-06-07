// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

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

// Counter for number of words loaded
unsigned int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash the word to get the bucket index
    unsigned int index = hash(word);

    // Start at the beginning of the bucket
    node *cursor = table[index];

    // Traverse the linked list in this bucket
    while (cursor != NULL)
    {
        // Compare the word (case-insensitive)
        // strcasecmp returns 0 if words are equal (ignoring case)
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;  // Word found!
        }

        // Move to the next node in the linked list
        cursor = cursor->next;
    }

    // Word not found in this bucket
    return false;
}

unsigned int hash(const char *word)
{
    unsigned int hash_value = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        hash_value += tolower(word[i]);
    }
    return hash_value % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file for reading
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    word_count = 0;  // Reset word count

    // Clear the hash table
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Buffer to store each word as we read it
    char word[LENGTH + 1];

    // Read each word from the file, one per line
    while (fgets(word, sizeof(word), file) != NULL)
    {
        // Remove the newline character at the end
        word[strcspn(word, "\n")] = '\0';

        // Skip empty words (blank lines)
        if (strlen(word) == 0)
        {
            continue;  // Skip to next iteration of while loop
        }

        // Create a new node for this word
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;  // If malloc fails, return false
        }

        // Copy the word into the node
        strcpy(new_node->word, word);

        // Hash the word to get the bucket index
        unsigned int index = hash(word);

        // Insert the node at the START of the bucket
        new_node->next = table[index];
        table[index] = new_node;

        word_count++;
    }

    // Close the file
    fclose(file);

    return true;  // Success!
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Go through each bucket in the hash table
    for (int i = 0; i < N; i++)
    {
        // Start at the beginning of this bucket
        node *cursor = table[i];

        // Traverse the linked list in this bucket
        while (cursor != NULL)
        {
            // Save the next node BEFORE freeing
            node *temp = cursor->next;

            // Free the current node
            free(cursor);

            // Move to the next node
            cursor = temp;
        }
    }

    return true;
}
