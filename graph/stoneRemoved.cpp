#include "graph.h"

// https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/submissions/1935492119/

class Solution {
    void dfs(int stone, vector<int>& connect, vector<vector<int>>& stones) {
        connect[stone] = 1;
        for (int i{0}; i < stones.size(); ++i) {
            if (!connect[i] 
                && (stones[stone][0] == stones[i][0] || stones[stone][1] == stones[i][1]))
                dfs(i, connect, stones);
        }
    }
public:
    int removeStones(vector<vector<int>>& stones) {
        vector<int> connect(stones.size(), 0);
        int count{0};
        for (int i{0}; i < stones.size(); ++i) {
            if (!connect[i]) {
                count++;
                dfs(i, connect, stones);
            }
        }
        return stones.size() - count;
    }
};