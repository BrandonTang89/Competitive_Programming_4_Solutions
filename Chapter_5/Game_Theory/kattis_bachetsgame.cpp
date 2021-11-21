/**Kattis - bachetsgame
 * The problem itself is not too difficult. The only "trick" is to drop the parameter of the current
 * player since the game has a form of symmetry, ie both players make the same move and will both
 * do the same optimal moves.. So instead of having our dp state be (n, player) and have a return of
 * whether stan will win, we just use (n) which returns whether the current player will win, thus
 * halving the state space.
 * 
 * The more interesting thing is that I ran into a bug where my code would throw a RTE at large values
 * of n. However, I was able to AC on kattis... Hm
 * 
 * Time: O(n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

int n, m;
int memo[1000005];
vector<int> s;
bool player_wins(int n){
    if (n == 0) return false;

    if (memo[n] != -1) return memo[n];

    bool win = 0;
    for (auto d: s){
        if (n - d < 0)continue;
        if (not player_wins(n - d)){
            win = 1;
            break;
        }
    }

    memo[n] = win;
    return memo[n];
}
int main(){
    while (scanf("%d %d", &n, &m) != EOF){
        memset(memo, -1, sizeof memo);
        s.assign(m, 0);

        for (int i=0;i<m;i++){
            scanf("%d", &s[i]);
        }
        
        if (player_wins(n)){
            printf("Stan wins\n");
        }
        else{
            printf("Ollie wins\n");
        }
    }


    return 0;
}