#include <iostream>
#include <stack>
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

// ==================================
// APPROACH 1: Recursion
// -TC: O(n)
// -SC: O(n)
// ==================================
class Solution {
    Node* prev = nullptr;
public:
    void flatten(Node* root) {
        if (!root) return;
        flatten(root->right);
        flatten(root->left);
        root->right = prev;
        root->left = nullptr;
        prev = root;
    }
};

// ==================================
// APPROACH 2: Stack (Iterative Preorder Traversal)
// -TC: O(n)
// -SC: O(n)
// ==================================

class Solution {
public:
    void flatten(Node* root) {
        if (!root) return;
        stack<Node*> st;
        st.push(root);

        while (!st.empty()) {
            Node* node = st.top();
            st.pop();

            if (node->right)
                st.push(node->right);
            if (node->left)
                st.push(node->left);

            if (!st.empty())
                node->right = st.top();
            node->left = nullptr;
        }
    }
};

// ==================================
// APPROACH 3: Morris-like Traversal
// -TC: O(n)
// -SC: O(1)
// ==================================
class Solution {
public:
    void flatten(Node* root) {
        Node* cur = root;

        while (cur) {
            if (cur->left) {
                Node* rightmost = cur->left;
                while (rightmost->right)
                    rightmost = rightmost->right;
                rightmost->right = cur->right;
                cur->right = cur->left;
                cur->left = nullptr;
            }
            cur = cur->right;
        } 
    }
};