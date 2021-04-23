#include "frs.h"
#include <assert.h>

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

    return G;
}