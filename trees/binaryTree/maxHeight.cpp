#include <iostream>
#include <queue>
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

// Can be used to find both max height and max depth
int maxHeight(Node* root) {
    // One level under the leaf node -> height = -1
    if (root == nullptr) return -1;

    // h(node) = 1 + max( h(left), h(right))
    return 1 + max(maxHeight(root->left), maxHeight(root->right));
}

// Level order traversal -> find max depth
int maxDepth(Node* root) {
    int depth = 0;
    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();
        ++depth;

        // Traverse all nodes at the current level
        for (int i{0}; i < levelSize; ++i) {
            Node* node = q.front();
            q.pop();
            
            // Enqueue children nodes for next level
            if (node->left != nullptr)
                q.push(node->left);
            if (node->right != nullptr)
                q.push(node->right);
        }
    }

    // depth = level - 1
    return depth-1;
}

