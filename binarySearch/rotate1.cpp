#include <iostream>
#include <vector>
using namespace std;

/*
Problem: 
There is an integer array nums sorted in ascending order (with distinct values).
Prior to being passed to your function, nums is possibly left rotated at an unknown index k (1 <= k < nums.length) such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed).
Given the array nums after the possible rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums.
You must write an algorithm with O(log n) runtime complexity.
----------------------------------
APPROACH: Binary Search 
When the array is rotated, one part of the array is always sorted, the other contains the pivot (the rotated part).
Using this, we can decide which part to eliminate using BS.
For every index 'mid':
- Either the left half is sorted
- Or right half is sorted
And then we shrink search space based on whether target lies in that sorted half or not.

- Time complexity: O(lgn)
*/

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size(); 
        int low = 0;
        int high = n-1;

        while (low <= high) {
            int mid = low + (high-low)/2;
            if (nums[mid] == target) return mid;

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
        return -1;
    }
};