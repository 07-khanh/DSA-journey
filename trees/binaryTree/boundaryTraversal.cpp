#include <iostream>
#include <stack>
#include <vector>
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
    bool isLeaf(Node* node) {
        return (!node->left && !node->right);
    }
    
    void collectLeft(Node* root, vector<int>& res) {
        if (root == nullptr) return;
        
        if (!isLeaf(root)) {
            res.push_back(root->data);
    
            if (root->left)
                collectLeft(root->left, res);
            else
                collectLeft(root->right, res);
        }
    }
    
    void collectLeaf(Node* root, vector<int>& res) {
        if (root == nullptr) return;
        
        if (isLeaf(root)) {
            res.push_back(root->data);
            return;
        }
        collectLeaf(root->left, res);
        collectLeaf(root->right, res);
    }
    
    void collectRight(Node* root, vector<int>& res) {
        if (root == nullptr) return;
        
        if (!isLeaf(root)) {
            if (root->right)
                collectRight(root->right, res);
            else
                collectRight(root->left, res);
            res.push_back(root->data);
        }
    }
    
    
  public:
    vector<int> boundaryTraversal(Node *root) {
        vector<int> res;
        
        if (!root) return res;
        
        if (!isLeaf(root))
            res.push_back(root->data);
            
        collectLeft(root->left, res);
        collectLeaf(root, res);
        collectRight(root->right, res);
        
        return res;
    }
};