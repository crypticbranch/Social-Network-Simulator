#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include "TreeNode.hpp"
#include <algorithm>
#include <climits>

class AVLTree
{
private:
    TreeNode *root;

    int getHeight(TreeNode *node)
    {
        return node ? node->height : 0;
    }

    int getBalance(TreeNode *node)
    {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    TreeNode *rightRotate(TreeNode *y)
    {
        TreeNode *x = y->left;
        TreeNode *T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        return x;
    }

    TreeNode *leftRotate(TreeNode *x)
    {
        TreeNode *y = x->right;
        TreeNode *T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        return y;
    }

    TreeNode *insert(TreeNode *node, const string &value, time_t ts)
    {
        if (!node)
            return new TreeNode(value);

        if (ts < node->timestamp)
            node->left = insert(node->left, value, ts);
        else
            node->right = insert(node->right, value, ts);

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        if (balance > 1 && ts < node->left->timestamp)
            return rightRotate(node);
        if (balance < -1 && ts > node->right->timestamp)
            return leftRotate(node);
        if (balance > 1 && ts > node->left->timestamp)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && ts < node->right->timestamp)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void printInOrder(TreeNode *node, int &N)
    {
        if (!node || N == 0)
            return;
        printInOrder(node->right, N);
        if (N > 0)
        {
            cout << node->content << " ";
            N--;
        }
        printInOrder(node->left, N);
    }

public:
    AVLTree() { root = nullptr; }

    void push_back(const string &value)
    {
        time_t now = time(0);
        root = insert(root, value, now);
    }

    void displayTopN(int N)
    {
        if (N == -1)
            N = INT_MAX;
        printInOrder(root, N);
        cout << endl;
    }
};

#endif