#include <string>
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

/*
Problem: Given a string s, return the longest palindromic substring in s.

APPROACH 1:  Dynamic Programming
- Time: O(n^2)
- Space: O(n^2)

APPROACH 2: Two pointers - Expand Around Center
- Time: O(n^2)
- Space: O(1) -> Space Optimization
*/


// =======================
// Approach 1: DP 
// =======================
class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        // dp[i][j] = true : there is a palindromic substring from i to j
        vector<vector<bool>> palin(n, vector<bool>(n, false));

        int start;
        int maxLen{0};

        for (int i{n-1}; i >= 0; --i) {
            for (int j{i}; j < n; ++j) {
                // Substring of length 1 -> palindromic
                if (i == j) {
                    palin[i][j] = true;
                }
                // If characters at both ends match, and there is a palindromic substring without them 
                //then we can form a longer palindromic substring.
                else if (s[i] == s[j] && (palin[i+1][j-1] || j - i < 3))
                    palin[i][j] = true;
                
                // Keep track of the longest length
                if (j-i+1 > maxLen) {
                    maxLen = j-i+1;
                    start = i;
                }
            }
        }
        return s.substr(start, maxLen); 
    }
};


// =======================
// Approach 2: Two pointers - Expand Around Center (Space Optimized)
// =======================
class Solution {
private:
    int expandAroundCenter(string s, int l, int r) {
        while (l >= 0 && r < s.size() && s[l] == s[r]) {
            --l;
            ++r;
        }
        return r-l-1;
    }
public:
    string longestPalindrome(string s) {
        int start;
        int maxLen = 0;

        for (int i{0}; i < s.size(); ++i) {
            //Odd substring has a center while even substring doesn't -> check both cases
            int odd = expandAroundCenter(s, i, i);
            int even = expandAroundCenter(s, i, i+1);

            int len = max(odd, even);
            if (len > maxLen) {
                maxLen = len;
                start = i-(len-1)/2;
            }
        }
        return s.substr(start, maxLen);
    }
};