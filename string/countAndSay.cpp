#include <string>
#include <vector>
#include <iostream>
using namespace std;

string intToString(int n) {
    string res;
    while (n > 0) {
        res += ('0' + n%10);
        n /= 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

string countAndSay(int n) {
    if (n == 1) return "1";
    string s = countAndSay(n-1);
    string rle;
    int l = 0;
    int r = 0;
    while (r < s.size()) {
        while (r < s.size() && s[r] == s[l])
            ++r;
        string times = intToString(r-l);
        char num = s[l];
        rle  = rle + times + num;
        l = r;
    }
    return rle;
}

int main() {
    cout << countAndSay(4);
}
