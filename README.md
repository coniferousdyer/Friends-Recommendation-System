# Friends Recommendation System

This is the GitHub repository for Team 20, whose members have been assigned the project "Friends Recommendation System". 

The members of Team 20 are: 

* Jay Ghevariya
* Konduru Nithin
* Syed Imami
* Yashwanth Kottu
* Arjun Muraleedharan

<br>

# Structure

We have implemented our network as a graph. The graph is in turn implemented as an adjacency list, but with several modifications. We have used an array, userList of hash tables (friendList). Each element of userList is a pointer to a struct User, containing the details of the User. Each struct User contains a pointer to an array of Node pointers, which is the friendList of that User. Each Node pointer represents a bucket and points to a linked list. That is, we have used separate chaining here. The friendList contains only the IDs of the friends, which can be used to reference them if needed.

<br>
<p align="center">
<img src="Images/Network.png">
</p>
<br>

We also include a minHeap in the graph, which stores the IDs of the users deleted. This is done to minimize the time taken for user deletion, as we don't have to shift the elements of the array and change existing user IDs. We merely reserve the deleted ID for the next user to register. The next user to register would get the minimum of all the deleted IDs, which is why we use a minHeap.

<br>
<p align="center">
<img src="Images/MinHeap.png">
</p>
<br>

# Working

We make use of hashing to optimise the time taken for operations. Searching for a user in the userList of the graph can be done in O(1) time, as the array provides random access. Since the number of users are not known beforehand, we allocate a dynamic array of size 2, and double the size, reallocating elements every time the array is full. We follow the same procedure for the minHeap.

Each user starts off with a friendList of size 2, since again, the number of friends a user can have is not known beforehand. We again use a dynamic array here. However, random access does not help us here, as the friends' IDs are not placed in the corresponding indices, to conserve memory and time. 

Instead, we use separate chaining. Each element of the dynamic array is a bucket containing a few of the friends of the user. When the load factor becomes 1, we perform rehashing, doubling the table size.

<br>
<p align="center">
<img src="Images/Rehashing.png">
</p>
<br>

When we <strong>ADD A USER</strong>, we first check the minHeap to see if the ID of any previously deleted user is available or not. If heapSize = 0 (minHeap is empty), we assign the user ```G->maxUserID + 1``` as their ID. If not, we assign the user ```G->minHeap[0]```, the minimum ID in the heap. In this way, we guarantee that the user gets the minimum possible ID, while utilising left over space. An average of O(1) time is taken to add the user while O(log n) time is taken to maintain the heap property.

When we <strong>DELETE A USER</strong>, we free the memory associated with the user and insert their ID into the minHeap, so that any future users can be assigned that ID. We also delete the user from the friendLists of all the other users who have added that user as a friend. Deletion takes O(1) time, insertion of ID into the minHeap takes O(log n) time and removal of user from friendList of all users (```removefriendofuser()```) takes at worst O(n) time.

## <strong>Friends Recommendation</strong>

There are two different recommendation algorithms we have used here:

1. For already existing users (those who have friends)
2. For newly registered users (those with no friends)

<br>

For <strong>EXISTING USERS</strong> with friends, our algorithm is based on recommending friends of friends of the user, friends of those friends and so on. In order to achieve this in the fastest time possible, we perform <strong>Breadth-First Traversal</strong> starting from the user. We have implemented a queue which stores the user IDs for this purpose. We start with the user and their friends by enqueueing them, but we do not count them. Instead, we traverse through their friends, the friends of their friends and so on. The user is thus recommended new friends in this way.

For <strong>NEW USERS</strong> without friends, our algorithm is based on <strong>grouping users with common parameters together</strong>. We use the idea of hash tables to divide users into buckets and access them quicker. We have an integer hash table (IntHashtable) for age, and 2 string hash table (StringHashtable) for city and school. 

* IntHashtable consists of a 1D array of linked lists. The linked list at the i-th position contains the IDs of users for which i = age % 100. 

* StringHashtable consists of a 2D array of linked lists. The linked list at i, j contains the strings of length i + 1 and starting with the j-th letter of the alphabet.






