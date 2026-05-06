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
public:
    bool isSameTree(Node* p, Node* q) {
        if (!p && !q) return true;

        if (p && q && p->data == q->data)
            return (isSameTree(p->left, q->left) 
                && isSameTree(p->right, q->right));
        return false;
    }
};