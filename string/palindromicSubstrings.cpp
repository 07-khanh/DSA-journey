#include <iostream>
#include <string>
#include <vector>
using namespace std;

int countSubstrings(string s) {
        int n = s.size();
        int count{0};
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int i{n-1}; i >= 0; --i) {
            for (int j{i}; j < n; ++j) {
                if (s[i] == s[j]) {
                    if (j - i < 3 || dp[i+1][j-1]) {
                        dp[i][j] = 1;
                        ++count;
                    }
                }
            }
        }
        return count;
    }

int main() {
    string s  = "fdsklf";
    cout << countSubstrings(s);
}