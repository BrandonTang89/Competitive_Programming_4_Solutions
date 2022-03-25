/**HackerRank - Problem Solving Intermediate Question 2
 * Given a paper with dimensions w, h and a sequence of cuts, determine at each state, the maximum area of the pieces cut. 
 * 
 * Input Format:
 * w: width of the paper
 * h: height of the paper
 * isVertical: a sequence of 0s and 1s, where 0 indicates a horizontal cut and 1 indicates a vertical cut
 * distance: a sequence of integers, where each integer is the distance from the left or top of the paper to the cut
 * 
 * Output Format:
 * A vector of integers, where each integer is the maximum area of the pieces cut at each state
 * 
 * Constraints:
 * n <= 1e5
 * 1 <= w, h <= 1e6
 * 
 * Sample Input: getMaxArea(4, 4, {0, 1}, {3, 1});
 * Sample Output: {12, 9}
 * 
 * Explanation:
 * Notice that we can dealt with horizontal cuts and vertical cuts separately. At each state, the maximum area is the maximum of the length
 * between any 2 horizontal cuts times the maximum of the length between any 2 vertical cuts.
 * 
 * We can store these lengths as well as the cuts in binary search trees. For each new vertical cut, we insert it into the cut tree. Then, we determine
 * the length which is being cut, then remove it from the length tree and insert 2 new lengths which are from the length being cut by the new cut.
 * Same idea with horizontal cuts.
 * 
 * Time: O(n log n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

vector<long> getMaxArea(int w, int h, vector<bool> isVertical, vector<int> distance) {
    multiset<ll> verts, horis;
    set <ll> vert, hori;

    vert.insert(0);
    vert.insert(w);
    verts.insert(w);
    hori.insert(0);
    hori.insert(h);
    horis.insert(h);

    vector<long> ans;
    for (int i=0; i< (int) (isVertical.size()); i++) {
        if (isVertical[i]) {
            if (vert.find(distance[i]) == vert.end()){ // new line
                
                auto it = vert.insert(distance[i]).first;
                ll center = *it;
                ll left = *(--it);
                ll right = *(++(++it));

                verts.erase(verts.find(right - left));
                verts.insert(center - left);
                verts.insert(right - center);
            }
        } 
        else {
            if (hori.find(distance[i]) == hori.end()){ // new line
                
                auto it = hori.insert(distance[i]).first;
                ll center = *it;
                ll left = *(--it);
                ll right = *(++(++it));

                horis.erase(horis.find(right - left));
                horis.insert(center - left);
                horis.insert(right - center);
            }
        }

        ll max_area = *(--verts.end()) * *(--horis.end());
        ans.push_back(max_area);
    }
    return ans;
}

int main(){
    auto a = getMaxArea(4, 4, {0, 1}, {3, 1});
    for (auto i : a) cout << i << " ";


    return 0;
}