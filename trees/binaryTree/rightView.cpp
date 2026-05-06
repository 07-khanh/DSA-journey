#include <iostream>
#include <queue>
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
    vector<int> rightSideView(Node* root) {
        if (!root) return {};
        vector<int> res;
        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            int n = q.size();
            for (int i{0}; i < n; ++i) {
                Node* cur = q.front();
                q.pop();

                if (i == 0) res.push_back(cur->data);

                if (cur->right)
                    q.push(cur->right);
                if (cur->left)
                    q.push(cur->left);
            }
        }
        return res;
    }
};