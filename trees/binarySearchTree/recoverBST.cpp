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
Problem: You are given the root of a binary search tree (BST), where the values of exactly two nodes of the tree were swapped by mistake. 
Recover the tree without changing its structure.

APPROACH 1: Inorder traversal using recursion
APPROACH 2: Morris traversal
- Both approaches make use the property of inorder traversal, in which the nodes are sorted.
=> Keep track of the first and the second violation in order
=> Those two nodes are the swapped nodes
*/

//=============================
//APPROACH 1: Inorder traversal using recursion
//- TC: O(n)
//- SC: O(n) - call stack
//=============================
class Solution1 {
public:
    Node* first = nullptr;
    Node* last = nullptr;
    Node* prev = nullptr;

    void inorder(Node* root) {
        if (!root) return;
        inorder(root->left);
        
        if (prev && root->data < prev->data) {
            if (!first) first = prev;
            last = root;
        }
        prev = root;

        inorder(root->right);
    }
    void recoverTree(Node* root) {
        inorder(root);
        swap(first->data, last->data);
    }
};

//=============================
//APPROACH 2: Inorder traversal using Morris traversal
//- TC: O(n)
//- SC: O(1) -> Optimized
//=============================

class Solution2 {
private:
    void update(Node* prev, Node* cur, Node*& first, Node*& last) {
        if (prev && cur->data < prev->data) {
            if (!first)
                first = prev;
            last = cur;
        }
    }
public:
    void recoverTree(Node* root) {
        Node* cur = root;
        Node* first = nullptr;
        Node* last = nullptr;
        Node* prev = nullptr;
        while (cur) {
            if (!cur->left) {
                // Visit node ->check for violation
                update(prev, cur, first, last);

                // Update prev
                prev = cur;
                cur = cur->right;
            }
            else  {
                // Find inorder predecessor
                Node* pred =cur->left;
                while (pred->right && pred->right != cur) 
                    pred = pred->right;

                if (!pred->right) {
                    // Create thread
                    pred->right = cur;
                    cur = cur->left;
                }
                else {
                    // Remove thread
                    pred->right = nullptr;

                    // Visit node ->check for violation
                    update(prev, cur, first, last);

                     // Update prev
                    prev = cur;
                    cur = cur->right;
                }
            }
        }
        if (first && last) 
            swap(first->data, last->data);
    }
};