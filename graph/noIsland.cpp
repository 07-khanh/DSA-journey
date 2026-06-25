#include "graph.h"

class Solution {
public:
    int n, m;
    void dfs(int i, int j, vector<vector<char>>& g) {
        if (i < 0 || j < 0 || i >= n || j >= m || g[i][j] == '0')
            return;
        g[i][j] = '0';
        dfs(i + 1, j, g);
        dfs(i - 1, j, g);
        dfs(i, j + 1, g);
        dfs(i, j - 1, g);
    }
    int numIslands(vector<vector<char>>& g) {
        n = g.size();
        m = g[0].size();
        int c = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (g[i][j] == '1') {
                    c++;
                    dfs(i, j, g);
                }
            }
        }
        return c;
    }
};