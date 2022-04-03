/**Kattis - bing
 * Really easy question. Just use a hashmap of all the prefixes of strings. Note that we
 * could have used string view if we really needed to save memory.
 * 
 * Time O(n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

unordered_map<string, int>m;
int n;
int main(){
    cin >> n;
    for (int i=0; i<n; i++){
        string s;
        cin >> s;
        cout << m[s] << endl;
        for (int j=1; j<= (int) s.size(); j++){
            string t = s.substr(0, j);
            m[t]++;
        }
    }
    return 0;
}