/**Kattis - inflagrantedelicto
 * kp is always 2:
 *  If the first event of both is not the same, then we just the 2 first events as our subset.
 *  else we go on to check the second and continue.
 *  Since the 2 sequences are not identical, then there must be a point where the events of both
 *  don't line up.
 * 
 * kr is LCS + 1 since for all k <= length of LCS, we could potentially select a subset of LCS
 * which would result in no consitent reconciliation.
 * 
 * Time: O(n log k), Space: O(n)
 */

#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;

int n, x;
vector<int> v1, v;

int main(){
    scanf("%d", &n);
    v1.assign(n, 0);
    for (int i=0;i<n;i++){
        scanf("%d", &x);
        x--;
        v1[x] = i;
    }
    for (int i=0;i<n;i++){
        scanf("%d", &x);
        x--;
        v.push_back(v1[x]);
    }

    vector<int>L(n, 0); // L[i] is the minimum last element of an IS of length i
    int k = 0; // length of current LIS
    for (int i=0;i<n;i++){
        int pos = lower_bound(L.begin(), L.begin()+k, v[i]) - L.begin();
        L[pos] = v[i];
        if (pos == k){
            k++;
        }
    }
    printf("2 %d\n", k+1);



    return 0;
}