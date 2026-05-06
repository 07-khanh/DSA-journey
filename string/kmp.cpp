#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> kmp(const string& s) {
    int n = s.size();

    vector<int> pi(n, 0);
    for (int i{1}; i < n; ++i) {
        int j = pi[i-1];
        while (j > 0 && s[j] != s[i]) {
            j = pi[j-1];
        }

        if (s[i] == s[j])
            ++j;
        pi[i] = j;
    }
    return pi;
}

vector<int> findPattern(const string& text, const string& pattern) {
    int T = text.size();
    int P = pattern.size();

    // Compute the LPS table
    vector<int> pi = kmp(pattern);

    // Matching pattern to text
    vector<int> occurrences;
    int i{0};
    int j{0};

    while (i < T) {
        if (text[i] == pattern[j]) {
            ++i;
            ++j;

            if (j == P) {
                occurrences.push_back(i-j);
                j = pi[j-1];
            }
        }
        else {
            if (j != 0) 
                j = pi[j-1];
            else {
                ++i;
            }
        }
    }
    return occurrences;
}


vector<int> countingPrefixOccurrence(const string& s) {
    int n = s.size();
    vector<int> pi = kmp(s);

    vector<int> ans(n, 0);
    for (int i{0}; i < n; ++i) {
        ans[pi[i]]++;
    }

    for (int i{n-1}; i > 0; --i) {
        ans[pi[i-1]] += ans[i];
    }

    for (int i{0}; i < n; ++i)
        ans[i]++;
    
    return ans;
}

int numberOfDistinctSubstrings(const string& s) {
    int n = s.size();
    int ans{0};
    
    string cur;
    for (int i{0}; i < n; ++i) {
        cur += s[i];
        string rev = cur;
        reverse(rev.begin(), rev.end());
        vector<int> pi = kmp(rev);

        int max_pi{0};
        for (int p : pi)
            max_pi = max(max_pi, p);

        ans += i+1-max_pi;
    }
    return ans;
}

int stringCompression(const string& s) {
    int n = s.size();
    vector<int> pi = kmp(s);
    int k = n - pi[n-1];
    if (n % k == 0) return k;
    return n; 
}