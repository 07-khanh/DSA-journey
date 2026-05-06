#include <iostream>
#include <vector>
using namespace std;

/*
Problem:
Given a row-wise sorted matrix mat[][] of size n*m, where the number of rows and columns is always odd. 
Return the median of the matrix.

APPROACH: Binary search on answer.
*/
class Solution {
    int median(vector<vector<int>> &mat) {
        // code here
        int m = mat.size();
        int n = mat[0].size();
        int half = (m*n)/2;
        
        int low = mat[0][0];
        int high = mat[0][n-1];

        // Search space will be from smallest to largest element
        for (int i{0}; i < m; ++i) {
            low = min(low, mat[i][0]);
            high = max(high, mat[i][n-1]);
        } 
        
        while (low <= high) {
            int mid = low + (high-low)/2;
            
            int count = 0;

            // Count number of elements <= mid
            for (int i{0}; i < m; ++i) {
                count += (upper_bound(mat[i].begin(), mat[i].end(), mid)-mat[i].begin());
            }

            // if count > half, mid has > half elements <= to it, thus could be the median, 
            // but we will find for a even smaller element that also has count > half.
            if (count > half)
                high = mid-1;
            
            // if count < half -> absolutely not median
            else
                low = mid+1;
        }

        // low will be the first element having > half (half+1) elements <= low.
        return low;
    }
};

