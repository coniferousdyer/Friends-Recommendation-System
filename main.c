#include "hash.h"
#include "graphics.h"
#include <stdio.h>

int main(void)
{
    Graph *G = CreateGraph();

    // //------------TRIAL-------------//
    // AddUser(G);
    // AddUser(G);
    // AddUser(G);
    // AddUser(G);
    // AddUser(G);
    // AddUser(G);
    // AddUser(G);
    // AddUser(G);
    // AddUser(G);
    // AddUser(G);
    // AddFriend(G, 0, 1);
    // AddFriend(G, 0, 2);
    // AddFriend(G, 0, 3);
    // AddFriend(G, 1, 7);
    // AddFriend(G, 1, 8);
    // AddFriend(G, 1, 2);
    // AddFriend(G, 2, 6);
    // AddFriend(G, 3, 5);
    // AddFriend(G, 3, 4);
    // AddFriend(G, 4, 9);
    // AddFriend(G, 5, 9);
    // //------------------------------//

    int currentID; // To store the ID of the currently logged in user
    char option;

    //-------------------LOGIN---------------------//

    system("clear");
    PrintTitle();
    delay(3000);

logout: // Whenever a user logs out or deletes their account
    system("clear");
    PrintLoginMenu();

    printf("\nEnter option (1 to signup, 2 to login, 3 to exit): ");
    scanf(" %c", &option);

    switch (option)
    {
    case '1': // SIGN UP
        system("clear");
        Signup(G, &currentID);    // Prompts user to sign up by entering details
        NewFriends(G, currentID); // Recommends new friends
        break;
    case '2': // LOG IN
        system("clear");
        Login(G, &currentID); // Prompts user to log in with a valid ID
        break;
    case '3': // EXIT
    {
        system("clear");
        printf("\nBye! Hope to see you back!\n\n");
        DeleteGraph(G); // Deleting memory malloced for graph
        exit(0);
    }
    break;
    default:
    {
        printf("\nInvalid option entered. Please try again.\n");
        delay(2000);
        goto logout; // Retry login
    }
    }

    //-----------------MAIN MENU------------------//

    do // Enclosing main menu in an infinite do-while loop
    {
        delay(2000);
        system("clear");
        PrintMenu();

    retryMainMenu: // When main menu option choosing fails
        printf("\nEnter option: ");
        scanf(" %c", &option);

        switch (option)
        {
        case '1': // ADD FRIEND
        {
            int friendID;
            printf("Enter ID of user you want to add as friend: ");
            scanf("%d", &friendID);

            // Checking if friend actually exists
            if (G->userList[friendID] == NULL || friendID > G->maxUserID)
            {
                printf("\n\nSuch a user does not exist and cannot be added as a friend.\n\n");
                delay(2000);
                continue; // Return to main menu
            }

            if (friendID == currentID)
            {
                printf("\nA user cannot be their own friend.\n");
                delay(2000);
                continue; // Return to main menu
            }

            AddFriend(G, currentID, friendID);
        }
        break;

        case '2': // UNFRIEND
        {
            int friendID;
            printf("Enter ID of user you want to unfriend: ");
            scanf("%d", &friendID);

            // Friend does not exist
            if (G->userList[friendID] == NULL || friendID > G->maxUserID)
            {
                printf("\n\nUser with ID %d does not exist.\n\n", friendID);
                delay(2000);
                continue; // Return to main menu
            }

            RemoveFriend(G, currentID, friendID);
        }
        break;

        case '3': // CHECK FRIEND
        {
            int userID, friendID;
            printf("Enter ID of user whose friend list you want to search: ");
            scanf("%d", &userID);
            printf("Enter ID of user whom you want to check is their friend: ");
            scanf("%d", &friendID);

            // User does not exist
            if (G->userList[userID] == NULL || userID > G->maxUserID)
            {
                printf("\n\nUser with ID %d does not exist.\n\n", friendID);
                delay(2000);
                continue; // Return to main menu
            }

            // Friend does not exist
            if (G->userList[friendID] == NULL || friendID > G->maxUserID)
            {
                printf("\n\nUser with ID %d does not exist.\n\n", friendID);
                delay(2000);
                continue; // Return to main menu
            }

            IsFriend(G, userID, friendID);
        }
        break;

        case '4': // RECOMMEND FRIENDS
        {
            // If user has no friends, then we recommend new friends based on our algorithm
            // Else we recommend them based on friends on friends

            if (G->userList[currentID]->numFriends == 0) // Checks if user has no friends
                NewFriends(G, currentID);
            else
            {
                int K;
                printf("Enter number of recommendations you would like: ");
                scanf("%d", &K);
                RegFriends(G, currentID, K);
            }
        }
        break;

        case '5': // LOG OUT
        {
            printf("\nYou have been logged out.\n");
            delay(2000);
            goto logout;
        }
        break;

        case '6': // DELETE ACCOUNT
        {
            RemoveUser(G, currentID);
            printf("\nAccount has been successfully deleted.\n");
            delay(2000);
            goto logout;
        }
        break;

        case '7': // EXIT
        {
            system("clear");
            printf("\nBye! Hope to see you back!\n\n");
            DeleteGraph(G); // Deleting memory malloced for graph
            exit(0);
        }
        break;

        default:
        {
            printf("\nInvalid option entered. Please try again.\n");
            delay(2000);
        }
        }
    } while (true);

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
// RemoveFriend works
// RemoveFriendFromUser works

// RegFriends
// NewFriends
