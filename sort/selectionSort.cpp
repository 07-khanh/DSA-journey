#include <iostream>
using namespace std;

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

 