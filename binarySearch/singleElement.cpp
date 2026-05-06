#include <vector>
using namespace std;

/*
Problem:
You are given a sorted array consisting of only integers where every element appears exactly twice, except for one element which appears exactly once.
Return the single element that appears only once.

APPROACH: Binary Search
If a pair appears in indices (even, odd), the single element should be on the right side of the pair.
If a pair appears in indices (odd, even), the single element should be on the right side of the pair (the single element shifts the indices of the pairs after).
We base on this property to carry out BS, eliminate half of search space.

-Time complexity: O(lgn)
*/

class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int n = nums.size();
        int low = 0;
        int high = n-1;
        while (low < high) {
            int mid = low + (high-low)/2;
            if (mid % 2 == 1) --mid;
            if (nums[mid] == nums[mid+1]) 
                low = mid+2;
            else
                high = mid;
        }
        return nums[high];
    }
};