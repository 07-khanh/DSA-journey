#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

//===============================
// APPROACH 1: Brute Force 
// Time complexity: O(k*n)
//===============================
class Solution1 {
    double minMaxDist(vector<int> &stations, int K) {
        int n = stations.size();
        if (n == 1) return 0;
        if (n == 2) return (double)(stations[1] - stations[0]) / (K + 1);

        vector<int> midNum(n-1, 0);
        
        for (int i{0}; i < K; ++i) {
            double maxLen = 0;
            int maxIdx = 0;

            // Find the largest gap
            for (int k{0}; k < n-1; ++k) {
                double gap = (double)(stations[k+1] - stations[k]) / (midNum[k] + 1);
                if (gap > maxLen) {
                    maxLen = gap;
                    maxIdx = k;
                }
            }   
            // Put the station in the largest gap
            midNum[maxIdx]++;
        }
        
        // Find the largest gap, which is the smallest possible
        double ans = 0;
        for (int i{0}; i < n-1; ++i) {
            double gap = (double)(stations[i+1] - stations[i]) / (midNum[i] + 1);
            ans = max(ans, gap);
        }
        return ans;
    }
};


//===============================
// APPROACH 2: Heap
// Time complexity: O(nlgn + klgn)
// Space complexity: O(n-1)
// Like the brute force approach but optimize the finding max gap process by keeping a max heap DS (priority queue)
//===============================
class Solution2 {
    double minMaxDist(vector<int> &stations, int K, int n) {
        int n = stations.size();
        if (n == 1)  return 0;
        if (n == 2) return (double)(stations[1] - stations[0]) / (K+1);

        priority_queue<pair<double, int>, vector<pair<double, int>>> pq;
        for (int i{0}; i < n-1; ++i)
            pq.push({(double)stations[i+1]-stations[i], i});

        vector<int> gap(n-1, 0);
        for (int station{1}; station <= K; ++station) {
            pair<double ,int> p  = pq.top();
            double cur = p.first;
            int sec = p.second;
            pq.pop();
            
            double original = cur*(gap[sec]+1);
            double newGap = original / (gap[sec]+2);
            pq.push({newGap, sec});
            gap[sec]++;
        }
        return pq.top().first;
    }
};

