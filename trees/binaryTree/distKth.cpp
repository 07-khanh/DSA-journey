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

/*
Problem:
Given the root of a binary tree, the value of a target node target, and an integer k, 
return an array of the values of all nodes that have a distance k from the target node.
You can return the answer in any order.

APPROACH 1: Turn binary tree into graph -> BFS
APPROACH 2: DFS + Backtracking
*/

//==============================
// APPROACH 1: Turning binary tree into graph
// -TC: O(n)
// -SC: O(n)
//==============================
class Solution1 {
private:
    void buildGraph(Node* root, unordered_map<int, vector<int>>& graph) {
        if (!root) return;

        if (root->left) {
            graph[root->data].push_back(root->left->data);
            graph[root->left->data].push_back(root->data);
            buildGraph(root->left, graph);
        }
        if (root->right) {
            graph[root->data].push_back(root->right->data);
            graph[root->right->data].push_back(root->data);
            buildGraph(root->right, graph);
        }
    } 
public:
    vector<int> distanceK(Node* root, Node* target, int k) {
        if (k == 0) return {target->data};

        unordered_map<int, vector<int>> graph;
        buildGraph(root, graph);

        queue<int> q;
        unordered_set<int> visited;
        visited.insert(target->data);

        q.push(target->data);

        vector<int> res;

        while (!q.empty() && k >= 0) {
            int n = q.size();
            for (int i{0}; i < n; ++i) {
                int node = q.front();
                q.pop();

                if (k == 0) 
                    res.push_back(node);
                else 
                    for (int x : graph[node]) 
                        if (!visited.count(x)) {
                            q.push(x);
                            visited.insert(x);
                        }
            }
            --k;
        }
        return res;
    }
};

//==============================
// APPROACH 2: DFS + Backtracking
// -TC: O(n)
// -SC: O(h)
//==============================

class Solution2 {
private:
    // Helper to find nodes at distance 'k' in a subtree
    void findKthDown(Node* root, int k, vector<int>& res) {
        if (!root || k < 0) return;

        if (k == 0) res.push_back(root->data);

        findKthDown(root->left, k-1, res);
        findKthDown(root->right, k-1, res);
    }
    
    // Returns distance of 'target' from 'root'. Returns -1 if not found.
    int backtrack(Node* root, Node* target, int k, vector<int>& res) {
        if (!root) return -1;

        // If at target, search down the kth depth in target's subtree
        if (root == target) {
            findKthDown(root, k, res);
            // distance of direct parent to target
            return 1;
        }
        
        // Search left subtree
        int dl = backtrack(root->left, target, k, res);
        // If target is in left subtree
        if (dl != -1) {
            // If current node has dist k from target, add it to result
            if (dl == k)
                res.push_back(root->data);
            // Else find in right subtree, now the depth desired is k-(dl+1)
            else findKthDown(root->right, k-dl-1, res);
            // Increment dist (go to next dist)
            return dl+1;
        }

        // Search right subtree
        int dr = backtrack(root->right, target, k, res);
         // If target is in right subtree
        if (dr != -1) {
            // If current node has dist k from target, add it to result
            if (dr == k)
                res.push_back(root->data);
            // Else find in left subtree, now the depth desired is k-(dr+1)
            else findKthDown(root->left, k-dr-1, res);
            // Increment dist (go to next dist)
            return dr+1;
        }

        // If both subtrees don't have target
        return -1;
    }
public:
    vector<int> distanceK(Node* root, Node* target, int k) {
        if (k == 0) return {target->data};
        vector<int>res;
        backtrack(root, target, k, res);
        return res;
    }
};

