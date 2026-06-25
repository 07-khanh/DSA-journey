#include "graph.h"


void dfs(vector<vector<int>>& adj, vector<bool>& visited, int s, vector<int>& res) {
    visited[s] = true;
    res.push_back(s);

    // Recursively visit all adjacent 
    // vertices that are not visited yet
    for (int i : adj[s]) {
        if (!visited[i]) {
            dfs(adj, visited, i, res);
        }
    }
}

vector<vector<int>> getComponents(vector<vector<int>>& adj) {
    int V = adj.size();
    vector<bool> visited(V, false);
    vector<vector<int>> res;

    // Loop through all vertices 
    // to handle all components
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            vector<int> component;
            dfs(adj, visited, i, component);
            res.push_back(component);
        }
    }

    return res;
}

void addEdge(vector<vector<int>>& adj, int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
}

