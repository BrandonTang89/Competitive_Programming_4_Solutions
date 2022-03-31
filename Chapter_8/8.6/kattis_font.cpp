/**Kattis - font
 * Pretty easy complete search on the NP complete problem of number of set covers. Here we are
 * trying to cover the set [a..z] and each candidate is a word which we process into a bitmask
 * of which letters it covers. Since n is small, we use complete search to either take the
 * word or not.
 * 
 * Time: O(2^n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

string word;
vector<int> word_masks;
int n;

int search(int idx, int mask){
    if (idx == n)return (mask == (1 << 26) - 1);
    return search(idx + 1, mask) + search(idx + 1, mask | word_masks[idx]);
}
int main(){
    cin >> n; 
    word_masks.assign(n, 0);
    for (int i=0; i<n; i++){
        cin >> word;
        for (auto c: word){
            word_masks[i] |= (1 << (c-'a'));
        }
    }
    int ans = search(0, 0);
    cout << ans << endl;
    return 0;
}