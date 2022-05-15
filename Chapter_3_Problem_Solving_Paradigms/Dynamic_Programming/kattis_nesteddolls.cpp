/* Kattis - Nesteddolls

Abridge problem statement:
    Find the size of the minimal chain cover of S, the finite partially ordered set of dolls.

Observation 0:
    The number of dolls needed is the size of the minimal chain cover of S... But maybe finding the size of the maximal
    anti-chain will be easier though. We know these 2 values are the same due to Dilworth's theorem anyway...

Observation 1:
    If we sort the dolls by the first dimension in decending order and second dimention in ascending order,
    and then find the longest non-decreasing sequence in the second dimension... What do we get? 

    Turns out it is the maximal anti chain length. But why?

    30 10 -
    20 19 -
    20 20 - 
    15 20 -
    10 18
    10 30 -

    The reasoning is that for any 2 elements on a NDS, if (x1, y1) come before (x2, y2):
        x2 <= x1 so not (x2, y2) > (x1, y1)
        and yet y2 >= y1 so not (x2, y2) < (x1, y1)

        Thus all members of the NDS can form an anti-chain.
    
    In fact, all anti-chains are NDSs on the sorted array...
    
    Since we are finding the length of the maximal anti chain, we should thus find the LNDS

Time: O(n log k), Mem: O(n)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n, t;
int w, h;
vector<pair<int,int>> v;

bool cus_comp(pair<int,int>a, pair<int,int> b){
    if (a.first > b.first) return true;
    if (b.first > a.first) return false;
    else
        return (a.second <= b.second);
}

int main(){
    cin >> t;
    for (int tc=0;tc<t;tc++){
        v.clear();
        cin >> n;
        for (int i=0;i<n;i++){
            cin >> w >> h;
            v.emplace_back(make_pair(w, h)); 
        }

        sort(v.begin(), v.end(), cus_comp);

        vector<int>L(n, 0); // L of length n, all elements 0
        int k = 0;
        for (int i=0;i<n;i++){
            int pos = upper_bound(L.begin(), L.begin()+k, v[i].second) - L.begin();
            L[pos] = v[i].second;
            if (pos == k){
                k++;
            }
        }
        cout << k << endl;

    }

   return 0;
}