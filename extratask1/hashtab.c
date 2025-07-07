#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "eth.h"

unsigned int hash(int key, int size)
{
    return (unsigned int)key % size;
    
}

HashTable* create_table(int size)
{
    HashTable *ht = malloc(sizeof(HashTable));
    ht->size = size;
    ht->table = calloc(size, sizeof(KeyAndValue*));
    return ht;

}

void upset(HashTable *ht, int key, int value)
{
    unsigned int ind = hash(key, ht -> size);
    KeyAndValue *current = ht->table[ind];

    while (current != NULL)
    {
        if(current->key == key)
        {
            current->value = value;
            return;
        }
        current = current->next;
    }
    
    KeyAndValue *new_node = malloc(sizeof(KeyAndValue));
    new_node->key = key;
    new_node->value = value;
    new_node->next = ht->table[ind];
    ht->table[ind] = new_node;
}

int get(HashTable *ht, int key, int def_value)
{
    unsigned int ind = hash(key, ht -> size);
    KeyAndValue *current = ht->table[ind];

    while (current != NULL)
    {
        if(current->key == key)
        {
            return current->value;
        }
        current = current->next;
    }
    return def_value;
}

int update(HashTable *ht, int key, int new_value)
{
    unsigned int ind = hash(key, ht -> size);
    KeyAndValue *current = ht->table[ind];

    while (current != NULL)
    {
        if(current->key == key)
        {
            int old_value = current->value;
            current->value = new_value;
            return old_value;
        }
        current = current->next;
    }
    return -1;
}

void free_table(HashTable *ht)
{
    for (int i = 0; i < ht->size; i++)
    {
        KeyAndValue *current = ht->table[i];
        while (current != NULL)
        {
            KeyAndValue *temp = current;
            current = current->next;
            free(ht);
        }
    }
    free(ht->table);
    free(ht);
}