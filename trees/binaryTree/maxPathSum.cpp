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
    int pathSum(Node* root, int& maxSum) {
        if (root == nullptr)    
            return 0;
        int l = max(0, pathSum(root->left, maxSum));
        int r = max(0, pathSum(root->right, maxSum));
        maxSum = max(maxSum, root->data + l + r);
        return root->data + max(l, r);
    }
public:
    int maxPathSum(Node* root) {
        int maxSum = root->data;
        pathSum(root, maxSum);
        return maxSum;
    }
};