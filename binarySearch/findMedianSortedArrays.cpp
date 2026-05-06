#include <iostream>
#include <vector>
using namespace std;

/*
Problem: 
Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.
The overall run time complexity should be O(log (m+n)).

APPROACH 1: Merge two arrays
- Time complexity: O(m+n)
- Space complexity: O(m+n) - can be optimized to O(1)

APPROACH 2: Binary Search - Divide and Conquer
Partion the two arrays into two halves.
(half1 : nums1[0..cut1-1] + nums2[0..cut2-1]   ;   half2: nums1[cut1..m] + nums2[cut2..n])
If the largest in half1 is smaller than the min in half2, this is a valid partition, meaning half1 contains (m+n)/2 smallest elements,
half2 contains the remaining larger elements.
From here we can infer the median.

- Time complexity: O(lg(m+n))
- Space complexity: O(1)
*/

//==============================
//APPROACH 1: Merge two arrays - O(m+n)
//==============================

class Solution1 {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int i = 0;
        int j = 0;
        int m = nums1.size();
        int n = nums2.size();
        int k = 0;
        vector<int> nums(m+n);
        while (i < m && j < n) {
            if (nums1[i] <= nums2[j])
                nums[k++] = nums1[i++];
            else
                nums[k++] = nums2[j++];
        }
        while (i < m)
            nums[k++] = nums1[i++];
        while (j < n) 
            nums[k++] = nums2[j++];
        
        if ((m+n)%2==0) {
            int mid = (m+n)/2;
            return (double)(nums[mid-1]+nums[mid])/2;
        }
        else return nums[(m+n)/2];
    }
};

//==============================
//APPROACH 2: Binary Search + Divide and Conquer - O(log(m+n))
//==============================

class Solution2 {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        // Ensure nums1 is the smaller array, then 'half' is always > 'm' > 'cut1' and 'cut2' is always valid.
        if (m > n) 
            return findMedianSortedArrays(nums2, nums1);

        // Required size of each partition
        int half = (m+n)/2;

        bool even = ((m+n)%2 == 0);

        // Can take from 0 to m numbers from nums1
        int low = 0;
        int high = m;   

        while (low <= high) {
            int cut1 = low + (high-low)/2;
            int cut2 = half - cut1; // Always valid because cut1 <= half

            int l1 = INT_MIN;   // If the left half take no number from nums1
            int r1 = INT_MAX;   // If left half take all of nums1
            if (cut1 > 0)
                l1 = nums1[cut1-1];
            if (cut1 < m)
                r1 = nums1[cut1];

            int l2 = INT_MIN;   // If the left half take no number from nums2
            int r2 = INT_MAX;   // If left half take all of nums2
        
            if (cut2 > 0)
                l2 = nums2[cut2-1];
            if (cut2 < n)
                r2 = nums2[cut2];

            // Take less of nums1 in half -> more nums2
            // -> decrease l1 (put in right half), increase r2
            if (l1 > r2) {
                high = cut1-1;
                continue;
            }
            // Take more of nums1 in half -> less nums2
            // -> decrease l2 (put in right half), increase r1
            else if (l2 > r1) {
                low = cut1+1;
                continue;
            }
            
            int l = max(l1, l2);
            int r = min(r1, r2);

            if (even) 
                return ((double)l+ (double)r)/2;
            else {
                // If m + n is odd, the median lies in the right half because half = floor((m+n)/2)
                return r;
            }   
        }
        return 0.0;
    }
};