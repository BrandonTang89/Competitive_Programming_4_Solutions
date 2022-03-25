/**Kattis - rollercoasterfun
 * A very interesting DP problem!. 
 * 
 * Observation 1: If b != 0, b >= 1 ==> f(i, k) where k >= 32 will be 0, ie each ride
 * is only profitable at most 32 times. 
 * 
 * Observation 2: If b == 0, each ride can possibly be used up to T <= 25000 times :( but
 * if b == 0 for all rides, we don't have to include information about how many times we
 * have taken each of the rides. 
 * 
 * Observation 3: The order in which we take rides is irrelevant. Thus we can assume the guy
 * takes all the diminishing rides (drides) before the recurrent rides (rrides).
 * 
 * The key idea is thus to split into two parts: for the drides, we have state =
 * (rides_considered, T) where we have T time to try to take all the rides after
 * rides_considered. So we process the rides one at a time, try taking each ride up to
 * 32 times. Thus the time complexity for this part is O(n * 32 * T).
 * 
 * For the rrides, we have state = (T) where we then try one of each of the rrides! This
 * more appropriate state representation results in O(T*n) time for this section.
 * 
 * Also note that we don't need to reset the memo arrays after each run because we set T
 * to be remaining time left rather than time passed! Thats pretty big brain.
 * 
 * Time: O(n*T), Space: O(n*T)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

int n;
int INF = 1e9;
vector<tuple<int, int, int>> drides; // a, b, t; where b != 0
vector<tuple<int, int>> rrides; // a, t. b = 0

int memo1[101][25002], memo2[25002];
int dp2(int T){
    if (T == 0) return 0; 
    if (T < 0) return -INF;

    if (memo2[T] != -1) return memo2[T];
    memo2[T] = 0;
    for (auto &[a, t] : rrides){
        memo2[T] = max(memo2[T], dp2(T-t) + a);
    }

    return memo2[T];
}
int dp1(int rides_considered, int T){
    if (T == 0) return 0; 
    if (T < 0) return -INF;
    if (rides_considered == (int) drides.size()) return dp2(T);
    if (memo1[rides_considered][T] != -1) return memo1[rides_considered][T];

    auto &[a, b, t] = drides[rides_considered];
    int ans = dp1(rides_considered+1, T), fun = 0;
    for (int k=1; k*t <= T; k++){
        int increase_in_fun = a - (k-1)*(k-1)*b;
        if (increase_in_fun <= 0) break;
        fun += increase_in_fun;

        ans = max(ans, dp1(rides_considered+1, T-k*t) + fun);
        // cout << "ans " << ans << " fun " << fun << " k " << k << " T " << T << endl;
    }
    return memo1[rides_considered][T] = ans;
}

int main(){
    cin >> n;
    for (int i=0; i<n; i++){
        int a, b, t;
        cin >> a >> b >> t;
        if (b != 0) drides.push_back({a, b, t});
        else rrides.push_back({a, t});
    }

    memset(memo1, -1, sizeof memo1);
    memset(memo2, -1, sizeof memo2);
    
    int num_sess = 0, T;
    cin >> num_sess;

    for (int i=0; i<num_sess; i++){
        cin >> T;
        cout << dp1(0, T) << endl;
    }

    return 0;
}