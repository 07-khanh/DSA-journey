#include "graph.h"

// CYCLE DETECTION IN DIRECTED GRAPH

class Solution {
    bool isCycle(vector<vector<int>>& adj) {
        int V = adj.size();

        vector<bool> visited(V, false);
        vector<bool> recurStack(V, false);

        for (int i{0}; i < V; ++i) {
            if (!visited[i]) {
                if (dfs(i, adj, visited, recurStack))
                    return true;
            }
        }
        return false;
    }

    bool dfs(int node, vector<vector<int>>& adj, vector<bool>& visited, vector<bool>& recurStack) {
        visited[node] = true;
        recurStack[node] = true;

        for (int nei : adj[node]) {
            if (!visited[nei]) {
                if (dfs(nei, adj, visited, recurStack))
                    return true;
            }
            else if (recurStack[nei])
                return true;
        }
        recurStack[node] = false;
        return false;
    }
};