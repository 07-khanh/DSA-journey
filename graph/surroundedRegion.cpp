#include "graph.h"

class Solution {
private: 
    void dfs(pair<int, int> node, vector<vector<char>>& board, vector<vector<int>>& visited) {
        int m = board.size();
        int n = board[0].size();
        auto [row, col] = node;
        visited[row][col] = 1;
        vector<pair<int, int>> dirs = {
            {1, 0}, {-1, 0}, {0, 1}, {0, -1}
        };

        for (auto [x, y] : dirs) {
            int nrow = row + x;
            int ncol = col + y;

            if (nrow >= 0 && ncol >= 0 && nrow < m && ncol < n && !visited[nrow][ncol] && board[nrow][ncol] == 'O') {
                dfs({nrow, ncol}, board, visited);
            }
        }
    }
public:
    void solve(vector<vector<char>>& board) {
        int m = board.size();
        int n = board[0].size();
        vector<vector<int>> visited(m, vector<int>(n, 0));

        for (int i{0}; i < n; ++i) {
            if (board[0][i] == 'O')
                dfs({0, i}, board, visited);
            if (board[m-1][i] == 'O') 
                dfs({m-1, i}, board, visited);
        }
        for (int i{0}; i < m; ++i) {
            if (board[i][0] == 'O')
                dfs({i, 0}, board, visited);
            if (board[i][n-1] == 'O') 
                dfs({i, n-1}, board, visited);
        }

        for (int i{0}; i < m; ++i) {
            for (int j{0}; j < n; ++j) {
                if (board[i][j] == 'O' && !visited[i][j])
                    board[i][j] = 'X';
            }
        }
    }
};