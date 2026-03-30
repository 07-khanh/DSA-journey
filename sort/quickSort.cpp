#include <iostream>
#include <cstdlib>
using namespace std;

int RANDOMIZED_PARTITION(int* A, int p, int r) {
    int s = p + rand() % (r - p + 1);
    swap(A[r], A[s]);
    
    int i = p - 1;
    int x = A[r];
    for (int j = p; j <= r - 1; ++j) {
        if (A[j] <= x) {
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i+1], A[r]);
    return i+1;
}

void QUICKSORT(int* A, int p, int r) {
    if (p >= r) return;
    int q = RANDOMIZED_PARTITION(A, p, r);
    QUICKSORT(A, p, q-1);
    QUICKSORT(A, q+1, r);
}


int main() {
    srand(time(NULL));

}