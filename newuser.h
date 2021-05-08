#ifndef NEWUSER_H
#define NEWUSER_H

#include "queue.h"
#include "frs.h"
#include <stdlib.h>
#include <string.h>

// Stores a matrix containing linked lists containing user IDs
// The linked list at grid[i][j] has a string parameter whose length is i + 1 and starts with the (j + 1)th letter of the alphabet
typedef struct StringHashtable
{
    Node *grid[13][26];
} StringHashtable;

// A normal hash table which stores integers
typedef struct IntHashtable
{
    Node *array[100];
} IntHashtable;

StringHashtable *CreateSHT();

// Inserts ID into SHT
void SHTCity_Insert(Graph *G, StringHashtable *S, int id);
// Deletes ID from SHT
void SHTCity_Delete(Graph *G, StringHashtable *S, int id);
// Traverses linked list at S->grid[i][j] and stores
void SHTCity_Traverse(Graph *G, StringHashtable *S, int A[], char city[]);

void SHTSchool_Insert(Graph *G, StringHashtable *S, int id);
void SHTSchool_Delete(Graph *G, StringHashtable *S, int id);
void SHTSchool_Traverse(Graph *G, StringHashtable *S, int A[], char city[]);

#endif