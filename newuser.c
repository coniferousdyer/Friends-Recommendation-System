#include "newuser.h"

//-------------Linked List functions-------------//

Node *CreateNode()
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->next = NULL;

    return newNode;
}

Node *SLL_Insert(Node *head, int n)
{
    Node *newHead = CreateNode();

    newHead->next = head;
    newHead->id = n;

    return newHead;
}

Node *SLL_Delete(Node *head, int n)
{
    Node *temp = head, *previous = NULL;

    while (temp != NULL && temp->id != n)
    {
        previous = temp;
        temp = temp->next;
    }

    if (temp == NULL)
        return NULL;
    else if (previous == NULL)
    {
        head = temp->next;
        free(temp);
        return head;
    }
    else
    {
        previous->next = temp->next;
        free(temp);
        return head;
    }
}

void DeleteSLL(Node *head)
{
    Node *temp = head, *holder = NULL;

    while (temp != NULL)
    {
        holder = temp;
        temp = temp->next;
        free(holder);
    }
}

//-------------IntHashtable-------------//

IntHashtable *CreateIHT()
{
    IntHashtable *I = (IntHashtable *)malloc(sizeof(IntHashtable));

    for (int i = 0; i < 100; i++)
        I->array[i] = NULL;

    return I;
}

void DeleteIHT(IntHashtable *I)
{
    for (int i = 0; i < 100; i++)
       DeleteSLL(I->array[i]);

    free(I->array);
    free(I);
}

void IHT_Insert(Graph *G, IntHashtable *I, int id)
{
    int i = G->userList[id]->age % 100;

    I->array[i] = SLL_Insert(I->array[i], id);
}

void IHT_Delete(Graph *G, IntHashtable *I, int id)
{
    int i = G->userList[id]->age;

    I->array[i] = SLL_Delete(I->array[i], id);
}

void IHT_Traverse(Graph *G, IntHashtable *I, int A[], int age)
{
    Node *temp = I->array[age];
    int i = 0;

    while (temp != NULL)
    {
        if (temp->id == age)
        {
            A[i] = temp->id;
            ++i;
        }

        temp = temp->next;
    }
}

//-------------StringHashtable Functions-------------//

// SHT -> City

StringHashtable *CreateSHT()
{
    StringHashtable *S = (StringHashtable *)malloc(sizeof(StringHashtable));

    for (int i = 0; i < 13; i++)
        for (int j = 0; j < 26; j++)
            S->grid[i][j] = NULL; // Initialising every element of 2D matrix to NULL

    return S;
}

void DeleteStringHashtable(StringHashtable *S)
{
    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 26; j++)
            DeleteSLL(S->grid[i][j]); // Deleting each linked list

        free(S->grid[i]); // Freeing each row of 2D matrix
    }

    free(S->grid); // Freeing whole matrix
    free(S);       // Freeing StringHashtable
}

void SHTCity_Insert(Graph *G, StringHashtable *S, int id)
{
    int i = strlen(G->userList[id]->city) - 1; // Checking length of city of user ID
    int j = G->userList[id]->city[0] - 'A';    // Checking first letter of city of user ID

    S->grid[i][j] = SLL_Insert(S->grid[i][j], id);
}

void SHTCity_Delete(Graph *G, StringHashtable *S, int id)
{
    int i = strlen(G->userList[id]->city) - 1; // Checking length of city of user ID
    int j = G->userList[id]->city[0] - 'A';    // Checking first letter of city of user ID

    S->grid[i][j] = SLL_Delete(S->grid[i][j], id);
}

void SHTCity_Traverse(Graph *G, StringHashtable *S, int A[], char city[])
{
    int i = strlen(city) - 1; // Checking length of city of user ID
    int j = city[0] - 'A';    // Checking first letter of city of user ID

    Node *temp = S->grid[i][j];
    int i = 0;

    while (temp != NULL) // Traverses through linked list at grid[i][j]
    {
        if (strcmp(G->userList[temp->id]->city, city) == 0)
        {
            A[i] = temp->id; // Storing IDs of users who are from city
            ++i;
        }

        temp = temp->next;
    }
}

// SHT -> School

void SHTSchool_Insert(Graph *G, StringHashtable *S, int id)
{
    int i = strlen(G->userList[id]->school) - 1; // Checking length of city of user ID
    int j = G->userList[id]->school[0] - 'A';    // Checking first letter of city of user ID

    S->grid[i][j] = SLL_Insert(S->grid[i][j], id);
}

void SHTSchool_Delete(Graph *G, StringHashtable *S, int id)
{
    int i = strlen(G->userList[id]->school) - 1; // Checking length of city of user ID
    int j = G->userList[id]->school[0] - 'A';    // Checking first letter of city of user ID

    S->grid[i][j] = SLL_Delete(S->grid[i][j], id);
}

void SHTSchool_Traverse(Graph *G, StringHashtable *S, int A[], char school[])
{
    int i = strlen(school) - 1; // Checking length of city of user ID
    int j = school[0] - 'A';    // Checking first letter of city of user ID

    Node *temp = S->grid[i][j];
    int i = 0;

    while (temp != NULL) // Traverses through linked list at grid[i][j]
    {
        if (strcmp(G->userList[temp->id]->school, school) == 0)
        {
            A[i] = temp->id; // Storing IDs of users who are from city
            ++i;
        }

        temp = temp->next;
    }
}

//-------------Friends Recommendation Functions-------------//
