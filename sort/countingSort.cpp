#include <iostream>
using namespace std;

void COUNTINGSORT(int A[], int B[], int n, int k) {
    int C[k+1];
    for (int i = 0; i < n; ++i) {
        C[A[i]] = 0;
    }
    for (int i = 0; i < n; ++i) {
        C[A[i]]++;
    }
    for (int i = 1; i < k; ++i) {
        C[i] += C[i-1];
    }
    for (int i = n-1; i >= 0; --i) {
        B[C[A[i]]-1] = A[i];
        C[A[i]]--;
    }
    delete[] C;
}