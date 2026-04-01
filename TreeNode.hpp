#ifndef TREENODE_HPP
#define TREENODE_HPP

#include <iostream>
#include <ctime>
using namespace std;

class TreeNode
{
public:
    string content;
    time_t timestamp;
    TreeNode *left;
    TreeNode *right;
    int height;

    TreeNode(string value)
    {
        content = value;
        timestamp = time(0);
        left = right = nullptr;
        height = 1;
    }
};

#endif