#include <iostream>
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

class Solution {
private:
    int height(Node* root, int& diameter) {
        if (root == nullptr) return 0;

        int l = height(root->left, diameter);
        int r = height(root->right, diameter);

        diameter = max(diameter, l+r);
        return 1 + max(l, r);
    }
public:
    int diameterOfBinaryTree(Node* root) {
        int diameter = 0;
        height(root, diameter);
        return diameter;
    }
};