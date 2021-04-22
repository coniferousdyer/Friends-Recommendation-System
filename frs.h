#ifndef FRS_H
#define FRS_H

#include <stdbool.h>

typedef struct User
{
    int id;
    char name[20];
    int age;
    char city[15];
    int numFriends;  // Number of friends user has
    int *friendList; // List of friends
} User;

typedef struct Graph
{
    int numUsers;   // Number of users
    User *userList; // List of users
} Graph;

User *CreateUser();
Graph *CreateGraph();

void AddUser(Graph *G);
void RemoveUser(Graph *G, int id);

bool IsFriend(Graph *G, int idA, int idB);
void RegFriends(Graph *G, int userID, int K);
void NewFriends(Graph *G, int userID);

#endif