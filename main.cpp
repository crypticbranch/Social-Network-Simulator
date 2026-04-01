#include <iostream>
#include <sstream>
#include <string>
#include "Graph.hpp"
using namespace std;

int main()
{
    graph g;
    string line;

    cout << "Enter commands (type EXIT to stop):\n";

    while (getline(cin, line))
    {
        if (line.empty())
            continue;

        stringstream ss(line);
        string command;
        ss >> command;

        // -------------------- ADD_USER --------------------
        if (command == "ADD_USER")
        {
            string username;
            ss >> username;
            g.addUser(username);
        }

        // -------------------- ADD_FRIEND --------------------
        else if (command == "ADD_FRIEND")
        {
            string u1, u2;
            ss >> u1 >> u2;
            g.addFriendship(u1, u2);
        }

        // -------------------- ADD_POST --------------------
        else if (command == "ADD_POST")
        {
            string username;
            ss >> username;
            string content;
            getline(ss, content);
            content.erase(0, content.find_first_not_of(" \""));
            content.erase(content.find_last_not_of("\" ") + 1);
            g.addPost(username, content);
        }

        // -------------------- LIST_FRIENDS --------------------
        else if (command == "LIST_FRIENDS")
        {
            string username;
            ss >> username;
            g.listFriends(username);
        }

        // -------------------- SUGGEST_FRIENDS --------------------
        else if (command == "SUGGEST_FRIENDS")
        {
            string username;
            int N;
            ss >> username >> N;
            g.suggestFriends(username, N);
        }

        // -------------------- DEGREES_OF_SEPARATION --------------------
        else if (command == "DEGREES_OF_SEPARATION")
        {
            string u1, u2;
            ss >> u1 >> u2;
            int d = g.degreeOfSeparation(u1, u2);
            cout << d << "\n";
        }

        // -------------------- OUTPUT_POSTS --------------------
        else if (command == "OUTPUT_POSTS")
        {
            string username;
            int N;
            ss >> username >> N;
            g.showPosts(username, N);
        }

        // -------------------- EXIT --------------------
        else if (command == "EXIT")
        {
            cout << "Exiting program...\n";
            break;
        }

        // -------------------- INVALID --------------------
        else
        {
            cout << "Invalid command: " << command << "\n";
        }
    }

    return 0;
}