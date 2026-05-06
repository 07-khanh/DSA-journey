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

class Solution {
public:
    Node* lowestCommonAncestor(Node* root, Node* p, Node* q) {
        if (root == nullptr) return nullptr;
        
        if (root->data > p->data && root->data > q->data)
            return lowestCommonAncestor(root->left, p, q);
        else if (root->data < p->data && root->data < q->data)
            return lowestCommonAncestor(root->right, p, q);
        else return root;
    }
};