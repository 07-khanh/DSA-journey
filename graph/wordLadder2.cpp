#include "graph.h"

class Solution {
private:
    unordered_map<string, unordered_set<string>> predecessors;
    vector<vector<string>> result;

    void buildPath(vector<string>& currentPath, const string& beginWord, const string& currentWord) {
        if (currentWord == beginWord) {
            vector<string> completePath(currentPath.rbegin(), currentPath.rend());
            result.push_back(completePath);
            return;
        }

        for (const string& s : predecessors[currentWord]) {
            currentPath.push_back(s);
            buildPath(currentPath, beginWord, s);
            currentPath.pop_back();
        }
    }

public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> wordSet(wordList.begin(), wordList.end());
        if (wordSet.find(endWord) == wordSet.end()) return {};

        queue<string> q;
        q.push(beginWord);
        if (wordSet.count(beginWord)) wordSet.erase(beginWord);

        bool found = false;

        while (!q.empty() && !found) {
            int level_size = q.size();
            unordered_set<string> visited_this_level;

            for (int i = 0; i < level_size; ++i) {
                string word = q.front();
                q.pop();

                string original = word;
                for (int k = 0; k < word.size(); ++k) {
                    char original_char = word[k];
                    for (char c = 'a'; c <= 'z'; ++c) {
                        word[k] = c;

                        if (wordSet.count(word)) {
                            // If it's a word we haven't expanded into a deeper level yet
                            if (visited_this_level.find(word) == visited_this_level.end()) {
                                visited_this_level.insert(word);
                                q.push(word);
                            }
                            // Crucial: Always map the predecessor link for ALL valid level matches
                            predecessors[word].insert(original);

                            if (word == endWord) {
                                found = true;
                            }
                        }
                    }
                    word[k] = original_char; // Restore
                }
            }

            // Clean up the main word pool ONLY after finishing the current level
            for (const string& w : visited_this_level) {
                wordSet.erase(w);
            }
        }

        if (found) {
            vector<string> currentPath;
            currentPath.push_back(endWord);
            buildPath(currentPath, beginWord, endWord);
        }
        return result;
    }
};