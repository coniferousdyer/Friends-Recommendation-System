#include "frs.h"
#include <assert.h>
#include "queue.h"
#include "binarysearch.h"
#include "heap.h"

// #define NDEBUG

User *CreateUser()
{
    User *U = (User *)malloc(sizeof(User));
    assert(U != NULL && "Malloc returned NULL in CreateUser().");
    U->friendList = CreateFriendList();
    U->numFriends = 0;

    return U;
}

User **CreateUserList()
{
    User **U = (User **)malloc(2 * sizeof(User *)); // Initial array size of 4
    assert(U != NULL && "Malloc returned NULL in CreateUserList().");
    for (int i = 0; i < 4; i++)
        U[i] = NULL;

    return U;
}

int *CreateFriendList()
{
    int *FL = (int *)malloc(2 * sizeof(int)); // Initial array size of 2
    assert(FL != NULL && "Malloc returned NULL in CreateFriendList().");

    return FL;
}

Graph *CreateGraph()
{
    Graph *G = (Graph *)malloc(sizeof(Graph));
    assert(G != NULL && "Malloc returned NULL in CreateGraph().");
    G->userList = CreateUserList();
    G->numUsers = 0;
    G->minHeap = (int *)malloc(2 * sizeof(int));
    G->heapSize = 0;

    return G;
}

Graph *DeleteGraph(Graph *G)
{
    for (int i = 0; i < G->numUsers; i++)
    {
        free(G->userList[i]->friendList);
        free(G->userList[i]);
    }

    free(G->userList);
    free(G->minHeap);
    free(G);

    return NULL;
}

void RegFriends(Graph *G, int userID, int K)
{
    if (userID >= G->numUsers)
    {
        printf("Error occurred. User does not exist.\n");
        return;
    }

    printf("Would you like to make some friends? Here is a list of recommendations!\n\n");

    bool visited[G->numUsers];
    QueuePtr Q = CreateQueue();

    for (int i = 0; i < G->numUsers; i++)
        visited[i] = false;
    visited[userID] = true;
    // Marking user and user's friends as already visited
    // Enqueueing friends
    for (int i = 0; i < G->userList[userID]->numFriends; i++)
    {
        visited[G->userList[userID]->friendList[i]] = true;
        Enqueue(Q, G->userList[userID]->friendList[i]);
    }

    // We subtract the number of friends of user from total number of users
    int n = G->numUsers - G->userList[userID]->numFriends;
    int K = (n <= K ? n : K);

    while (K--)
    {
        int u = Q->front->id; // u -> current node in queue
        Dequeue(Q);

        for (int i = 0; i < G->userList[u]->numFriends; i++)
            if (!visited[G->userList[u]->friendList[i]])
            {
                visited[G->userList[u]->friendList[i]] = true;
                Enqueue(Q, G->userList[u]->friendList[i]);
                printf("%d\t%s\tAge %d\t%s\n%d friends\n",
                       G->userList[u]->id,
                       G->userList[u]->name,
                       G->userList[u]->age,
                       G->userList[u]->city,
                       G->userList[u]->numFriends);
            }
    }

    printf("\n");

    //-----------------------//

    printf("Enter IDs of users from above whom you would like to add as friends: ");

    int friendID, count = 0;

    while (scanf("%d", &friendID) > 0)
    {
        AddFriend(G, userID, friendID);
        count++;
    }

    printf("\n%d users added as friends of %s (ID %d).\n\n", count, G->userList[userID]->name, userID);

    DeleteQueue(Q);
}

void removefriendofuser(Graph *G, int num)
{
    for (int i = 0; i < G->numUsers; i++)
    {
        if (G->userList[i] == NULL)
            continue;

        // Binary searching for the position of the userID
        int pos = SearchValue(G->userList[i]->friendList, G->userList[i]->numFriends, num);

        if (pos != -1)
        {
            for (int j = pos + 1; j < G->userList[i]->numFriends; j++)
                G->userList[i]->friendList[j - 1] = G->userList[i]->friendList[j]; // Shifting elements to left
            G->userList[i]->numFriends--;                                          // Decreasing number of friends by 1
        }
    }
}

void RemoveUser(Graph *G, int num)
{
    if (G->userList[num] == NULL)
    {
        printf("\n\nThe user does not exist in the network. Please enter a different ID.\n\n");
        return;
    }

    Insert(G->minHeap, &G->heapSize, num); // Adding deleted index to heap

    free(G->userList[num]->friendList);
    free(G->userList[num]);

    removefriendofuser(G, num);

    G->userList[num] = NULL;
}

bool IsFriend(Graph *G, int idA, int idB)
{
    if (!(G->userList[idA]))
        printf("User for ID %d does not exist.\n\n", idA);
    else if (!(G->userList[idB]))
        printf("User for ID %d does not exist.\n\n", idB);
    else
    {
        User *firstUser = G->userList[idA];
        return BinarySearch(firstUser->friendList, idB, 0, (firstUser->numFriends) - 1);
    }

    return 0;
}

void AddUser(Graph *G, User *U)
{
    int i = 0;

    // Using iteration we can always allot minimum positive integer to the added user.
    // We have to make sure while removing user that user* is again pointed to NULL
    // or else that would destroy the continuity.
    while (i < G->numUsers && G->userList[i] != NULL)
    {
        i++;
    }

    // G->userlist[i] would be a user* which is NULL
    // We need to update this pointer to user*
    // here user* is a pointer to struct user that stores all data related to that particular user.
    if (i <= G->numUsers - 1)
        G->userList[i] = U;
    else
    {
        //  we have to resize the array ...
        // after we have that function
        G->userList[G->numUsers] = U;
    }

    return;
}