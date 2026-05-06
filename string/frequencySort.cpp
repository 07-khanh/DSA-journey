#include <string>
#include <unordered_map>
#include <map>
using namespace std;

/* 
Problem:
Given a string s, sort it in decreasing order based on the frequency of the characters. The frequency of a character is the number of times it appears in the string.
Return the sorted string. If there are multiple answers, return any of them.

Solution: 
- Time: O(nlogn)
- Space: O(n)
- Can replace multimap and sort by keeping in heap (priority_queue)-> still O(nlogn)
*/

class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char, int> mp;
        for (char c : s) mp[c]++;
        multimap<int, char, greater<int>> freq;
        for (auto p : mp) 
            freq.insert({p.second, p.first});
        

        string res;
        for (auto [i, c] : freq) {
            if (i == 0) break;
            res += string(i, c);
        }
        return res;
    }
};