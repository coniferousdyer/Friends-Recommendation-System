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

