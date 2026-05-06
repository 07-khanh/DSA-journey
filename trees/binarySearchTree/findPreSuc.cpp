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
You are given the root of a BST and an integer key. 
You need to find the inorder predecessor and successor of the given key. 
If either predecessor or successor is not found, then set it to NULL.

- Time complexity: O(N)
*/

class Solution {
  public:
    vector<Node*> findPreSuc(Node* root, int key) {
        Node* suc = nullptr;
        Node* pred = nullptr;
        
        Node* cur = root;
        while (cur) {
            if (cur->data > key) {
                // If data > key, set it as potential successor
                // Explore the left subtree to look for smaller successor
                suc = cur;
                cur = cur->left;
            }
            else if (cur->data < key) {
                // If data < key, set it as potential predecessor
                // Explore the right subtree to look for larger predecessor
                pred = cur;
                cur = cur->right;
            }
            else {
                // If data == key
                if (cur->left) {
                    // If cur has left subtree, predecessor will be the maximum (rightmost) node in left subtree
                    Node* maxi = cur->left;
                    while (maxi->right) {
                        maxi = maxi->right;
                    }
                    pred = maxi;
                }
                if (cur->right) {
                    // If cur has right subtree, successor will be the minimum (leftmost) node in right subtree
                    Node* mini = cur->right;
                    while (mini->left) {
                        mini = mini->left;
                    }
                    suc = mini;
                }
                break;
            }
        }
        if (!suc && !pred) return {};
        else return {pred, suc};
    }
};

