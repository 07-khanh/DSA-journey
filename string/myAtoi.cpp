#include <string>
#include <iostream>
using namespace std;

/*
Problem:
Implement the myAtoi(string s) function, which converts a string to a 32-bit signed integer.

The algorithm for myAtoi(string s) is as follows:

Whitespace: Ignore any leading whitespace (" ").
Signedness: Determine the sign by checking if the next character is '-' or '+', assuming positivity if neither present.
Conversion: Read the integer by skipping leading zeros until a non-digit character is encountered or the end of the string is reached. If no digits were read, then the result is 0.
Rounding: If the integer is out of the 32-bit signed integer range [-231, 231 - 1], then round the integer to remain in the range. Specifically, integers less than -231 should be rounded to -231, and integers greater than 231 - 1 should be rounded to 231 - 1.
Return the integer as the final result.

*/
class Solution {
public:
    int myAtoi(string s) {
        int n = s.size();
        long long ans = 0;
        int i{0};
        int sign = 1;
        while (i < n) {
            while (i < n && s[i] == ' ')
                ++i;
            if (i >= n) return 0;
            if (s[i] == '-') {
                sign = -1;
                ++i;
            }
            else if (s[i] == '+') 
                ++i;

            while (i < n && s[i] == '0')
                ++i;
            if (i >= n) return 0;

            while (i < n && ('0' <= s[i] && s[i] <= '9')) {
                ans = ans*10 + (s[i++]-'0');
                if (sign*ans < INT_MIN) 
                    return INT_MIN;
                else if (sign*ans > INT_MAX)
                    return INT_MAX;
            }
            break;
        }
        return static_cast<int>(sign*ans);
    }
};

