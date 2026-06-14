using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    char colour;
    Node* parent;

    Node(int data) : data(data), left(nullptr), right(nullptr), colour('R'), parent(nullptr) {};
};


Node* rotateLeft(Node* node) {
    Node* x = node->right;
    Node* y = x->left;
    x->left = node;
    node->right = y;
    node->parent = x;

    if (y != nullptr)
        y->parent = node;

    return x;
}

Node* rotateRight(Node* node) {
    Node* x = node->left;
    Node* y = x->right;
    x->right = node;
    node->left = y;
    node->parent = x;
    
    if (y != nullptr)
        y->parent = node;

    return x;
}

Node* insertHelp(Node* root, int data) {
    bool f = false;

    if (root == nullptr)
        return new Node(data);

    if (data <= root->data) {
        root->left = insertHelp(root->left, data);
        root->left->parent = root;
        
    }
    else 
        root->right = insertHelp(root->right, data);
}