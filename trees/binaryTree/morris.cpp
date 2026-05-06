#include <iostream>
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
MORRIS TRAVERSAL:
APPROACH: Create threaded binary tree
- Connect node to its inorder successor
-> be able follow back up the tree

- Time complexity: O(N) 
    Each edge in the tree is traversed at most 3 times (build thread, print, remove thread)
- Space complexity: O(1) 
    Optimized compared to other traversal methods
*/


//=====================
// INORDER
//=====================
vector<int> morrisTraversal(Node* root) {
    vector<int> inorder;
    Node* cur = root;

    while (cur != nullptr) {
        if (cur->left == nullptr) {
            // No left child, visit and go right
            inorder.push_back(cur->data);
            cur = cur->right;
        }
        else {
            // Find the inorder predecessor (rightmost in left subtree)
            Node* prev = cur->left;
            while (prev->right && prev->right != cur) {
                prev = prev->right;
            }
            if (prev->right == nullptr) {
                // Create thread
                prev->right = cur;
                cur = cur->left;
            }
            else {
                // Thread already exists, left subtree is done
                prev->right = nullptr; // Restore tree
                inorder.push_back(cur->data);
                cur = cur->right;
            }
        }
    }
    return inorder;
}

//=====================
// PREORDER
//=====================
vector<int> morrisTraversal(Node* root) {
    vector<int> preorder;
    Node* cur = root;

    while (cur != nullptr) {
        if (cur->left == nullptr) {
            preorder.push_back(cur->data);
            cur = cur->right;
        }
        else {
            Node* prev = cur->left;
            while (prev->right && prev->right != cur) {
                prev = prev->right;
            }
            if (prev->right == nullptr) {
                prev->right = cur;
                // Print when node is traversed for the 1st time
                preorder.push_back(cur->data);
                cur = cur->left;
            }
            else {
                prev->right = nullptr;
                cur = cur->right;
            }
        }
    }
    return preorder;
}

