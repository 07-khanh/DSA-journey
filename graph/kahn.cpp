#include "graph.h"

vector<int> topologicalSort(int V, const vector<vector<int>>& adj) {
    vector<int> in_degree(V, 0);

    // Step 1: Calculate the in-degree of every vertex
    for (int u = 0; u < V; ++u) {
        for (int v : adj[u]) {
            in_degree[v]++;
        }
    }

    // Step 2: Push all vertices with an in-degree of 0 into a queue
    queue<int> q;
    for (int i = 0; i < V; ++i) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }

    vector<int> topo_order;

    // Step 3: Process vertices
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topo_order.push_back(u);

        // Reduce the in-degree of all outgoing neighbors
        for (int v : adj[u]) {
            in_degree[v]--;

            // If in-degree becomes 0, add it to the queue
            if (in_degree[v] == 0) {
                q.push(v);
            }
        }
    }

    // Step 4: Check for cycles
    if (topo_order.size() != V) {
        return {}; // Return an empty vector if a cycle is detected
    }

    return topo_order;
}