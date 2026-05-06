#include <iostream>
#include <string>
#include <vector>
using namespace std;


//======================
// NODE STRUCTURE
//======================

struct Node {
    int data;
    Node* left;
    Node* right;

    Node() : data(0), left(nullptr), right(nullptr) {}
    Node(int x) : data(x), left(nullptr), right(nullptr) {}
    Node(int x, Node *left, Node *right) : data(x), left(left), right(right) {}
};

/*
Problem:
Given the root of a binary tree, return all root-to-leaf paths in any order.
*/

// APPROACH 1: Pass by reference + Backtracking
class Solution {
private:
    void preorder(Node* root, string& st, vector<string>& paths) {
        if (!root) return;

        string temp = st;
        
        st += to_string(root->data);

        if (!root->left && !root->right) 
            paths.push_back(st);
        else {
            st += "->";
            preorder(root->left, st, paths);
            preorder(root->right, st, paths);
        }
        st = temp;
    }
public:
    vector<string> binaryTreePaths(Node* root) {
        vector<string> paths;
        string st = "";
        preorder(root, st, paths);
        return paths;
    }
};

// APPROACH 2: Pass by value -> No need to backtrack
class Solution {
private:
    void preorder(Node* root, string st, vector<string>& paths) {
        if (!root) return;
        
        st += to_string(root->data);

        if (!root->left && !root->right) 
            paths.push_back(st);
        else {
            st += "->";
            preorder(root->left, st, paths);
            preorder(root->right, st, paths);
        }
    }
public:
    vector<string> binaryTreePaths(Node* root) {
        vector<string> paths;
        string st = "";
        preorder(root, st, paths);
        return paths;
    }
};
