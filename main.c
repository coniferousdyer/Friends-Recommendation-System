#include "hash.h"
#include <stdio.h>

int main(void)
{
    Graph *G = CreateGraph();

    for (int i = 0; i < 3; i++)
        AddUser(G);

    printf("%d %s %s %s\n", G->userList[0]->id, G->userList[0]->name, G->userList[0]->city, G->userList[0]->school);

    for (int i = 1; i < 3; i++)
        AddFriend(G, 0, i);

    RemoveFriend(G, 0, 2);
    RemoveFriend(G, 0, 10);

    for (int i = 0; i < G->userList[0]->bucketNo; i++)
    {
        Node *temp = G->userList[0]->friendList[i];
        while (temp != NULL)
        {
            printf("%d ", temp->id);
            temp = temp->next;
        }
    }

    printf("\n");

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
// AddFriend works
// IsFriend works
// RemoveFriendFromUser works
// RemoveFriend works

// RegFriends
