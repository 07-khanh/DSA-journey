#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <utility>
using namespace std;

//======================
// NODE STRUCTURE
//======================

struct Node {
    int data;
    Node* left;
    Node* right;
    int height;

    Node() : data(0), left(nullptr), right(nullptr), height(1) {}
    Node(int x) : data(x), left(nullptr), right(nullptr), height(1) {}
    Node(int x, Node *left, Node *right, int height) : data(x), left(left), right(right), height(height) {}
};

int getHeight(Node* n) {
    return n ? n->height : 0;
}

int getBalance(Node* n) {
    return n? getHeight(n->left) - getHeight(n->right) : 0;
}

Node* rightRotate(Node* root) {
    Node* newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    newRoot->height = 1 + max(getHeight(newRoot->left), getHeight(newRoot->right));

    return newRoot;
}

Node* leftRotate(Node* root) {
    Node* newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    newRoot->height = 1 + max(getHeight(newRoot->left), getHeight(newRoot->right));

    return newRoot;
}

Node* insertNode(Node* node, int key) {

    // Insert node
    if (!node) return new Node(key);

    if (node->data > key)
        node->left = insertNode(node->left, key);
    else if (node->data < key)
        node->right = insertNode(node->right, key);
    else
        return node;

    // Update ancestors' height
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);

    // LL
    if (balance > 1 && key < node->left->data) 
        return rightRotate(node);
    // RR
    else if (balance < -1 && key > node->right->data)
        return leftRotate(node);
    // LR
    else if (balance > 1 && key > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node); 
    }
    // RL
    else if (balance < -1 && key < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

Node* deleteNode(Node* node, int key) {
    if (!node) return node;

    if (node->data > key)
        node->left = deleteNode(node->left, key);
    else if (node->data < key)
        node->right = deleteNode(node->right, key);
    else {
        if (!node->right) {
            Node* temp = node->left;
            delete node;
            return temp;
        }
        else if (!node->left) {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        else {
            Node* suc = node->right;
            while (suc->left)
                suc = suc->left;
            node->data = suc->data;
            node->right = deleteNode(node->right, suc->data);
        } 
    }

    if (node == nullptr)
        return node;

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);

    if (balance > 1) {
        if (getBalance(node->left) >= 0)
            return rightRotate(node);
        else {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }
    else if (balance < -1) {
        if (getBalance(node->right) <= 0)
            return leftRotate(node);
        else {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }

    return node;
}
