#include "graph.h"

// https://leetcode.com/problems/find-eventual-safe-states/submissions/1928503663/

class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int V = graph.size();
        queue<int> q;
        vector<vector<int>> reverseGraph(V);
        vector<int> result;
        vector<int> inDegree(V, 0);
        vector<int> safe(V, 0);

        for (int i{0}; i < V; ++i) {
            for (int x : graph[i]) {
                reverseGraph[x].push_back(i);
                inDegree[i]++;
            }
        }

        for (int i{}; i < V; ++i) {
            if (inDegree[i] == 0)
                q.push(i);
        }

        while (!q.empty()) {
            int node = q.front();
            safe[node] = 1;
            q.pop();

            for (int x : reverseGraph[node]) {
                --inDegree[x];
                if (inDegree[x] == 0)
                    q.push(x);
            }
        }

        for (int i{0}; i < V; ++i) {
            if (safe[i])
                result.push_back(i);
        }
        return result;
    }
};