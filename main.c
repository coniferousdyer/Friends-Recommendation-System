#include "hash.h"
#include <stdio.h>

int main(void)
{
    Graph *G = CreateGraph();

    AddUser(G);
    AddUser(G);
    AddUser(G);
    RemoveUser(G, 1);
    AddUser(G);
    AddUser(G);
    RemoveUser(G, 0);
    AddUser(G);
    RemoveUser(G, 0);

    for (int i = 0; i < 5; i++)
    {
        if (G->userList[i] != NULL)
            printf("%d %s %s\n", G->userList[i]->id, G->userList[i]->name, G->userList[i]->city);
    }

    DeleteGraph(G);

    return 0;
}

// H_Insert works
// H_Delete works
// H_Search works
// H_Rehash works
// DeleteGraph works
// DeleteFriendList works
// CreateGraph works
// CreateUser works
// CreateFriendList works
// CreateUserList works
// AddUser works
// RemoveUser works

// RemoveFriendFromUser 
// AddFriend
// RemoveFriend
// IsFriend
// RegFriends
