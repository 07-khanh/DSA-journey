#include <iostream>
#include <queue>
#include <map>
#include <set>
using namespace std;


/*
Problem:
Given the root of a binary tree, calculate the vertical order traversal of the binary tree.
For each node at position (row, col), its left and right children will be at positions (row + 1, col - 1) and (row + 1, col + 1) respectively. The root of the tree is at (0, 0).
The vertical order traversal of a binary tree is a list of top-to-bottom orderings for each column index starting from the leftmost column and ending on the rightmost column. 
There may be multiple nodes in the same row and same column. In such a case, sort these nodes by their values.
Return the vertical order traversal of the binary tree. 

APPROACH 1: Using <map> and <multiset>

APPROACH 2: Using <tuple> 
*/


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


// ==============================
// APPROACH 1: Using <map> and <multiset> - O(nlogn)
// ==============================
class Solution {
public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {

        // <map> and <multiset> automatically sort elements
        // <multiset> allows for duplicates
        map<int, map<int, multiset<int>>> vertical;

        queue<pair<TreeNode*, pair<int, int>>> q;
        q.push({root, {0, 0}});

        while (!q.empty()) {
            TreeNode* node = q.front().first;
            auto [row, col] = q.front().second;
            q.pop();

            vertical[col][row].insert(node->val);

            if (node->left)
                q.push({node->left, {row+1, col-1}});
            if (node->right)
                q.push({node->right, {row+1, col+1}});
        }

        vector<vector<int>> ans;
        for (auto p1 : vertical) {
            vector<int> col;
            for (auto p2 : p1.second)
                col.insert(col.end(), p2.second.begin(), p2.second.end());
            ans.push_back(col);
        }
        return ans;
    }
};

// ==============================
// APPROACH 2: Using <tuple> - O(nlogn)
// ==============================

class Solution {
private:
    void dfs(TreeNode* node, int row, int col, vector<tuple<int, int, int>>& nodes) {
        if (node == nullptr) return;
        
        nodes.push_back({col, row, node->val});
        dfs(node->left, row+1, col-1, nodes);
        dfs(node->right, row+1, col+1, nodes);
    }
public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        vector<tuple<int, int, int>> nodes;

        // Traverse by DFS and store nodes in 'nodes'
        dfs(root, 0, 0, nodes);

        // Sort separately using <tuple>'s default comparison
        sort(nodes.begin(), nodes.end());

        vector<vector<int>> ans;
        int prev;

        for (auto [col, row, val] : nodes) {
            // Group nodes by columns
            if (ans.empty() || col != prev) {  
                ans.push_back({});
                prev = col;
            }
            ans.back().push_back(val);
        }
        return ans;    
    }
};