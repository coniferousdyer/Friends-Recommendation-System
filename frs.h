#ifndef FRS_H
#define FRS_H

#include <stdbool.h>
#include <stdlib.h>
#include "queue.h"

// The information about each user is contained in a struct
typedef struct User
{
    int id;            // ID assigned to user
    char name[20];     // Name of user
    int age;           // Age of user
    char city[15];     // Name of city of user
    int numFriends;    // Number of friends user has
    Node **friendList; // List of friends (a hash table)
    int bucketNo;      // Number of buckets in friendList
} User;

/*
 * We implement our network as a graph.
 * The graph is represented as an array of hash tables.
 * Each element of the hash table is pointer to a linked list of struct Users.
 * That is, we use separate chaining in our graph.
*/
typedef struct Graph
{
    int numUsers;    // Number of users
    User **userList; // List of users
    int maxUserID;   // Stores the maximum user ID in userList
    int *minHeap;    // To retrieve minimum possible ID from deleted elements
    int heapSize;
} Graph;

User *CreateUser();        // Initialise an empty user
User **CreateUserList();   // Initialise an empty userlist
Node **CreateFriendList(); // Initialise an empty integer array friendList
Graph *CreateGraph();      // Initialise an empty graph

void AddUser(Graph *G);            // To register a user
void RemoveUser(Graph *G, int id); // To unregister a user

void removefriendofuser(Graph *G, int num); // To remove user with ID num from friendList of users

void AddFriend(Graph *G, int userID, int friendID);    // To add a friend
void RemoveFriend(Graph *G, int userID, int friendID); // To unfriend someone
void IsFriend(Graph *G, int idA, int idB);             // To check if A is a friend of B

// To recommend friends to existing users
void RegFriends(Graph *G, int userID, int K);
// To recommend friends to new users
void NewFriends(Graph *G, int userID);

void DeleteFriendList(Graph *G, int userID); // To delete a user's friendList
void DeleteGraph(Graph *G);                  // To delete the graph at the end of the program

#endif
