#include "graph.h"

class Solution {
private:
    bool dfs(int node, int col, vector<int>& colors, vector<vector<int>>& graph) {
        colors[node] = col;
        for (int x : graph[node]) {
            if (colors[x] == 0) {
                if (!dfs(x, -col, colors, graph)) return false;
            }
            else if (colors[x] == col)
                return false;
        }
        return true;
    }
public:
    bool isBipartite(vector<vector<int>>& graph) {
        int size = graph.size();
        vector<int> colors(size, 0);
        for (int i{0}; i < size; ++i) {
            if (colors[i] == 0)
                if (!dfs(i, 1, colors, graph))
                    return false;
        }
        return true;
    }
};