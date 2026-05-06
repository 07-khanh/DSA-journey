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
    bool dfs(Node* root1, Node* root2) {
        if (!root1 && !root2) return true;
        else if (!root1 || !root2 || root1->data != root2->data) return false;

        return dfs(root1->left, root2->right) && dfs(root1->right, root2->left);
    }
public:
    bool isSymmetric(Node* root) {
        if (!root) return true;
        return dfs(root->left, root->right);
    }
};