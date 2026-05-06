#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> z_function(const string& s) {
    int n = s.size();
    vector<int> z(n, 0);

    int l{0};
    int r{0};
    for (int i{1}; i < n; ++i) {
        z[i] = min(z[i-l], r-i);

        while (i + z[i] < n && s[z[i]] == s[i+z[i]])
            ++z[i];

        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}


vector<int> findSubstring(const string& text, const string& pattern) {
    int T = text.size();
    int P = pattern.size();
    string s = pattern + '$' + text;
    vector<int> z = z_function(s);

    vector<int> occurrences;
    for (int i{0}; i < T; ++i) {
        if (z[P + 1 + i] == P)
            occurrences.push_back(i);
    }
    return occurrences;
}


int numberOfDistinctSubstrings(const string& s) {
    int n = s.size();
    string cur = "";

    int res{0};
    for (int i{0}; i < n; ++i) {
        cur += s[i]; 
        string rev = cur;
        reverse(rev.begin(), rev.end());
        vector<int> z = z_function(rev);
        int z_max = 0;
        for (int j = 1; j < z.size(); ++j)
            z_max = max(z_max, z[j]);

        res += i+1 - z_max;
    }
    return res;
}

int stringCompression(const string& s) {
    int n = s.size();
    vector<int> z = z_function(s);

    for (int i{1}; n % i == 0; ++i) {
        if (i + z[i] == n) return i;
    }
}

