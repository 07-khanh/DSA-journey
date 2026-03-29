#include <iostream>
using namespace std;

int PARENT(int i) {
    return i/2;
}
int LEFT(int i) {
    return 2*i;
}
int RIGHT(int i) {
    return 2*i+1;
}

// O(lgn)
int MAX_HEAPIFY(int** A, int i, int n) {
    int l = LEFT(i);
    int r = RIGHT(i);
    int largest;
    if (l <= n && A[l] > A[i])
        largest = l;
    else
        largest = i;
    if (r <= n && A[r] > A[largest])
        largest = r;
    if (i != largest) {
        swap(A[i], A[largest]);
        MAX_HEAPIFY(A, largest, n);
    }
}

// O(n)
void BUILD_MAX_HEAP(int** A, int n) {
    for (int i = n/2 - 1; i >= 0; --i) {
        MAX_HEAPIFY(A, i, n);
    }
}

// O(nlgn)
void HEAPSORT(int** A, int n) {
    BUILD_MAX_HEAP(A, n);
    for (int i = n - 1; i >= 1; --i) {
        swap(A[n-1], A[0]);
        MAX_HEAPIFY(A, 0, --n);
    }
}


