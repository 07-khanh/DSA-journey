#include <iostream>
#include <queue>
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
Problem: Given the root of a binary tree, return the maximum width of the given tree.
The maximum width of a tree is the maximum width among all levels.
The width of one level is defined as the length between the end-nodes (the leftmost and rightmost non-null nodes), 
where the null nodes between the end-nodes that would be present in a complete binary tree extending down to that level are also counted into the length calculation.
It is guaranteed that the answer will in the range of a 32-bit signed integer.

APPROACH: Index every node levelwise using BFS
- TC: O(n)
*/

class Solution {
public:
    int widthOfBinaryTree(Node* root) {
        queue<pair<unsigned int , Node*>> q;
        q.push({0, root});
        unsigned int maxWidth = 0;

        while (!q.empty()) {
            unsigned int n = q.size();
            unsigned int first;
            unsigned int last;
            for (int i{0}; i < n; ++i) {
                auto [idx, cur] = q.front();
                q.pop();

                if (i == 0) first = idx;
                if (i == n-1) last = idx;

                if (cur->left)
                    q.push({2*(idx-first)+1, cur->left});   // subtract by 'first' to prevent overflow
                if (cur->right)
                    q.push({2*(idx-first)+2, cur->right});  // subtract by 'first' to prevent overflow
            }
            maxWidth = max(maxWidth, last-first+1);
        }
        return maxWidth;
    }
};