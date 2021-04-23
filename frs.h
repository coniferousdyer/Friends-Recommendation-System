#ifndef FRS_H
#define FRS_H

#include <stdbool.h>
#include <stdlib.h>

// The information about each user is contained in a struct
typedef struct User
{
    int id;          // ID assigned to user
    char name[20];   // Name of user
    int age;         // Age of user
    char city[15];   // Name of city of user
    int numFriends;  // Number of friends user has
    int *friendList; // List of friends
} User;

/*
 * We implement our network as a graph.
 * The graph is represented as an array of linked lists.
 * Each element of the array is pointer to a struct User.
 * Each User has a pointer to an integer array containing their friends.
*/
typedef struct Graph
{
    int numUsers;    // Number of users
    User **userList; // List of users
} Graph;

User *CreateUser();      // Initialise an empty user
User **CreateUserList();  // Initialise an empty userlist
int *CreateFriendList(); // Initialise an empty integer array friendList
Graph *CreateGraph();    // Initialise an empty graph

void AddUser(Graph *G);            // To register a user
void RemoveUser(Graph *G, int id); // To unregister a user

void AddFriend(Graph *G, int userID, int friendID); // To add a friend
bool IsFriend(Graph *G, int idA, int idB);          // To check if A is a friend of B

// To recommend friends to existing users
void RegFriends(Graph *G, int userID, int K);
// To recommend friends to new users
void NewFriends(Graph *G, int userID);

Graph *DeleteGraph(); // To delete the graph at the end of the program

#endif