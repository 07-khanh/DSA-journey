#include "graph.h"

// CYCLE DETECTION IN UNDIRECTED GRAPH

// ==================
// Using BFS
// ==================
class Solution1 {
    // Function to perform BFS from node 'start' to detect cycle
    bool bfs(int start, vector<vector<int>>& adj, vector<bool>& visited) {
        
        // Queue stores {current node, parent node}
        queue<pair<int, int>> q;
        
        // Start node has no parent
        q.push({start, -1});
        visited[start] = true;

        while (!q.empty()) {
            int node = q.front().first;
            int parent = q.front().second;
            q.pop();

            // Traverse all neighbors of current node
            for (int neighbor : adj[node]) {

                // If neighbor is not visited, mark it visited and push to queue
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push({neighbor, node});
                } 
                // If neighbor is visited and not parent, a cycle is detected
                else if (neighbor != parent) {
                    return true;
                }
            }
        }
        
        // No cycle found starting from this node
        return false; 
    }

    // Function to check if the undirected graph contains a cycle
    bool isCycle(vector<vector<int>>& adj) {
        
        int V= adj.size();
        
        // Keep track of visited vertices
        vector<bool> visited(V, false); 

        // Perform BFS from every unvisited node
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                
                // If BFS finds a cycle
                if (bfs(i, adj, visited)) { 
                    return true;
                }
            }
        }
        
        // If no cycle is found in any component
        return false;
    }
};

// ==================
// Using DFS
// ==================

class Solution2 {
    bool isCycle(vector<vector<int>>& adj) {
        int V= adj.size();
        
        // Keep track of visited vertices
        vector<bool> visited(V, false); 

        // Check every vertex to handle disconnected components
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                // If DFS finds a cycle
                if (dfs(i, -1, adj, visited)) { 
                    return true;
                }
            }
        }
        return false;
    } 


    bool dfs(int u, int parent, vector<vector<int>>& adj, vector<bool>& visited) {
        visited[u] = true;

        for (int v : adj[u]) {
            // Case 1: Neighbor is unvisited -> recurse deeper
            if (visited[v] == false)
                if (dfs(v, u, adj, visited))
                    return true;
                    
            // Case 2: Neighbor is visited, and it's NOT our immediate parent -> CYCLE!
            else if (v != parent)
                return true;
        }
        return false;
    }
};
