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
public:
    // Function to find the path from root to node with value x
    bool getPath(Node* root, vector<int>& arr, int x) {
        // If current node is NULL, return false
        if (!root) {
            return false;
        }

        // Add current node's value to the path
        arr.push_back(root->data);

        // If current node's value is equal to x, return true
        if (root->data == x) {
            return true;
        }

        // Recursively search in left or right subtree
        if (getPath(root->left, arr, x) ||
            getPath(root->right, arr, x)) {
            return true;
        }

        // If not found, backtrack and remove current node
        arr.pop_back();
        return false;
    }

    // Function to get the path from root to node with value B
    vector<int> solve(Node* A, int B) {
        // Vector to store the path
        vector<int> arr;

        // If root is NULL, return empty path
        if (!A) {
            return arr;
        }

        // Call helper function to fill the path
        getPath(A, arr, B);

        // Return the resulting path
        return arr;
    }
};