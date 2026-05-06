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
    vector<vector<int>> zigzagLevelOrder(Node* root) {
        vector<vector<int>> result;

        if(root==NULL) return result;

        queue<Node*> nodeq;
        nodeq.push(root);

        bool lefttoright=true;

        while(!nodeq.empty()){
            int size=nodeq.size();
            vector<int> row(size);

            for(int i=0;i<size;i++){
                Node* node=nodeq.front();
                nodeq.pop();

                int index=(lefttoright)?i:(size-1-i);
                row[index]=node->data;
                
                if(node->left){
                    nodeq.push(node->left);
                }
                if(node->right){
                    nodeq.push(node->right);
                }

            }
            lefttoright=!lefttoright;
            result.push_back(row);

        }
        return result;
    }
};