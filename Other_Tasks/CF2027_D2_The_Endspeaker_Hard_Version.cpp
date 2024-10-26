// #pragma GCC optimize("Ofast")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
// #pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);


int n, m;
vector<int> a, b;
vector<vector<ll>> memo;
int main(){
    int tc;
    cin >> tc;
    while (tc--){
        cin >> n >> m;
        a.assign(n, 0);
        b.assign(m, 0);
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        for (int i = 0; i < m; i++){
            cin >> b[i];
        }

        ll inf = 1e18;
        memo.assign(m+1, vector<ll>(n+1, inf)); 

        // dp(_, n) = 0
        for (int k = 0; k <= m; k++){
            memo[k][n] = 0;
        }

        for (int k=m; k >= 1; k--){
            priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq; // contains {dp(k,j)} for relevant j > i, lazy deletion
            pq.emplace(memo[k][n], n);
            int curSum = 0;  // sum of a(i+1)..a(curBack)
            int curBack = n-1; // we are considering dp(k, i+1)..dp(k, curBack)

            for (int i=n-1; i >= 0; i--){
                if (k < m) memo[k][i] = memo[k+1][i]; // we can try incrementing k
                curSum += a[i];
                while (curBack >= i && curSum > b[k-1]){
                    curSum -= a[curBack];
                    curBack--;
                }

                // curSum = a(i)..a(curBack) <= b[k-1]
                if (curBack < i){ // not possible to grab anything
                    pq.emplace(memo[k][i], i);
                    continue;
                }

                while (!pq.empty() && pq.top().second > curBack + 1){
                    pq.pop();
                }
                if (!pq.empty()){
                    ll val = pq.top().first;
                    memo[k][i] = min(memo[k][i], val + (m-k));
                }

                pq.emplace(memo[k][i], i);
                // cout << "k: " << k << " i: " << i << " memo: " << memo[k][i] << endl;
            }
        }

        vector<vector<ll>> numOps(m+1, vector<ll>(n+1, 0));
        const ll MOD = 1e9 + 7;
        for (int k = 0; k <= m; k++){
            numOps[k][n] = 1;
        }

        for (int k=m; k >= 1; k--){
            
            unordered_map<ll, ll> cellswithValue;
            cellswithValue[memo[k][n]] = numOps[k][n];
            int curSum = 0;  // sum of a(i+1)..a(curBack)
            int curBack = n-1; // we are considering dp(k, i+1)..dp(k, curBack)

            for (int i=n-1; i >= 0; i--){
                if (k < m){
                    if (memo[k][i] == memo[k+1][i]){
                        numOps[k][i] = numOps[k+1][i];
                    }
                }

                curSum += a[i];
                while (curBack >= i && curSum > b[k-1]){
                    curSum -= a[curBack];
                    cellswithValue[memo[k][curBack+1]] -= numOps[k][curBack+1];
                    cellswithValue[memo[k][curBack+1]] %= MOD;
                    curBack--;
                }

                // curSum = a(i)..a(curBack) <= b[k-1]
                if (curBack < i){ // not possible to grab anything
                    cellswithValue[memo[k][i]] += numOps[k][i];
                    cellswithValue[memo[k][i]] %= MOD;
                    continue;
                }


                numOps[k][i] += cellswithValue[memo[k][i] - (m-k)];
                numOps[k][i] %= MOD;

                cellswithValue[memo[k][i]] += numOps[k][i];
                cellswithValue[memo[k][i]] %= MOD;
            }
        }

        if (memo[1][0] >= inf){
            cout << -1 << endl;
        } else {
            cout << memo[1][0] << " " << (numOps[1][0]+MOD)%MOD << endl;
        }


        
        
    }

    return 0;
}