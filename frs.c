#include "frs.h"
#include <assert.h>
#include "queue.h"
#include "hash.h"
#include "heap.h"

// #define NDEBUG

//-------------ALLOCATION-------------//

User *CreateUser()
{
    User *U = (User *)malloc(sizeof(User));
    assert(U != NULL && "Malloc returned NULL in CreateUser().");
    U->friendList = CreateFriendList();
    U->numFriends = 0;
    U->bucketNo = 2;

    return U;
}

User **CreateUserList()
{
    User **U = (User **)malloc(2 * sizeof(User *)); // Initial array size of 2
    assert(U != NULL && "Malloc returned NULL in CreateUserList().");
    U[0] = U[1] = NULL;

    return U;
}

Node **CreateFriendList()
{
    Node **FL = (Node **)malloc(2 * sizeof(Node *)); // Initial array size of 2
    assert(FL != NULL && "Malloc returned NULL in CreateFriendList().");
    FL[0] = FL[1] = NULL;

    return FL;
}

Graph *CreateGraph()
{
    Graph *G = (Graph *)malloc(sizeof(Graph));
    assert(G != NULL && "1st Malloc returned NULL in CreateGraph().");
    G->userList = CreateUserList();
    G->numUsers = 0;
    G->maxUserID = -1;
    G->minHeap = (int *)malloc(2 * sizeof(int));
    assert(G != NULL && "2nd Malloc returned NULL in CreateGraph().");
    G->heapSize = 0;

    return G;
}

//-------------DEALLOCATION-------------//

void DeleteFriendList(Graph *G, int userID)
{
    for (int i = 0; i < G->userList[userID]->bucketNo; i++)
    {
        Node *temp = G->userList[userID]->friendList[i];

        Node *holder;
        while (temp != NULL)
        {
            holder = temp;
            temp = temp->next;
            free(holder);
        }
    }
}

void DeleteGraph(Graph *G)
{
    for (int i = 0; i <= G->maxUserID; i++)
    {
        if (G->userList[i] != NULL)
        {
            DeleteFriendList(G, i);
            free(G->userList[i]->friendList);
            free(G->userList[i]);
        }
    }

    free(G->minHeap);
    free(G->userList);
    free(G);
}

//-------------FUNCTIONALITIES-------------//

void AddUser(Graph *G)
{
    User *U = CreateUser();

    // Assign ID to new user
    if (G->heapSize == 0)
    {
        ++G->maxUserID; // If no elements in minHeap (no deleted IDs left), then User is stored at end of userList
        U->id = G->maxUserID;
    }
    else
    {
        U->id = G->minHeap[0]; // If there was a deleted user, then their ID is unused. We select the minimum of the deleted IDs
        Delete(G->minHeap, &G->heapSize);
    }

    ++G->numUsers; // Increasing number of users

    // Input user details
    printf("Enter user's name: ");
    scanf(" %[^\n]", U->name);
    printf("Enter user's age: ");
    scanf("%d", &U->age);
    printf("Enter user's city: ");
    scanf(" %[^\n]", U->city);
    printf("Enter user's school: ");
    scanf(" %[^\n]", U->school);

    G->userList[U->id] = U; // Putting user in the correct position in userList

    /*
     * We check if userList is full.
     * We do this by checking if numUsers is a power of 2
     * The capacity of userList is always successive powers of 2, and if numUsers == capacity, then it must be the next power of 2
     * If A is a power of 2, then A & (A - 1) = 0
     * We check if it's greater than 1 because 1 is a power of 2 but initial array size is 2
    */
    if (((G->numUsers & (G->numUsers - 1)) == 0) && (G->numUsers > 1))
    {
        G->userList = realloc(G->userList, 2 * G->numUsers * sizeof(User *)); // If full, we double the capacity
        for (int i = G->numUsers; i < 2 * G->numUsers; i++)
            G->userList[i] = NULL;
    }

    printf("\nUser has been successfully registered!\n\n");
}

void RemoveUser(Graph *G, int id)
{
    // User does not exist
    if (G->userList[id] == NULL || id > G->maxUserID)
    {
        printf("\n\nUser with ID %d does not exist.\n\n", id);
        return;
    }

    // Removing deleted user from friendList of all users
    removefriendofuser(G, id);

    // Inserting deleted ID into the minHeap
    Insert(G->minHeap, &G->heapSize, id);
    --G->numUsers; // Decreasing number of users

    if (((G->heapSize) & (G->heapSize - 1) == 0) && (G->heapSize != 1))
        G->minHeap = realloc(G->minHeap, 2 * G->heapSize);

    DeleteFriendList(G, id);
    free(G->userList[id]->friendList);
    free(G->userList[id]);
    G->userList[id] = NULL;
}

void removefriendofuser(Graph *G, int num)
{
    for (int i = 0; i <= G->maxUserID; i++)
    {
        if (G->userList[i] == NULL || i == num)
            continue;

        H_Delete_Without_Text(G, i, num);
    }
}

