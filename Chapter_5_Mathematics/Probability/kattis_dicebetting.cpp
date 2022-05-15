/**Kattis - dicebetting
 * Determine the probability of winning. Use dynamic programming to deal with overlapping sub problems
 * e.g. to get to (1, 1) we could go (3, 0) -> (2, 1) -> (1,1) or (3,0) -> (2, 0) -> (1, 1)
 * Probability of winning the weighted average of proability of winning if we get a new distinct
 * value or a repeated value.
 * 
 * Time: O(ns), Space: O(ns)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;
typedef long double ld;

int n, s, k;
ld memo[10005][501];
ld prob(int rolls_left, int num_distinct_vals){
    if (num_distinct_vals >= k)return 1;
    if (rolls_left == 0 || rolls_left < k-num_distinct_vals)return 0;

    if (memo[rolls_left][num_distinct_vals] != -1)return memo[rolls_left][num_distinct_vals];
    
    ld p_repeated = num_distinct_vals/(ld) s;
    ld p_different = 1 - p_repeated;

    return memo[rolls_left][num_distinct_vals] = p_repeated*prob(rolls_left-1, num_distinct_vals) + p_different*prob(rolls_left-1, num_distinct_vals+1);
}
int main(){
    memset(memo, -1, sizeof memo);
    scanf("%d %d %d", &n, &s, &k);
    printf("%.10Lf\n", prob(n, 0));

    return 0;
}