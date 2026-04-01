#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "User.hpp"
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class graph
{
    unordered_map<string, user *> users;

    string normalize(string username)
    {
        transform(username.begin(), username.end(), username.begin(), ::tolower);
        return username;
    }

public:
    void addUser(string username)
    {
        username = normalize(username);
        if (users.find(username) == users.end())
        {
            users[username] = new user(username);
        }
    }

    void addFriendship(string user1, string user2)
    {
        user1 = normalize(user1);
        user2 = normalize(user2);
        if (user1 == user2)
        {
            cout << "Cannot befriend oneself.\n";
            return;
        }
        if (users.find(user1) == users.end() || users.find(user2) == users.end())
        {
            cout << "One or both users not found\n";
            return;
        }

        users[user1]->addFriend(user2);
        users[user2]->addFriend(user1);
    }

    void addPost(string username, string content)
    {
        username = normalize(username);
        if (users.find(username) == users.end())
        {
            cout << "User not found\n";
            return;
        }
        users[username]->addPost(content);
    }

    void showPosts(string username, int N)
    {
        username = normalize(username);
        if (users.find(username) == users.end())
        {
            cout << "User not found\n";
            return;
        }
        users[username]->showTopPosts(N);
    }

    // ---------- Suggest Friends ----------
    void suggestFriends(string username, int N)
    {
        username = normalize(username);
        if (users.find(username) == users.end())
        {
            cout << "User not found\n";
            return;
        }

        user *me = users[username];
        unordered_map<string, int> mutualCount;

        for (auto it = me->directFriends.begin(); it != me->directFriends.end(); ++it)
        {
            string friendName = it->first;
            user *f = users[friendName];

            for (auto inner = f->directFriends.begin(); inner != f->directFriends.end(); ++inner)
            {
                string fofName = inner->first;

                // skip self and direct friends
                if (fofName == me->name)
                    continue;
                if (me->directFriends.find(fofName) != me->directFriends.end())
                    continue;

                // count mutual connections
                mutualCount[fofName]++;
            }
        }

        vector<pair<string, int>> result(mutualCount.begin(), mutualCount.end());
        sort(result.begin(), result.end(), [](auto &a, auto &b)
             {
            if (a.second == b.second)
                return a.first < b.first;
            return a.second > b.second; });

        int count = 0;
        for (auto &r : result)
        {
            if (count++ == N)
                break;
            cout << r.first << " (" << r.second << " mutuals)\n";
        }

        if (result.empty())
            cout << "No friend suggestions available.\n";
    }

    // ---------- Degrees of Separation ----------
    int degreeOfSeparation(string user1, string user2)
    {
        user1 = normalize(user1);
        user2 = normalize(user2);
        if (users.find(user1) == users.end() || users.find(user2) == users.end())
        {
            return -1;
        }
        if (user1 == user2)
            return 0;

        unordered_map<string, int> distance;
        for (auto &[uname, _] : users)
            distance[uname] = -1;

        distance[user1] = 0;
        queue<string> q;
        q.push(user1);

        while (!q.empty())
        {
            string current = q.front();
            q.pop();

            for (auto &[friendName, _] : users[current]->directFriends)
            {
                if (distance[friendName] == -1)
                {
                    distance[friendName] = distance[current] + 1;
                    q.push(friendName);
                    if (friendName == user2)
                        return distance[friendName];
                }
            }
        }
        return -1;
    }

    ~graph()
    {
        for (auto &[_, u] : users)
            delete u;
    }

    bool userExists(const string &username)
    {
        return users.find(normalize(username)) != users.end();
    }

    void listFriends(const string &username)
    {
        string u = normalize(username);
        if (users.find(u) == users.end())
        {
            cout << "User not found\n";
            return;
        }
        vector<string> friends;
        for (auto &f : users[u]->directFriends)
            friends.push_back(f.first);
        sort(friends.begin(), friends.end());
        for (auto &f : friends)
            cout << f << " ";
        cout << "\n";
    }
};

#endif