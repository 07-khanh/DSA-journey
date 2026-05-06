#include <vector>
using namespace std;

int binarySearch(int a[], int n, int t) {
    int low = 0;
    int high = n-1;

    while (low <= high) {
        int mid = low + (high-low)/2;
        if (a[mid] == t) return mid;
        if (a[mid] > t)
            high = mid-1;
        else
            low = mid+1;
    }
    return -1;
}


int binarySearchRecur(int a[], int low, int high, int t) {
    if (low > high) return -1;

    int mid = low + (high-low)/2; 

    if (a[mid] == t) return mid;
    
    if (a[mid] > t) 
        return binarySearchRecur(a, low, mid-1, t);
    else
        return binarySearchRecur(a, mid+1, high, t);
}

int lowerBound(int a[], int n, int t) {
    int ans = n;
    int low = 0;
    int high = n-1;

    while (low <= high) {
        int mid = low + (high-low)/2;
        if (a[mid] >= t) {
            ans = mid;
            high = mid-1;
        }
        else
            low = mid+1;
    }
    return ans;
}

int upperBound(int a[], int n, int t) {
    int ans = n;
    int low = 0;
    int high = n-1;

    while (low <= high) {
        int mid = low + (high-low)/2;
        if (a[mid] > t) {
            ans = mid;
            high = mid-1;
        }
        else
            low = mid+1;
    }
    return ans; 
}

int floor(int a[], int n, int t) {
    int ans = -1;
    int low = 0;
    int high = n-1;

    while (low <= high) {
        int mid = low + (high-low)/2;
        if (a[mid] <= t) {
            ans = a[mid];
            low = low+1;
        }
        else
            high = mid-1;
    }
    return ans; 
}