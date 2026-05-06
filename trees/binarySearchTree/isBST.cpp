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
    bool valid(Node* root, int mini, int maxi) {
        if (!root) return true;

        if (!(root->data > mini && root->data < maxi)) return false;

        return valid(root->left, mini, root->data) 
            && valid(root->right, root->data, maxi);
    }
public:
    bool isValidBST(Node* root) {
        return valid(root, INT_MIN, INT_MAX);
    }
};