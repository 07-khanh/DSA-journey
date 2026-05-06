#include <iostream>
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
Problem: Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.
*/

class Solution {
public:
    Node* lowestCommonAncestor(Node* root, Node* p, Node* q) {
        // Base Case: If we hit null or find one of the targets
        if (!root) return nullptr;
        if (root == p || root == q) return root;

        // Search in left and right subtrees
        Node* leftLca = lowestCommonAncestor(root->left, p , q); 
        Node* rightLca = lowestCommonAncestor(root->right, p , q); 

        // If both left and right are non-null, this node is the LCA
        if (leftLca && rightLca) return root;

        // Otherwise, return the one that is not null
        else return (leftLca) ? leftLca : rightLca;
    }
};