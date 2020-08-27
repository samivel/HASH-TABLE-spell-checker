// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"

// Defines a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;



//Make an array of nodes the size of hashtable
node *hashtable[HASHTABLESIZE];

// global variable for count of of dic words
unsigned int wordCount = 0;


bool isloaded = false;




// Hash function courtesy of reddit user https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/cf9nlkn
int hashThis(char *input)
{
    unsigned int hash = 0;
    for (int i = 0, n = strlen(input); i < n; i++)
    {
        hash = (hash << 2) ^ input[i];
    }
    return hash % HASHTABLESIZE;
}




// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Make an array to copy the word to
    int length = strlen(word);
    char copyOfWord[length + 1];

    // Make it lower
    for (int i = 0; i < length; i++)
    {
        copyOfWord[i] = tolower(word[i]);
    }
    copyOfWord[length] = '\0';

    //Hash the word

    int hashed = hashThis(copyOfWord);

    node *checker = hashtable[hashed];

    while (checker != NULL)
    {
        if (strcmp(checker->word, copyOfWord) == 0)
        {
            return true;
        }
        else
        {
            checker = checker->next;
        }
    }
    return false;
}



// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Opens the dictionary to a pointer called file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Unable to open dictionalry.\n");
        return false;
    }
    // Reads each word from file until the end, assigns words to word

    while (true)
    {
        //Make space for each word
        node *tmp = malloc(sizeof(node));
        if (tmp == NULL)
        {
            printf("Could not find memory for new node\n");
            return false;
        }

        // Assign word from dic to tmp

        fscanf(file, "%s", tmp->word);
        tmp->next = NULL;

        // Checks for end of file
        if (feof(file))
        {
            free(tmp);
            break;
        }

        wordCount++;

        int hash = hashThis(tmp->word);
        node *head = hashtable[hash];

        // If bucket is empty, insert as first node
        if (head == NULL)
        {
            hashtable[hash] = tmp;
        }

        // If occupied, place temp at front of line
        else
        {
            tmp->next = hashtable[hash];
            hashtable[hash] = tmp;
        }
    }

    fclose(file);
    isloaded = true;
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (wordCount == 0)
    {
        return 0;
    }
    else
    {
        return wordCount;
    }

}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < HASHTABLESIZE; i++)
    {
        node *pointer = hashtable[i];

        //Clear out the linked lists the same way we found values in them
        while (pointer != NULL)
        {
            node *deleter = pointer;
            pointer = pointer->next;
            free(deleter);
        }




    }




    return true;
}
