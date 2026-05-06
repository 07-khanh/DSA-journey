#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
Problem:
You are given a string s. You can convert s to a palindrome by adding characters in front of it.
Return the shortest palindrome you can find by performing this transformation.

APPROACH: Finding the longest palindromic prefix using KMP
- Time: O(n)
- Space: O(n)
*/

class Solution {
private:
    vector<int> kmp(string p) {
        int P = p.size();
        vector<int> pi(P, 0);
        for (int i{1}; i < P; ++i) {
            int j = pi[i-1];
            while (j > 0 && p[i] != p[j]) 
                j = pi[j-1];
            if (p[i] == p[j])
                ++j;
            pi[i] = j;
        }
        return pi;
    }

public:
    string shortestPalindrome(string s) {
        int n = s.size();
        string rev = s;
        reverse(rev.begin(), rev.end());
        string t = s + '#' + rev;
        vector<int> pi = kmp(t);
        return rev.substr(0, n-pi.back()) + s;
    }
};