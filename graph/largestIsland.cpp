#include "graph.h"

/* You are given an n x n binary matrix grid. You are allowed to change at most one 0 to be 1.
Return the size of the largest island in grid after applying this operation.
An island is a 4-directionally connected group of 1s.
*/
class Solution {
private:
    unordered_map<int, int> componentColor;
    vector<pair<int, int>> dirs = {
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}
    };

    void paint(int r, int c, vector<vector<int>>& grid, int color) {
        grid[r][c] = color;
        componentColor[color]++;

        for (auto[x, y] : dirs) {
            int row = r + x;
            int col = c + y;

            if (row >= 0 && col >= 0 && row < grid.size() && col < grid.size() && grid[row][col] == 1)
                paint(row, col, grid, color);
        }
    }

public:
    int largestIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        int color{2};
        
        int ans{1};
        for (int i{0}; i < n; ++i) {
            for (int j{0}; j < n; ++j) {
                if (grid[i][j] == 1) {
                    paint(i, j, grid, color++);
                    ans = max(ans, componentColor[color-1]);
                }
            }
        }



        for (int i{0}; i < n; ++i) {
            for (int j{0}; j < n; ++j) {
                if (grid[i][j] == 0) {
                    unordered_set<int> neiColor;
                    int count{1};

                    for (auto[x, y] : dirs) {
                        int row = i + x;
                        int col = j + y;

                        if (row >= 0 && col >= 0 && row < grid.size() && col < grid.size() 
                            && grid[row][col] != 0 && neiColor.find(grid[row][col]) == neiColor.end()) {
                            count += componentColor[grid[row][col]];
                            neiColor.insert(grid[row][col]);
                        }
                    }

                    ans = max(ans, count);
                }   
            }
        }
        return ans;
    }
};