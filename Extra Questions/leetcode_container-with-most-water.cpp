/**leetcode - container with most water
 * Not the most efficient solution, but AC nonetheless
 * Essentially we itereate from max height to 0 and for each height, we consider the left most
 * and right most line of that height as candidates for the max box. The left most line
 * will be paired with the right most line >= in height, and vice versa.
 * 
 * Time: O(n + max_height), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

class Solution {
   public:
    int maxArea(vector<int>& height) {
        vector<int> v[10009];  // v[i] stores indices of lines of height i
        int max_height = -1;
        int max_height_index = 0;
        int left = 100000, right = -1;
        for (int i = 0; i < height.size(); ++i) {
            v[height[i]].push_back(i);
            if (height[i] > max_height) {
                max_height = height[i];
                max_height_index = i;
            }
        }
        int max_area = 0;

        for (int i = max_height; i > 0; i--) {
            if (v[i].size() == 0) continue;
            left = min(left, v[i].front());
            right = max(right, v[i].back());
            max_area = max(max_area, i * (v[i].back() - left));
            max_area = max(max_area, i * (right - v[i].front()));
        }
        return max_area;
    };
};

int main() {
    Solution s;
    vector<int> v({1, 2});
    cout << s.maxArea(v) << endl;
    return 0;
}