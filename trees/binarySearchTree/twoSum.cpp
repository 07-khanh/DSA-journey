#include <iostream>
#include <stack>
#include <vector>
#include <unordered_set>
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
Problem: Given the root of a binary search tree and an integer k, 
return true if there exist two elements in the BST such that their sum is equal to k, or false otherwise.

APPROACH 1: Hashset
APPROACH 2: Two stacks
*/

//========================
// APPROACH 1: Hash set
// While traversing the tree, use Hashset to store vals we have seen, and check if k-current val is in the set.
// If yes, we have found the pair
// -> Use normal dfs, work on any BT, not using BST order

// - TC: O(n)
// - SC: O(n)
//========================

class Solution1 {
private:
    bool dfs(Node* root, int k, unordered_set<int>& nodes) {
        if (!root) return false;
        
        if (nodes.count(k-root->data)) return true;
        nodes.insert(root->data);
        return dfs(root->left, k, nodes) || dfs(root->right, k, nodes); 
    }

public:
    bool findTarget(Node* root, int k) {
        unordered_set<int> nodes;
        return dfs(root, k, nodes);
    }
};

//========================
// APPROACH 2: Two sum using two stacks
// Maintain two stacks to perform a concurrent In-order and Reverse In-order traversal
// Popping from left stack when sum is too small and popping from right stack when sum is too large

//- TC: O(n)
//- SC: O(h) -> Optimized
//========================

class Solution2 {
public:
    bool findTarget(Node* root, int k) {
        stack<Node*> st1;
        stack<Node*> st2;

        Node* cur1 = root;
        Node* cur2 = root;

        while (true) {
            // Inorder traversal
            while (cur1) {
                st1.push(cur1);
                cur1 = cur1->left;
            }
            // Reverse inorder traversal
            while (cur2) {
                st2.push(cur2);
                cur2 = cur2->right;
            }
            if (st1.empty() || st2.empty()) break;

            Node* node1 = st1.top();
            Node* node2 = st2.top();

            // Termination condition: Two pointers meet
            if (node1 == node2) break;

            int sum = node1->data + node2->data;
            if (sum == k) 
                return true;
            else if (sum > k) {
                // If sum too large, pop from st2 -> reduce sum
                st2.pop();
                cur2 = node2->left;
            }
            else {
                // If sum too small, pop from st1 -> increase sum
                st1.pop();
                cur1 = node1->right;
            }
        }
        return false;
    }
};