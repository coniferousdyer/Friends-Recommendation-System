#include "hash.h"
#include <stdio.h>

int main(void)
{
    Graph *G = CreateGraph();

    AddUser(G);

    printf("%d %s %s %s\n", G->userList[0]->id, G->userList[0]->name, G->userList[0]->city, G->userList[0]->school);

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
