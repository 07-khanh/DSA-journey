#include <iostream>
#include <queue>
#include <map>
#include <unordered_set>
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

    // dist : distance from node to 'start' in its subtrees, return -1 if not
    // height: height of node
    struct Res {
        int dist;
        int height;
    };

    Res backtrack(Node* root, int start, int& maxi) {
        if (!root) return {-1, 0};

        // Explore left and right subtree
        Res left = backtrack(root->left, start, maxi);
        Res right = backtrack(root->right, start, maxi);

        // Default dist to be -1
        // Node's height is max height of left and right subtree + 1
        int curDist = -1;
        int curHeight = max(left.height, right.height) + 1;

        // Case 1: This node IS the infection source
        // -> Take into account the time to infect this node's subtrees
        // Distance to 'start' will be 0
        if (root->data == start) {
            maxi = max(maxi, max(left.height, right.height));
            curDist = 0;
        }   
        
        // Case 2: Infection source is in node's left subtree
        // Update distance of node to 'start'
        // Infection path: Start -> Node -> Right subtree
        if (left.dist != -1) {
            curDist = left.dist + 1;
            maxi = max(maxi, curDist + right.height);
        }
        // Case 3: Infection source is in node's right subtree
        // Update distance of node to 'start'
        // Infection path: Start -> Node -> Left subtree
        else if (right.dist != -1) {
            curDist = right.dist + 1;
            maxi = max(maxi, curDist + left.height);
        }
        return {curDist, curHeight};
    }
public:
    int amountOfTime(Node* root, int start) {
        int maxi = 0;
        backtrack(root, start, maxi);
        return maxi;
    }
};