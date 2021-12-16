/**Kattis - natjecaje
 * Somewhat tedious backtracking problem. But not too hard to AC if you are careful.
 * 
 * Time: O(2^n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

int n, s, r, x;
vector<int> v;

int backtrack(int u){ // returns the minimal number of teams that cannot start competition
    if (u == n){
        int ans = 0;
        for (auto i: v){
            if (i == -1)ans++;
        }
        return ans;
    }
    if (v[u] != 1)return backtrack(u+1); // cannot do anything

    int ans = INT_MAX;
    if (u == 0){
        if (v[1] == -1){
            v[1] = 0;
            v[0] = 0;
            ans = backtrack(u+1);
            v[1] = -1;
            v[0] = 1;
        }
        else{
            ans = backtrack(u+1);
        }
        return ans;
    }
    else if (u == n-1){
        if (v[u-1] == -1){
            v[u-1] = 0;
            v[u] = 0;
            ans = backtrack(u+1);
            v[u-1] = -1;
            v[u] = 1;
        }
        else{
            ans = backtrack(u+1);
        }
        return ans;
    }
    else{
        // either pass to before or after
        ans = backtrack(u+1); // assume we dont need to pass to before or after
        if (v[u-1] == -1){
            v[u-1] = 0;
            v[u] = 0;
            ans = min(ans, backtrack(u+1));
            v[u-1] = -1;
            v[u] = 1;
        }
        if (v[u+1] == -1){
            v[u+1] = 0;
            v[u] = 0;
            ans = min(ans, backtrack(u+1));
            v[u+1] = -1;
            v[u] = 1;
        }
        return ans;
    }
}

int main(){
    cin >> n >> s >> r;
    v.assign(n, 0);
    for (int i=0; i<s; i++){
        cin >> x;
        v[x-1] += -1;
    }
    for (int i=0; i<r; i++){
        cin >> x;
        v[x-1] += 1;
    }
    cout << backtrack(0) << endl;

    return 0;
}