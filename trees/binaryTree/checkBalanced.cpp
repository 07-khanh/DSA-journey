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
int maxHeight(Node* root) {
    if (root == nullptr) return 0;

    int l = maxHeight(root->left);
    int r = maxHeight(root->right);

    if (l == -1 || r == -1 || (abs(l - r) > 1)) return -1;

    return 1 + max(l, r);
}
public:
    bool isBalanced(Node* root) {
        if (maxHeight(root) == -1) return false;
        return true;
    }
};