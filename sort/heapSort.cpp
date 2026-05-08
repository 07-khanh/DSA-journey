#include <iostream>
#include <vector>
using namespace std;

int PARENT(int i) {
    return (i-1)/2;
}
int LEFT(int i) {
    return 2*i + 1;
}
int RIGHT(int i) {
    return 2*i + 2;
}

// Recurrence: T(n) = T(2n/3) + Theta(1)
// O(lgn)
int MAX_HEAPIFY(vector<int>& heap, int i, int n) {
    int l = LEFT(i);
    int r = RIGHT(i);
    int largest = i;
    
    if (l < n && heap[l] > heap[i])
        largest = l;
    
    if (r < n && heap[r] > heap[largest])
        largest = r;
    
    if (i != largest) {
        swap(heap[i], heap[largest]);
        MAX_HEAPIFY(heap, largest, n);
    }
}

// O(n)
void BUILD_MAX_HEAP(vector<int>& heap) {
    int n = heap.size();
    for (int i = n/2 - 1; i >= 0; --i) {
        MAX_HEAPIFY(heap, i, n);
    }
}

//===========================
// IN-PLACE VERSION
//===========================
void HEAPSORT(vector<int>& A) {
    int n = A.size();
    BUILD_MAX_HEAP(A, n);
    
    for (int i = n - 1; i >= 1; --i) {
        swap(A[n-1], A[0]);
        MAX_HEAPIFY(A, 0, --n);
    }
}


//===========================
// USE SEPARATE HEAP
//===========================

int EXTRACT_MAX(vector<int>& heap) {
    int n = heap.size();
    int maxi = heap[0];
    swap(heap[0], heap[n-1]);
    heap.pop_back();
    
    MAX_HEAPIFY(heap, 0, n-1);
    
    return maxi;
}

void INSERT(vector<int>& heap, int value) {
    heap.push_back(value);
    
    int i = heap.size()-1;
    
    while (i > 0) {
        int parent = PARENT(i);
        if (heap[i] > heap[parent]) {
            swap(heap[i], heap[parent]);
            i = parent;
        }
        else 
            break;
    }
}

void HEAPSORT(vector<int>& A) {
    int n = A.size();
    vector<int> heap;
    for (int i{0}; i < n; ++i)
        heap.push_back(A[i]);
    BUILD_MAX_HEAP(A[i]);

    for (int i{n-1}; i >= 0; --i) {
        int maxi = EXTRACT_MAX(heap);
        A[i] = maxi;
    }
}


