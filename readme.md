# SocialNet Simulator

---

## **Project Overview**

This project implements an **in-memory Social Media Network simulator**, where every user is represented as a vertex in a graph, and friendships are represented as undirected edges between users.

It supports **friend recommendations**, **degrees of separation**, **post management**, and **user connections** — similar to a simplified version of Facebook or LinkedIn’s backend graph system.

---

## **Compilation and Execution**

### **Build Script**

We provide a shell script `run.sh` to compile and execute the program.

```bash
#!/bin/bash
g++ -std=c++17 main.cpp -o socialnet
./socialnet
```

---

### **Usage Instructions**

#### **1. Open a terminal in your project folder**

```bash
cd ~/Desktop/SocialNet
```

#### **2. Make the script executable (first time only):**

```bash
chmod +x run.sh
```

#### **3. Run the script:**

```bash
./run.sh
```

The program starts in **interactive mode**. You’ll see:

```
Enter commands (type EXIT to stop):
```

At this point, you can start typing commands such as `ADD_USER`, `ADD_FRIEND`, etc.
After each command is executed, the program waits for the next one until you type `EXIT`.

---

### **Example Session**

```bash
ADD_USER Alice
ADD_USER Bob
ADD_USER Charlie
ADD_FRIEND Alice Bob
ADD_FRIEND Bob Charlie
ADD_POST Alice "Hello World!"
SUGGEST_FRIENDS Alice 3
DEGREES_OF_SEPARATION Alice Charlie
OUTPUT_POSTS Alice 5
EXIT
```

**Output:**

```
Charlie (1 mutuals)
2
Hello World!
Exiting program...
```

---

## **System Design**

### **1️⃣ User Class**

Each `user` object represents an individual in the network.
It contains:

* `string name` – user’s username
* `AVLTree posts` – stores posts sorted by creation time
* `unordered_map<string, bool> directFriends` – stores direct friends
* `user* next` – pointer for chaining users (if required)

**Methods:**

* `addFriend(string friendName)`
* `addPost(string content)`
* `showTopPosts(int N)`

---

### **2️⃣ Graph Class**

Represents the entire social network.

**Core Components:**

* `unordered_map<string, user*> users` – stores users by normalized (lowercase) names

**Key Methods:**

* `addUser(string username)` — creates a new user node
* `addFriendship(string user1, string user2)` — adds a mutual friendship
* `addPost(string username, string content)` — adds a post for a user
* `showPosts(string username, int N)` — displays top N posts of a user
* `suggestFriends(string username, int N)` — recommends new friends using mutual friends logic
* `degreeOfSeparation(string user1, string user2)` — finds the shortest connection path (using BFS)
* `listFriends(string username)` — lists all direct friends alphabetically

---

### **3️⃣ AVL Tree (for Posts)**

Implements a self-balancing binary search tree to maintain posts in chronological order.
Each node (`TreeNode`) contains:

* `string content`
* `time_t timestamp`
* `TreeNode *left, *right`
* `int height`

**Operations:**

* `insert()` — inserts posts while maintaining balance
* `rightRotate()` / `leftRotate()` — standard AVL rotations
* `displayTopN(N)` — prints most recent N posts

---

## **Supported Commands**

| Command                                 | Description                                                                        |
| --------------------------------------- | ---------------------------------------------------------------------------------- |
| `ADD_USER <username>`                   | Creates a new user                                                                 |
| `ADD_FRIEND <user1> <user2>`            | Adds a friendship between two users                                                |
| `ADD_POST <username> <"content">`       | Adds a post to the given user                                                      |
| `LIST_FRIENDS <username>`               | Displays all friends of a user                                                     |
| `SUGGEST_FRIENDS <username> <N>`        | Suggests up to N potential friends (sorted by mutual friends, then alphabetically) |
| `DEGREES_OF_SEPARATION <user1> <user2>` | Returns the degree of separation between two users                                 |
| `OUTPUT_POSTS <username> <N>`           | Displays top N most recent posts of the user                                       |
| `EXIT`                                  | Ends the program                                                                   |

---

## **Algorithmic Details**

### 🔹 Friend Suggestion Logic

* For each direct friend of the given user:

  * Traverse their friends (friends-of-friends).
  * If they are not the user and not already a direct friend, increment their **mutual count**.
* Sort by descending mutual count and alphabetically for ties.

**Time Complexity:**
O(F²) in the worst case (F = number of friends).

---

### 🔹 Degree of Separation

Implements a **Breadth-First Search (BFS)** from `user1` to `user2`.

**Algorithm Steps:**

1. Start at `user1` (distance = 0)
2. Explore all friends level by level
3. Return level count when `user2` is reached

**Time Complexity:**
O(V + E), where V = number of users, E = friendships.

---

### 🔹 AVL Tree (Posts)

* Each insertion takes O(log N) due to balancing.
* Retrieving top N posts is O(N).

---

## **Error Handling**

| Error                                        | Output                               |
| -------------------------------------------- | ------------------------------------ |
| Adding an existing user                      | `"User not found"`                 |
| Adding friendship between non-existent users | `"One or both users not found"`                |
| Posting for a non-existent user              | `"User not found"`                   |
| Suggesting friends for non-existent user     | `"User not found"`                   |
| No friend suggestions available              | `"No friend suggestions available."` |

---

## **Complexity Analysis**

| Operation            | Time Complexity |
| -------------------- | --------------- |
| Add User             | O(1)            |
| Add Friendship       | O(1)            |
| Suggest Friends      | O(F²)           |
| Degree of Separation | O(V + E)        |
| Add Post             | O(log N)        |
| Show Posts           | O(N)            |
| List Friends         | O(F log F)      |

---


