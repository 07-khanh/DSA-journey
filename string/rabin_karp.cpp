#include <iostream>
#include <string>
#include <vector>
using namespace std;


// =======================
// APPROACH 1: Using rolling hash
// =======================
vector<int> rabin_karp(string const& text, string const& pattern) {
    const int p = 256;  // Number of  ASCII characters
    const int m = 1e9 + 9; // Large prime number to avoid collisions
    
    int T = text.size();
    int P = pattern.size();
    if (P > T) return {};

    long long p_pow{1};

    // Precompute the largest power 
    for (int i{1}; i < P; ++i) {
        p_pow = (p_pow * p) % m; 
    }

    long long h_p = 0;
    long long cur_h = 0;
    for (int i{0}; i < P; ++i) {
        h_p = ((h_p * p) % m + pattern[i]) % m;     // Hash of pattern
        cur_h = ((cur_h * p) % m + text[i]) % m;    // Hash of the first P characters in text
    } 

    vector<int> occurrences;
    for (int i{0}; i+P <= T; ++i) {
        if (h_p == cur_h) {
            if (text.substr(i, P) == pattern)
                occurrences.push_back(i);
        }
        if (i+P < T)
            // Rolling hash formula
            cur_h = ((cur_h + m - text[i] * p_pow % m) * p + text[i+P]) % m;
    }
    return occurrences;
}

// =======================
// APPROACH 2: Using prefix hash (simpler, direct hash lookup)
// =======================

vector<int> rabin_karp(string const& text, string const& pattern) {
    const int p = 256;  // Number of  ASCII characters
    const int m = 1e9 + 9; // Large prime number to avoid collisions
    
    int T = text.size();
    int P = pattern.size();
    if (P > T) return {};

    vector<long long> p_pow(T);
    p_pow[0] = 1;
    // Precompute power
    for (int i{1}; i < T; ++i) {
        p_pow[i] = (p_pow[i-1]*p) % m; 
    }

    // Prefix hash of text
    vector<long long> h(T+1, 0);
    for (int i{0}; i < T; ++i) 
        h[i+1] = (h[i] + text[i]*p_pow[i]) % m;

    // Hash of pattern
    long long h_p = 0;
    for (int i{0}; i < P; ++i) 
        h_p = (h_p + pattern[i]*p_pow[i]) % m;

    vector<int> occurrences;
    for (int i{0}; i+P <= T; ++i) {
        long long cur_h = (h[i+P] + m - h[i]) % m; // add m to avoid negative value
        if (cur_h == (h_p * p_pow[i]) % m) {
            if (text.substr(i, P) == pattern)
                occurrences.push_back(i);
        }
    }
    return occurrences;
}