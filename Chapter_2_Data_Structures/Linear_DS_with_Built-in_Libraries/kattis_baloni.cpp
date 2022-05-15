/**Kattis - baloni
 * if the leftmost balloon is at height h, we need to throw a dart at height h, removing the leftmost
 * balloon and considering that we have a dart travelling at height h-1. We can do this repeatedly, 
 * throwing a new dart if no dart is present to hit the leftmost balloon, else we let the existing
 * darts hit the leftmost balloon. We use a DAT to represent the number of arrows at each height.
 * 
 * Time: O(n), Space: O(1)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

int arrows[1000009];
vector<int> arr;
int main(){
    int n; 
    cin >> n;
    arr.resize(n);
    for (int i=0; i<n; ++i){
        cin >> arr[i];
    }

    int ans = 0;
    for (auto c: arr){
        if (arrows[c] == 0){
            ans++;
        }
        else{
            arrows[c]--;
        }
        if (c == 1) continue;
        arrows[c-1] += 1;
    }
    cout << ans << endl;
    return 0;
}