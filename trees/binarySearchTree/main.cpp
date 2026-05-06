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

void inorderTreeWalk(Node* root) {
    if (root != nullptr) {
        inorderTreeWalk(root->left);
        cout << root->data << " ";
        inorderTreeWalk(root->right);
    }
}

Node* search(Node* root, int key) {
    if (root == nullptr || root->data == key)
        return root;

    if (root->data > key)
        return search(root->left, key);

    return search(root->right, key);
}

// Maximum key is always at rightmost node
int maxVal(Node* root) {
    if (!root) return -1;

    int x;
    while (root->right != nullptr)
        x = root->data;
    return x;
}

// Minimum key is always at leftmost node
int minVal(Node* root) {
    if (!root) return -1; 

    int x;
    while (root->left != nullptr)
        x = root->data;
    return x;
}

// Finding predecessor of key
Node* findPredecessor(Node* root, int key) {
    Node* predecessor = nullptr;

    while (root) {
        if (key > root->data) {
            
            // potential predecessor
            predecessor = root;
            
            // look for larger predecessors
            root = root->right;
        } 
        else {
            root = root->left;
        }
    }
    return predecessor;
}

// Finding successor of key
Node* findSuccessor(Node* root, int key) {
    Node* successor = nullptr;

    while (root) {
        if (key < root->data) {
            
            // potential successor
            successor = root;
            
            // look for smaller successor
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return successor;
}



int findCeil(Node* root, int key) {
    int ceil = -1;
    while (root) {
        if (root->data == key)
            return root->data;

        if (key < root->data) {
            ceil = root->data;
            root = root->left;
        }
        else
            root = root->right;   
    }
    return ceil;
}

int findFloor(Node* root, int key) {
    int floor = -1;
    while (root) {
        if (root->data == key)
            return root->data;

        if (key < root->data) 
            root = root->left;
        else {
            floor = root->data;
            root = root->right;   
        }
    }
    return floor;
} 

// =================================
// INSERTION
// =================================

Node* insertNode(Node* root, int val) {
    Node* node = new Node(val);

    if (root == nullptr) return node;

    Node* cur = root;
    while (cur) {
        if (val <= cur->data) {
            if (cur->left)
                cur = cur->left;
            else {
                cur->left = node;
                break;
            }
        }
        else {
            if (cur->right)
                cur = cur->right;
            else {
                cur->right = node;
                break;
            }
        }
    }
    return root;
} 

Node* insertRecur(Node* root, int key) {
   
    // If the tree is empty, return a new node
    if (root == nullptr)
        return new Node(key);

    // Otherwise, recur down the tree
    if (key < root->data)
        root->left = insertRecur(root->left, key);
    else
        root->right = insertRecur(root->right, key);

    // Return the (unchanged) node pointer
    return root;
}

// =================================
// DELETION
// =================================

// APPROACH 1: Recursion

Node* getSuccessor(Node* root) {
    root = root->right;
    while (root && root->left)
        root = root->left;
    return root;
}

Node* deleteNode(Node* root, int key) {
    if (root == nullptr) 
        return root; 

    // Find key
    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        // Node with 0 or 1 subtree
        if (root->left == nullptr) {
            // Connect node's parent with right subtree
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            // Connect node's parent with left subtree
            Node* temp = root->left;
            delete root;
            return temp;
        }
        else {
            // Node with 2 children
            Node* succ = getSuccessor(root);
            // Replace root node's data with its successor's.
            root->data = succ->data;
            // Recursively delete the 'old' successor node
            root->right = deleteNode(root->right, succ->data);
        }
    }
    return root;
}





