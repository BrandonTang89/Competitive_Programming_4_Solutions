#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;

int n;
vector<int> jmp; // jmp[i] = j means a[i] XOR ... XOR a[j] = 0 and j is the smallest possible
vector<int> a;

ll MOD = 1e9 + 7;
vector<vector<ll>> memo;

ll dp(int idx, int t){
    // t = 0 => number of ways to finish given that the next index to choose is idx and v[X] = a[idx-1] for exactly one X in {0, 1, 2}
    // t = 1 => number of ways to finish given that the next index to choose is idx and v[0] = v[1] = v[2] = 0

    if (idx == n) return 1;
    if (memo[idx][t] != -1) return memo[idx][t];

    ll ans = 0;
    if (t == 1){
        if (jmp[idx] == -1){
            ans = 3;
        }
        else{
            ans = (dp(jmp[idx]+1, 1) * 3) % MOD;
            ans += (dp(jmp[idx]+1, 0) * 6) % MOD;
        }
    }
    else{
        if (jmp[idx-1] == -1){
            ans = 1;
        }
        else{
            ans = (dp(jmp[idx-1]+1, 1) * 1) % MOD;
            ans += (dp(jmp[idx-1]+1, 0) * 2) % MOD;
        }
    }

    return memo[idx][t] = ans % MOD;
}

int main(){
    int tc;
    cin >> tc;
    while(tc--){
        cin >> n;
        a.resize(n);
        jmp.assign(n, -1);

        vector<int> prefixXor(n);
        map<int, int> m; // m[x] = i means a[0] XOR ... XOR a[i] = x 
        m[0] = -1;
        for(int i = 0; i < n; i++){
            cin >> a[i];
            prefixXor[i] = a[i] ^ (i == 0 ? 0 : prefixXor[i-1]);

            if (m.find(prefixXor[i]) != m.end()){
                jmp[m[prefixXor[i]] + 1] = i;
            }
            m[prefixXor[i]] = i;
        }
        
        memo.assign(n, vector<ll>(2, -1));
        cout << dp(0, 1) << endl;
    }

    return 0;
}