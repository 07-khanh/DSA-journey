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
private:
    void inorder(Node* root, int& count, int k, int& res) {
        if (root == nullptr || count == k)
            return;
        inorder(root->left, count, k, res);
        count++;
        if (count == k)
            res = root->data;
        inorder(root->right, count, k, res);
    }

public:
    int kthSmallest(Node* root, int k) {
        int count = 0;
        int res;
        inorder(root, count, k, res);
        return res;
    }
};