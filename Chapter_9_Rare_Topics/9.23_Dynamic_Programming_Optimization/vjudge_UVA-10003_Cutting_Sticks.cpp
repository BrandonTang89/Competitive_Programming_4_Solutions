/**Uva 10003 - cutting sticks
 * We let the state be (l, r) where l and r refer to the indices of the cuts on the left and right of the
 * current stick. We try cutting every cut between l and r. Notice that this satisfies the quadrangle
 * inequality and thus we can use Knuth's optimisation.
 * 
 * Time: O(n^2), Space: O(n^2)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;

ll n, INF = 1e9, l;
vector<ll> A;
int cost(int l, int r) {  // range sum of [l, r]
    return (A[r] - A[l]);
}

vector<vector<int>> memo, opt;
int dpKnuth(int i, int j) {
    if (i + 1 == j){
        opt[i][j] = i;
        return memo[i][j] = 0; // already cut
    }
    if (memo[i][j] != -1) return memo[i][j];
    memo[i][j] = INF;

    int start = (j > i ? opt[i][j - 1] : i);
    if (start == -1) start = i;  // if not yet processed that state

    int end = (i < n - 1 ? opt[i + 1][j] : j);
    if (end == -1) end = j;  // if not yet processed that state

    for (int k = start; k <= end; k++) {
        int tcost = dpKnuth(i, k) + dpKnuth(k, j) + cost(i, j);
        if (tcost < memo[i][j]) {
            memo[i][j] = tcost;
            opt[i][j] = k;
        }
    }
    return memo[i][j];
}

int main(){
    while (1){
        cin >> l;
        if (l == 0)break;
        cin >> n;
        A.resize(n+2);
        A[0] = 0;
        for (int i=1; i<=n; i++){
            cin >> A[i];
        }
        A[n+1] = l;
        
        n += 2;
        memo.assign(n, vector<int>(n, -1));
        opt.assign(n, vector<int>(n, -1));
        cout << "The minimum cutting is " << dpKnuth(0, n - 1) << "." << endl;
    }

    return 0;
}