#include <iostream>
using namespace std;

void BUBBLE_SORT(int a[], int n) {
    for (int i{n-1}; i > 0; --i) {
        bool didSwap = false;
        for (int j{0}; j < i; ++j) {
            if (a[j] > a[j+1]) {
                didSwap = true;
                swap(a[j], a[j+1]);
            }
        }
        if (!didSwap) break;
    } 
}

int main() {
    int n;
    cin >> n;
    int a[n];
    for (int i{0}; i < n; ++i)
        cin >> a[i];
    BUBBLE_SORT(a, n);
    for (int i{0}; i < n; ++i)
        cout << a[i] << " ";
    cout << "\n";
}