void AddFriend(Graph *G, int userID, int friendID)
{
    // Checking if friend actually exists
    if (G->userList[friendID] == NULL || friendID > G->maxUserID)
    {
        printf("\n\nSuch a user does not exist and cannot be added as a friend.\n\n");
        return;
    }

    if (friendID == userID)
    {
        printf("\n\nA user cannot be their own friend.\n\n");
        return;
    }

    // Inserting it into the hash table friendList of user
    H_Insert(G, userID, friendID);

    // Incrementing number of friends of user
    ++G->userList[userID]->numFriends;

    // If load factor of friendList is 1, then we rehash
    if (G->userList[userID]->numFriends / G->userList[userID]->bucketNo == 1)
        H_Rehash(G, userID);

    printf("\n\n%s is now a friend of %s!\n\n", G->userList[friendID]->name, G->userList[userID]->name);
}

void RemoveFriend(Graph *G, int userID, int friendID)
{
    // User does not exist
    if (G->userList[friendID] == NULL || friendID > G->maxUserID)
    {
        printf("\n\nUser with ID %d does not exist.\n\n", friendID);
        return;
    }

    if (friendID == userID)
    {
        printf("\n\nA user cannot be their own friend.\n\n");
        return;
    }

    // Calling H_Delete_With_Text which deleted friend from friendList using hashing
    H_Delete_With_Text(G, userID, friendID);
}

void IsFriend(Graph *G, int idA, int idB)
{
    // Checking if friend actually exists
    if (G->userList[idB] == NULL || idB > G->maxUserID)
    {
        printf("\n\nSuch a user does not exist and cannot be a friend of the user.\n\n");
        return;
    }

    if (idA == idB)
    {
        printf("\n\nA user cannot be their own friend.\n\n");
        return;
    }

    // H_Search searches the hash table friendList for idB, and returns 1 if found and 0 if not found
    if (H_Search(G, idA, idB))
        printf("\n\nUser with %s is a friend of %s.\n\n", G->userList[idA]->name, G->userList[idB]->name);
    else
        printf("\n\nUser with %s is not a friend of %s.\n\n", G->userList[idA]->name, G->userList[idB]->name);
}

// We perform BFS to find second friends, third friends and so on
void RegFriends(Graph *G, int userID, int K)
{
    // User does not exist
    if (G->userList[userID] == NULL || userID > G->maxUserID)
    {
        printf("\n\nUser with ID %d does not exist.\n\n", userID);
        return;
    }

    printf("Would you like to make some friends? Here is a list of recommendations!\n\n");

    bool visited[G->numUsers];
    QueuePtr Q = CreateQueue();

    // We subtract the number of friends of user from total number of users
    int n = G->numUsers - G->userList[userID]->numFriends;
    K = (n <= K ? n : K);

    for (int i = 0; i < G->numUsers; i++)
        visited[i] = false;
    visited[userID] = true;
    // Marking user and user's friends as already visited
    // Enqueueing friends
    for (int i = 0; i < G->userList[userID]->bucketNo; i++)
    {
        Node *temp = G->userList[userID]->friendList[i];

        while (temp != NULL)
        {
            visited[temp->id] = true;
            Enqueue(Q, temp->id);
            temp = temp->next;
        }
    }

    while (true)
    {
        int u = Q->front->id; // u -> current node in queue
        Dequeue(Q);

        for (int i = 0; i < G->userList[u]->bucketNo; i++)
        {
            Node *temp = G->userList[u]->friendList[i];

            while (temp != NULL)
            {
                if (!visited[temp->id])
                {
                    visited[temp->id] = true;
                    Enqueue(Q, temp->id);

                    printf("%d\t%s\tAge %d\t%s\n%d friends\n",
                           G->userList[u]->id,
                           G->userList[u]->name,
                           G->userList[u]->age,
                           G->userList[u]->city,
                           G->userList[u]->numFriends);

                    --K;
                    if (!K)       // We check if K = 0
                        goto end; // If K = 0, then we terminate the process

                    temp = temp->next;
                }
            }
        }
    }

end:
    printf("\n");

    printf("Enter IDs of users from above whom you would like to add as friends: ");

    int friendID, count = 0;

    while (scanf("%d", &friendID) > 0)
    {
        H_Insert(G, userID, friendID);
        count++;
    }

    printf("\n%d users added as friends of %s (ID %d).\n\n", count, G->userList[userID]->name, userID);

    DeleteQueue(Q);
}

//-------------TO BE TAKEN CARE OF-------------//

// Check if friend is a user before searching/deleting. Let user try again?
// Check for duplicates in user and friendlist
// If searching for duplicates, display all?
// Test RegFriends and all functionalities
// In main.c, check if user exists before calling function (except for RegFriends, RemoveUser, AddUser)
