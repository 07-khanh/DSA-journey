#include <string>
#include <stack>
using namespace std;

/*
Problem:
A valid parentheses string is either empty "", "(" + A + ")", or A + B, where A and B are valid parentheses strings, and + represents string concatenation.
For example, "", "()", "(())()", and "(()(()))" are all valid parentheses strings.
A valid parentheses string s is primitive if it is nonempty, and there does not exist a way to split it into s = A + B, with A and B nonempty valid parentheses strings.
Given a valid parentheses string s, consider its primitive decomposition: s = P1 + P2 + ... + Pk, where Pi are primitive valid parentheses strings.
Return s after removing the outermost parentheses of every primitive string in the primitive decomposition of s.

Approach 1: Using stack to keep track of primitive parentheses string
- Time: O(n)
- Space: O(n)

Approach 2: Using a counter 'balance' (Optimized)
- Time; O(n)
- Space: O(1)
*/


// =======================
// Approach 1: Keep track using stack
// =======================
class Solution_With_Stack {
public:
    string removeOuterParentheses(string s) {
        int n = s.size();
        stack<int> st;
        string res;

        // Loop over the string and skip adding char to result when at outermost level (stack is empty)
        for (int i{0}; i < n; ++i) {
            if (s[i] == '(') {
                if (!st.empty())
                    res += s[i];
                st.push(i);
            }
            else {
                st.pop();
                if (!st.empty()) {
                    res += s[i];
                }
            }
        }
        return res;
    }
};


// =======================
// Approach 2: Keep track using a counter 'balance' 
// =======================
class Solution_Optimized {
public:
    string removeOuterParentheses(string s) {
        int n = s.size();
        string res;
        int balance{0};

         // Loop over the string and skip adding char to result when at outermost level (balance = 0)
        for (int i{0}; i < n; ++i) {
            if (s[i] == '(') {
                if (balance > 0) {
                    res += s[i];
                }
                balance++;
            }
            else {
                balance--;
                if (balance > 0)
                    res += s[i];
            }
        }
        return res;
    }
};

