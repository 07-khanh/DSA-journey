#include <iostream>
#include <vector>
using namespace std;

/*
Problem: 
There is an integer array nums sorted in non-decreasing order (not necessarily with distinct values).
Before being passed to your function, nums is rotated at an unknown pivot index k (0 <= k < nums.length) such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed).
Given the array nums after the rotation and an integer target, return true if target is in nums, or false if it is not in nums.
You must decrease the overall operation steps as much as possible.
----------------------------------
APPROACH: Binary Search 
Exactly like rotate1 but with duplicates.
Therefore, there will be an edge case where a[mid] == a[low] == a[high], so we cannot decide which half is sorted.
The approach is to shrink search space on both ends (low++, high--) because if a[mid] is not the target then a[low] and a[high]
are also not the target.

- Time complexity: O(lgn)
*/

class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int n = nums.size(); 
        int low = 0;
        int high = n-1;

        while (low <= high) {
            int mid = low + (high-low)/2;
            if (nums[mid] == target) return true;

            // Ambiguous case due to duplicates
            if (nums[low] == nums[mid] && nums[high] == nums[mid]) {
                ++low;
                --high;
            }
            // Check if the left half is sorted
            if (nums[low] <= nums[mid]) {

                // Check if target is in left half -> shrink search space
                if (nums[low] <= target && nums[mid] >= target) 
                    high = mid-1;
                else 
                    low = mid+1;
            }
            // Check if right half is sorted
            else {

                // Check if target is in right half -> shrink search space
                if (nums[mid] <= target && nums[high] >= target) 
                    low = mid+1;
                else 
                    high = mid-1;
            }
        }
        return false;
    }
};