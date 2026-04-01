#ifndef USER_HPP
#define USER_HPP

#include "AVLTree.hpp"
#include <unordered_map>
#include <string>
using namespace std;

class user
{
public:
    string name;
    AVLTree posts;
    unordered_map<string, bool> directFriends;
    user *next;

    user(string username)
    {
        name = username;
        next = nullptr;
    }

    void addPost(string content)
    {
        posts.push_back(content);
    }

    void showTopPosts(int N)
    {
        posts.displayTopN(N);
    }

    void addFriend(string friendName)
    {
        directFriends[friendName] = true;
    }
};

#endif