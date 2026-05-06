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

    Node() : data(0), left(nullptr), right(nullptr) {}
    Node(int x) : data(x), left(nullptr), right(nullptr) {}
    Node(int x, Node *left, Node *right) : data(x), left(left), right(right) {}
};

//======================
// PREORDER TRAVERSAL (Root-Left-Right)
//======================

// APPROACH 1: Recursion
void preorderRecur(Node* root) {
    if (root == nullptr)
        return;
    
    // Root
    cout << root->data << " ";

    // Left subtree
    preorderRecur(root->left);

    // Right subtree
    preorderRecur(root->right);
}

// APPROACH 2: Iterative + One stack
void preorderIter(Node* root) {
    if (root == nullptr) return;

    stack<Node*> st;
    st.push(root);

    while (!st.empty()) {
        Node* node = st.top();
        st.pop();
        cout << node -> data << " ";

        // Reverse the order (right-left) because of LIFO structure
        if (node->right != nullptr)
            st.push(node->right);
        if (node->left != nullptr)
            st.push(node->left);
    }
}

//======================
// INORDER TRAVERSAL (Left-Root-Right)
//======================

// APPROACH 1: Recursion
void inorderRecur(Node* root) {
    if (root == nullptr) 
        return;

    // Left subtree
    inorderRecur(root->left);

    // Root
    cout << root->data << " ";

    // Right subtree
    inorderRecur(root->right);
}

// APPROACH 2: Iterative + One stack
void inorderIter(Node* root) {
    if (root == nullptr) return;

    stack<Node*> st;
    Node* node = root;

    while (true) {
        if (node != nullptr) {
            st.push(node);
            // Go down the left subtree
            node = node->left;
        }
        else {
            if (st.empty())
                break;

            // Finish left subtree -> print root and go to right subtree
            node = st.top();
            st.pop();
            cout << node->data << " ";
            node = node->right;
        }
    }
}

//======================
// POSTORDER TRAVERSAL (Left-Right-Root)
//======================

// APPROACH 1: Recursion
void postorderRecur(Node* root) {
    if (root == nullptr) 
        return;
    
    // Left subtree
    postorderRecur(root->left);

    // Right subtree
    postorderRecur(root->right);

    // Root
    cout << root->data << " ";
}

// APPROACH 2: Iterative + Two stacks
// Idea: Do preorder-like traversal (Node-Right-Left)
// Then postorder will be the reverse of that (Left-Right-Node).
void postorderIter1(Node* root) {
    if (root == nullptr) return;

    stack<Node*> st1;
    stack<Node*> st2;

    st1.push(root);
    
    while (!st1.empty()) {
        Node* node = st1.top();
        st1.pop();

        st2.push(node);

        if (node->left != nullptr)
            st1.push(node->left);
        if (node->right != nullptr)
            st1.push(node->right);
    }

    while (!st2.empty()) {
        cout << st2.top()->data << " ";
        st2.pop();
    }
}

// APPROACH 3: Iterative + One stack
void postorderIter2(Node* root) {
    if (root == nullptr) return;

    stack<Node*> st;
    Node* cur = root;
    Node* lastProcessed = nullptr; // Track the node we just finished

    while (cur != nullptr || !st.empty()) {
        // Step 1: Reach the leftmost node
        if (cur != nullptr) {
            st.push(cur);
            cur = cur->left;
        } 
        else {
            Node* peekNode = st.top();
            
            // Step 2: Can we go right? 
            // We go right ONLY if a right child exists AND we haven't just processed it.
            if (peekNode->right != nullptr && lastProcessed != peekNode->right) {
                cur = peekNode->right;
            } 
            else {
                // Step 3: Backtrack/Process Node
                // Either right is null, or we just finished the right subtree.
                cout << peekNode->data << " ";
                lastProcessed = peekNode; // Mark this node as complete
                st.pop();
            }
        }
    }
}

void allTravesals(Node* root) {
    if (root == nullptr)
        return;

    vector<int> preorder;
    vector<int> inorder;
    vector<int> postorder;

    stack<pair<Node*, int>> st;
    st.push({root, 1});

    while (!st.empty()) {
        pair<Node*, int> cur = st.top();
        Node* node = cur.first;
        int state = cur.second;

        if (state == 1) {
            preorder.push_back(node->data);
            ++cur.second;

            if (node->left != nullptr)
                st.push({node->left, 1});
        }
        else if (state == 2) {
            inorder.push_back(node->data);
            ++cur.second;

            if (node->right != nullptr) 
                st.push({node->right, 1});
        }
        else if (state == 3) {
            postorder.push_back(node->data);
            st.pop();
        }
    }

    // Print results
    cout << "Preorder: "; for(int x : preorder) cout << x << " "; cout << "\n";
    cout << "Inorder: ";  for(int x : inorder) cout << x << " "; cout << "\n";
    cout << "Postorder: "; for(int x : postorder) cout << x << " "; cout << "\n";
}

//======================
// LEVEL ORDER TRAVERSAL (BFS)
//======================
vector<int> levelOrder(Node* root) {
    if (root == nullptr) return;

    queue<Node*> q;

    q.push(root);

    while (!q.empty()) {
        Node* node = q.front();
        q.pop();

       cout << node -> data << " ";

        if (node->left != nullptr)
            q.push(node->left);
        if (node->right != nullptr)
            q.push(node->right);
    }
}