#include <string>
#include <sstream>
using namespace std;

/*
Problem: 
Given an input string s, reverse the order of the words.
A word is defined as a sequence of non-space characters. The words in s will be separated by at least one space.
Return a string of the words in reverse order concatenated by a single space.
Note that s may contain leading or trailing spaces or multiple spaces between two words. 
The returned string should only have a single space separating the words. Do not include any extra spaces.

Approach 1: Using stringstream to tokenize string, store words in a string vector.
- Time: O(n)
- Space: O(n)
- Waste more space, but clearer and easier to understand

Approach 2: Two pointers, loop in reverse
- Time : O(n)
- Space: O(n) - just the result string

Approach 3: Two pointers, in-place
-Time: O(n)
-Space: O(1) -> in-place
- More difficult to understand
*/


// =======================
// Approach 1: Using stringstream
// =======================
class Solution {
public:
    string reverseWords(string s) {
        vector<string> tokens;
        stringstream ss(s);

        string token;
        while (ss >> token) {
            tokens.push_back(token);
        }
        string res;
        for (auto pos = tokens.rbegin(); pos != tokens.rend(); pos++) {
            res += *pos;
            // If not the last word, add space
            if (pos < tokens.rend()-1)
                res += " ";
        }
        return res;
    }
};

// =======================
// Approach 2: Two pointers, loop in reverse, extra result string 
// =======================
class Solution {
public:
    string reverseWords(string s) {
        int n = s.size();
        string res;
        int i{n-1};

        while (i >= 0) {
            // Skip trailing spaces
            while (i >= 0 && s[i] == ' ')
                --i;

            // Break early if having proccessed the entire string
            if (i < 0) break;

            // Mark the end of word
            int j = i;

            // Extract word
            while (i >= 0 && s[i] != ' ')
                --i;
            string word = s.substr(i+1, j-i);

            // Add leading space if not the first word in result string, and then append the word to result.
            if (!res.empty()) res += ' ';
            res += word;
            
        }
        return res;
    }
};


// =======================
// Approach 3: Two pointers, in-place 
// =======================
class Solution {
public:
    string reverseWords(string s) {
        int n = s.size();
        reverse(s.begin(), s.end());

        // Write pointers
        int left = 0;
        int right = 0;

        // Read pointer
        int i = 0;

        while (i < n) {
            // Skip leading spaces in reversed string
            while (i < n && s[i] == ' ')
                i++;
            
            // Break early if having proccessed the entire string
            if (i == n) break;

            // Write reversed word in-place and then reverse the word
            while (i < n && s[i] != ' ') {
                s[right++] = s[i++];
            }
            reverse(s.begin() + left, s.begin() + right);


            s[right++] = ' ';
            left = right;
            i++;
        }

        // 'right' is the size of result string + 1 (including the extra space at the end)
        s.resize(right-1);
        return s;
    }
};