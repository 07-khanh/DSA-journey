#include <iostream>
#include <map>
#include <vector>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node() : data(0), left(nullptr), right(nullptr) {}
    Node(int x) : data(x), left(nullptr), right(nullptr) {}
    Node(int x, Node *left, Node *right) : data(x), left(left), right(right) {}
};


/*
Problem: Given two integer arrays preorder and inorder where preorder is the preorder traversal of a binary tree 
and inorder is the inorder traversal of the same tree, construct and return the binary tree.
*/


// ==================================
// APPROACH 1: Using unordered map 
// - TC: O(n^2)
// - SC: 
//  + Best case: O(logn) for balanced tree
//  + Worst case: O(n) for skewed tree
// ================================== 
class Solution {
    Node* build(int i1, int i2, int j1, int j2, vector<int>& preorder, vector<int>& inorder) {
        // Base case: if the range is invalid, return null
        if (i1 > i2) return nullptr;

        // The first element in preorder is always the root of the current subtree
        Node* root = new Node(preorder[i1]);
        
        int idx = j1;
        int count = 0;
        // Find where this root sits in the inorder array - O(n)
        while (idx < inorder.size() && inorder[idx] != preorder[i1]) {
            ++idx;
            ++count;
        }
        
        // Recursive calls with updated boundaries
        root->left = build(i1+1, i1+count, j1, idx-1, preorder, inorder);
        root->right = build(i1+count+1, i2, idx+1, j2, preorder, inorder);
        return root;
    }
public:
    Node* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int m = preorder.size();
        return build(0, m-1, 0, m-1, preorder, inorder);
    }
};


// ==================================
// APPROACH 2: Using unordered map 
// - TC: O(n)
// - SC: O(n) for call stack and map
// ==================================
class Solution {
    Node* build(int i1, int i2, int j1, int j2, vector<int>& preorder, vector<int>& inorder, unordered_map<int, int>& inorderMap) {
        // Base case: if the range is invalid, return null
        if (i1 > i2 ) return nullptr;

        // The first element in preorder is always the root of the current subtree
        Node* root = new Node(preorder[i1]);
        
        // Find where this root sits in the inorder array using our map (O(1))
        int idx = inorderMap[preorder[i1]];

        // Calculate how many nodes are in the left subtree
        int count = idx-j1;
        

        // Recursive calls with updated boundaries
        root->left = build(i1+1, i1+count, j1, idx-1, preorder, inorder, inorderMap);
        root->right = build(i1+count+1, i2, idx+1, j2, preorder, inorder, inorderMap);
        return root;
    }
public:
    Node* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int m = preorder.size();
        unordered_map<int, int> inorderMap;
        for (int i{0}; i < m; ++i)
            inorderMap[inorder[i]] = i;
        return build(0, m-1, 0, m-1, preorder, inorder, inorderMap);
    }
};