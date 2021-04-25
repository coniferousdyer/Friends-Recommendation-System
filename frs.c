#include "frs.h"
#include <assert.h>
#include "queue.h"

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
    User **U = (User **)malloc(4 * sizeof(User *)); // Initial array size of 4
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
    G->minHeap = (int *)malloc(4 * sizeof(int));
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

    DeleteQueue(Q);
}