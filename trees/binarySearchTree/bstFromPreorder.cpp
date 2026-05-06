#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <utility>
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
Given an array of integers preorder, which represents the preorder traversal of a BST (i.e., binary search tree), 
construct the tree and return its root.
*/

class Solution {
private:
    Node* bstBuild(int& i, vector<int>& preorder, int ub) {
        // If we've used all elements or the current element 
        // doesn't fit in the current BST range, return null.
        if (i >= preorder.size() || preorder[i] > ub) 
            return nullptr;
        
        // The current element is the root for this subtree
        Node* root = new Node(preorder[i++]);

        // For left subtree: the current root's value is the new upper limit
        root->left = bstBuild(i, preorder, root->data);
        
        // For right subtree: the upper limit remains whatever it was for the current root
        root->right = bstBuild(i, preorder, ub);
        return root;
    }

public:
    Node* bstFromPreorder(vector<int>& preorder) {
        int i = 0;
        return bstBuild(i, preorder, INT_MAX);
    }
};