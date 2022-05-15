/**Kattis - programmingteamselection
 * Decide whether we can partition the graph into triangles (3 cliques). We use DP.
 * 
 * Time: O(2^n * n^3), Space: O(2^n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;
#define LSOne(S) (S & (-S))

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n, e; // n <= 14
int tc = 0;
map<string, int> fromnames;
vector<int> adjmat;

int memo[1 << 15], last_used[1 << 15];
bool dp(int mask){
    if (mask == 0)return true;
    if (last_used[mask] == tc)return memo[mask];
    last_used[mask] = tc;

    int ans = false;
    for (int m1 = mask; m1 && !ans; m1 ^= LSOne(m1)){
        for (int m2 = m1 ^ LSOne(m1); m2 && !ans ; m2 ^= LSOne(m2)){
            for (int m3 = m2 ^ LSOne(m2); m3 && !ans; m3 ^= LSOne(m3)){
                int a, b, c; // our next triangle
                a = __builtin_ctz(m1);
                b = __builtin_ctz(m2);
                c = __builtin_ctz(m3);

                if (adjmat[a] & (1 << b) && adjmat[b] & (1 << c) && adjmat[c] & (1 << a)){ // triangle
                    int nmask = mask ^ ((1 << c) | (1 << b) | (1 << a));
                    if (dp(nmask)){
                        ans = true;
                        break;
                    }
                }
            }
        }
    }

    return (memo[mask] = ans);
}

int main(){
    fast_cin();
    while (true){
        tc++;
        cin >> e;
        if (e == 0)break;
        adjmat.assign(16, 0);
        fromnames.clear();
        n = 0;

        for (int i=0; i<e; i++){
            string a, b;
            cin >> a >> b;
            if (fromnames.find(a) == fromnames.end()){
                fromnames[a] = n++;
            }
            if (fromnames.find(b) == fromnames.end()){
                fromnames[b] = n++;
            }

            adjmat[fromnames[a]] |= (1 << fromnames[b]);
            adjmat[fromnames[b]] |= (1 << fromnames[a]);
        }

        if (n % 3 != 0){
            cout << "impossible" << endl;
            continue;
        }
        for (int i=0; i<n; i++)adjmat[i] |= (1 << i);

        cout << (dp((1 << n) - 1) ? "possible" : "impossible") << endl;
    }


    return 0;
}