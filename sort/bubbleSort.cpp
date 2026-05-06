#include <iostream>
using namespace std;

/*
Loop invariant: 
- Inner loop: At the start of each iteration of the inner loop (indexed by j), a[j] is the largest element in the subarray a[0...j].
- Outer loop: At the start of each iteration of the outer loop (indexed by i), the subarray a[n-i...n-1] consists of the 
i largest elements of the original array in their final sorted positions.


Time complexity: Theta(n^2) for all cases.
    Theta(n) in best cases for optimized version
Space complexity: O(1).

*/

void BUBBLE_SORT(int a[], int n) {
    for (int i{0}; i < n-1; ++i) 
        for (int j{0}; j < n-i-1 ; ++j) 
            if (a[j] > a[j+1]) 
                swap(a[j], a[j+1]);
}

// OPTIMIZED
void BUBBLE_SORT(int a[], int n) {
    for (int i{0}; i < n-1; ++i) {
        bool didSwap = false;
        for (int j{0}; j < n-i-1 ; ++j) {
            if (a[j] > a[j+1]) {
                didSwap = true;
                swap(a[j], a[j+1]);
            }
        }
        // If no two elements are swapped, then break
        if (!didSwap) break;
    } 
}