#include <iostream>
#include <vector>
using namespace std;

/*
Problem:
A peak element in a 2D grid is an element that is strictly greater than all of its adjacent neighbors to the left, right, top, and bottom.
Given a 0-indexed m x n matrix mat where no two adjacent cells are equal, find any peak element mat[i][j] and return the length 2 array [i,j].
You may assume that the entire matrix is surrounded by an outer perimeter with the value -1 in each cell.
You must write an algorithm that runs in O(m log(n)) or O(n log(m)) time.
*/
class Solution {
public:
    vector<int> findPeakGrid(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();

        int low = 0;
        int high = n-1;

        while (low <= high) {
            int mid = low + (high-low)/2;
            int maxi;
            int maxNum = -1;

            // Find max of current column
            for (int i{0}; i < m; ++i) {
                if (mat[i][mid] > maxNum) {
                    maxNum = mat[i][mid];
                    maxi = i;
                }
            }

            int left = (mid > 0) ? mat[maxi][mid-1] : -1;
            int right = (mid < n-1) ? mat[maxi][mid+1] : -1;

            // If the current max is larger than its left and right neighbors -> peak
            if (mat[maxi][mid] > left && mat[maxi][mid] > right) return {maxi, mid};

            // Move left if left neighbor is larger
            if (mat[maxi][mid] < left) {
                high = mid-1;
            }

            // Move right if right neighbor is larger
            else 
                low = mid+1;
        }
        return {-1, -1};
    }
};