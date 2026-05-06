#include <iostream>
#include <vector>
using namespace std;

/*
Problem: 
Write an efficient algorithm that searches for a value target in an m x n integer matrix matrix. This matrix has the following properties:
Integers in each row are sorted in ascending from left to right.
Integers in each column are sorted in ascending from top to bottom.

APPROACH: Search from top-right or bottom-left corner -> can always eliminate one row or one column by comparing the current cell with target.
- Time complexity: O(m+n)
*/

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();

        int r = 0;
        int c = n-1;

        while (r < m && c >= 0) {
            if (matrix[r][c] == target) return true;
            if (matrix[r][c] > target)
                --c;
            else   
                ++r;
        }
        return false;
    }
};