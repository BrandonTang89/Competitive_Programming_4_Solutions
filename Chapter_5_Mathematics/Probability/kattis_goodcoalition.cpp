/**Kattis - goodcoalition
 * This is a generally simple question that can be solved with DP.. But i had a big problem debugging
 * since initially i used return -1 if total size <= 75. But this resulted in the function thinking
 * that the memo had not yet been computed for some edge cases (such as (1, 100) for all the parties).
 * 
 * Fixing this with the return -0.5 fixed the issue...
 * 
 * Time: O(150*150), Space: O(150*150)
 */

#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long double ld;

int num_tc, n, s;
ld p;
vector<tuple<int,ld>> parties;

ld memo[156][156];
ld stability(int i, int total_size){
    
    if (i == n){
        if (total_size <= 75) return -0.5;
        else return 1;
    }
    if (total_size >= 76)return 1; // speed up
    ld &ans = memo[i][total_size];
    if (ans != -1) return ans;

    auto &[s, p] = parties[i];
    ans = max(stability(i+1, total_size), stability(i+1, total_size + s) * p);

    return ans;
}

int main(){
    scanf("%d", &num_tc);
    for (int tc=0;tc<num_tc;tc++){
        scanf("%d", &n);
        parties.clear();
        memset(memo, -1, sizeof memo);
        for (int i=0;i<n;i++){
            scanf("%d %Le", &s, &p);
            p /= 100;
            parties.emplace_back(s,p);
        }

        printf("%.10Lf\n", 100*stability(0,0));
    }

    return 0;
}