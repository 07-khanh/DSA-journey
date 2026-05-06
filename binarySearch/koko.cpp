#include <vector>
#include <algorithm>
using namespace std;

/*
Koko loves to eat bananas. There are n piles of bananas, the ith pile has piles[i] bananas. The guards have gone and will come back in h hours.
Koko can decide her bananas-per-hour eating speed of k. Each hour, she chooses some pile of bananas and eats k bananas from that pile. If the pile has less than k bananas, she eats all of them instead and will not eat any more bananas during this hour.
Koko likes to eat slowly but still wants to finish eating all the bananas before the guards return.
Return the minimum integer k such that she can eat all the bananas within h hours.

APPROACH: Binary search
Loop invariant: 
    All k < low is INVALID
    All k > high is VALID
Therefore upon termination, low > high and low is the first VALID k -> return low.

- Time complexity: O(nlg(max(piles)))
*/

class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int low = 1;
        int high = *max_element(piles.begin(), piles.end());

        while (low <= high) {
            int mid = low + (high-low)/2;

            long long times = 0;
            for (int i{0}; i < piles.size(); ++i) {
                times += (piles[i] + mid - 1)/mid;
            }
            if (times <= h) 
                high = mid-1;
            else 
                low = mid+1;
        }
        return low;
    }
};