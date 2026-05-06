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
    int countNodes(Node* root) {
        if (!root) return 0;
        int l = 0;
        int r = 0;

        Node* leftNode = root;
        Node* rightNode = root;

        while (leftNode->left) {
            leftNode = leftNode->left;
            ++l;
        }

        while (rightNode->right) {
            rightNode = rightNode->right;
            ++r;
        }

        if (r == l) 
            return (1 << (l+1)) - 1;
        
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
};