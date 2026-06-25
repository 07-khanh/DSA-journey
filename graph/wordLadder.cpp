#include "graph.h"

// https://leetcode.com/problems/word-ladder/description/

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        int size = wordList.size();
        unordered_set<string> st(wordList.begin(), wordList.end());
        queue<pair<string, int>> q;
        q.push({beginWord, 1});
        st.erase(beginWord);

        while (!q.empty()) {
            auto [s, steps] = q.front();
            q.pop();
            if (s == endWord)
                return steps;
            
            for (int i{0}; i < s.size(); ++i) {
                char original = s[i];
                for (char ch{'a'}; ch <= 'z'; ++ch) {
                    s[i] = ch;

                    if (st.find(s) != st.end()) {
                        q.push({s, steps + 1});
                        st.erase(s);
                    }
                }
                s[i] = original;
            }
        }
        return 0;
    }
};