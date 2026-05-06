#include <iostream>
using namespace std;

int GET_MAX(int a[], int n) {
    int maxi = a[0];
    for (int i{1}; i < n; ++i)
        if (a[i] > maxi)
            maxi = a[i];
    return maxi;
}

void COUNTINGSORT(int a[], int n, int d) {
    int k = 10;
    int b[n];
    int c[k+1];

    for (int i = 0; i < k; ++i) 
        c[i] = 0;

    for (int i = 0; i < n; ++i) 
        c[(a[i] / d) % 10]++;
    
    for (int i = 1; i < k; ++i) {
        c[i] += c[i - 1];
    }
    for (int i = n-1; i >= 0; --i) {
        c[ (c[a[i]] / d) % 10 - 1 ] = a[i];
        c[ (c[a[i]] / d) % 10 ]--;
    }

    for (int i{0}; i < n; ++i)
        a[i] = b[i];
}

void RADIX_SORT(int a[], int n) {
    int maxi = GET_MAX(a, n);

    for (int d = 1; maxi / d > 0; d *= 10)
        COUNTINGSORT(a, n, d);
}