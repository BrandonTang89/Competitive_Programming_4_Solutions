/**Kattis - anthony
 * A relatively simple probability problem. The neat trick here is that we don't need to use
 * both c_left and a_left as DP parameters since a_left + c_left = n - game so we can recover
 * it from a_left and game.
 * 
 * Time: O(a*(a+c)), Space: O(a*(a+c))
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long double ld;

int n, a, c;
ld memo[2005][1005];
ld round_prob[2005];
ld prob_win(int game, int a_left){
    if (a_left == 0) return 0;
    int c_left = n - game - a_left;
    if (c_left == 0) return 1;

    ld &ans = memo[game][a_left];
    if (ans != -1) return ans;

    ans = round_prob[game] * prob_win(game + 1, a_left) + (1 - round_prob[game]) * prob_win(game + 1, a_left - 1);
    return ans;
}

int main(){
    scanf("%d %d", &a, &c);
    n = a + c; // n games are played
    for (int i = 0; i < n; i++) scanf("%Le", &round_prob[i]);
    memset(memo, -1, sizeof memo);
    printf("%Lf\n", prob_win(0, a));
    return 0;
}