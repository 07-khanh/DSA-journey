#include <string>
#include <vector>
using namespace std;

/* 
Problem:
The beauty of a string is the difference in frequencies between the most frequent and least frequent characters.
For example, the beauty of "abaacc" is 3 - 1 = 2.
Given a string s, return the sum of beauty of all of its substrings.

APPROACH: Keeping a frequency map and keep track of the min and max frequency for each substring.
- Time: O(n^2)
- Space: O(1) 
*/

class Solution {
public:
    int beautySum(string s) {
        int n = s.size();
        int res{0};

        for (int i{0}; i < n; ++i) {
            vector<int> freq(26, 0);

            for (int j{i}; j < n; ++j) {
                int maxFreq = 0;
                int minFreq = 501;

                freq[s[j]-'a']++;
                for (int freqi : freq) {
                    if (freqi > 0) {
                        maxFreq = max(maxFreq, freqi);
                        minFreq = min(minFreq, freqi);
                    }
                }
                res += (maxFreq-minFreq);
            }
        }
        return res;
    }
};