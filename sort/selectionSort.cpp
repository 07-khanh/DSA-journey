#include <iostream>
using namespace std;

/* 
Loop invariant: At the start of each interation of the outer FOR loop, A[0..j-1] is sorted and consists of j smallest elements.
After the first n-1 iterations, A[0..n-2] consists of n-1 smallest elements -> A[n-1] is automatically the largest.

Time Complexity: Theta(n^2) for all cases.
*/

void SELECTION_SORT(int a[], int n) {
    for (int i{0}; i < n-1; ++i) {        
        int mini{i};
        for (int j{i}; j < n; ++j) {
            if (a[j] < a[mini])
                mini = j;
        }
        if (i != mini) {
            swap(a[i], a[mini]);
        }
    }
}

 
