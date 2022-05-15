/**Kattis - ticketpricing
 * Another relatively simple DP problem. State: (current week, number of seats left), Transition:
 * Try each of the ticket prices.
 * 
 * Time: O(wn*max_k), Space: O(wn)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

const int INF = (int) 1e9;
int n, w, k;
vector<int> p, s;
vector<vector<pair<int, int>> > v; // v[w] = {(p, s)}
vector<vector<int>> memo; 

int dp(int cw, int pass_left){
    //cout << "cw: " << cw << " pass_left: " << pass_left << endl;
    if (pass_left == 0) return 0;
    if (cw == w) return 0;
    if (memo[cw][pass_left] != -1) return memo[cw][pass_left];

    int ans = 0;
    for (int i = 0; i < (int) v[cw].size(); i++){
        int p = v[cw][i].first;
        int s = v[cw][i].second;
        int num_sold = min(s, pass_left);
        ans = max(ans, num_sold*p + dp(cw + 1, pass_left - num_sold));
    }
    
    return memo[cw][pass_left] = ans;
}

int main(){
    cin >> n >> w;
    w++;
    v.assign(w, vector<pair<int, int>>());
    memo.assign(w, vector<int>(n+9, -1));
    for(int i = 0; i < w; i++){
        cin >> k;
        p.assign(k, 0);
        s.assign(k, 0);
        for (int j=0; j<k; j++){
            cin >> p[j];
        }
        for (int j=0; j<k; j++){
            cin >> s[j];
        }

        for (int j=0; j<k; j++){
            v[i].push_back(make_pair(p[j], s[j]));
        }
    }
    cout << dp(0, n) << endl;
    for (int i = 0; i < (int) v[0].size(); i++){
        int p = v[0][i].first;
        int s = v[0][i].second;
        int num_sold = min(s, n);
        if (dp(0,n) == num_sold*p + dp(1, n - num_sold)){
            cout << p << endl;
            break;
        }
    }


    return 0;
}