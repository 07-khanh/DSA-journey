#include <iostream>
using namespace std;

/*
Improved version of  INSERTION_SORT, perform INSERTION_SORT on gapped subarrays.
Comparing elements far apart first -> gradually reduce the gap 

Time complexity:
- Worst case: O(n^2)
- Average case: O(n^1.2 - n^1.5)
- Best case: O(nlogn)
*/
void SHELL_SORT(int a[], int n) {
    for (int gap{n/2}; gap > 0; gap /= 2) {
        for (int i{gap}; i < n; ++i) {
            int key = a[i];
            int j = i-gap;
            while (j >= 0 && a[j] > key) {
                a[j+gap] = a[j];
                j -= gap; 
            }
            a[j+gap] = key;
        }
    }
}