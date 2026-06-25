#include "graph.h"

// =======================
// Using DFS
// =======================

class Solution1 {
    void dfs(int node, vector<int>& visited, vector<vector<int>>& adj) {
        visited[node] = 1;
        for (int nei : adj[node]) {
            if (!visited[nei])
                dfs(nei, visited, adj);
        }
    }
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        vector<vector<int>> adj(n);

        for (int i{0}; i < n; ++i) {
            for (int j{0}; j < n; ++j) {
                if (isConnected[i][j]) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }

        int count{0};
        vector<int> visited(n, 0);
        for (int i{0}; i < n; ++i) {
            if (!visited[i]) {
                dfs(i, visited, adj);
                ++count;
            }
        }
        return count;
    }
};

// =======================
// Using DSU
// =======================

class DisjointSet {
    vector<int> parent, rank;
public:
    DisjointSet(int V) {
        rank.resize(V, 0);
        parent.resize(V);

        for(int i{0}; i < V; ++i) 
            parent[i] = i;
    }

    int find(int node) {
        if (node == parent[node])
            return node;
        return parent[node] = find(parent[node]);
    }

    void unionByRank(int u, int v) {
        int ulParent_u = find(u);
        int ulParent_v = find(v);

        if (ulParent_u == ulParent_v) return;

        if (rank[ulParent_u] < rank[ulParent_v])
            parent[ulParent_u] = ulParent_v;
        else if (rank[ulParent_u] > rank[ulParent_v])
            parent[ulParent_v] = ulParent_u;
        else {
            parent[ulParent_v] = ulParent_u;
            rank[ulParent_u]++;
        }
    }
    int countSet() {
        int count{0};
        for (int i{0}; i < parent.size(); ++i) {
            if (find(i) == i)
                ++count;
        }
        return count;
    }
};

class Solution2 {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        DisjointSet ds(n);

        for (int i{0}; i < n; ++i) {
            for (int j{0}; j < n; ++j) {
                if (isConnected[i][j])
                    ds.unionByRank(i, j);
            }
        }

        return ds.countSet();
    }
};