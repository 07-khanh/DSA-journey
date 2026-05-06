#include <vector>
using namespace std;

/*
Problem: 
Given an array arr of positive integers sorted in a strictly increasing order, and an integer k.
Return the kth positive integer that is missing from this array.

APPROACH: Binary Search
Loop invariant:
    arr[0..low-1] : elements having less than k missing positive numbers
    arr[high+1...n-1]: elements having more than k missing positive numbers
Upon termination: 'low' is the number of elments having less than k missing positive numbers.
Those elements will shift the kth original positive number by 'low' positions.
Therefore the answer is low + k.
*/

class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {
        int low = 0;
        int high = arr.size()-1;

        while (low <= high) {
            int mid = (low+high)/2;
            int missing = arr[mid]-mid-1;

            if (missing < k) 
                low = mid + 1;
            else
                high = mid - 1;
        }
        return k + low;
    }
};