/**Kattis - ridofcoins
 * An interesting problem. The first thing to notice is that the coin system is canonical. This
 * means we can answer the minimum number of coins needed to make a certain amount of change
 * using a greedy strategy assuming that we have infinite supply of each coin. So how can we
 * change the maximising problem to a minimising one? We can assume we give all the coins we have
 * then we try to get some back. Specifically we want to get back the minimum number of coins.
 *
 * Okay so we know that the greedy strategy is optimal if we have infinite of every coin...
 * But now we have coin restrictions. What do we do about this? Well we notice that 1 | 5 | 10.
 * Assuming we fix the number of 25 cent coins we use, the greedy strategy will definitely
 * work on the rest. This is because if we choose less than x/10 10 cent coins, we will need
 * more 1 and 5 cent coins, making it even less likely to be able to make the change, and increasing
 * the number of coins used in total. Similar idea for why we should always use x/5 coins after
 * choosing the number of 10 cent coins. 
 * 
 * To deal with the 25 cent coins, we just use a for loop. And get the max amount of coins we
 * can give the shop by keeping a global max.
 * 
 * Remember to typecast all the numbers to long long.
 * 
 * Time: O(1e8/25), Space: O(1)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

ll n_coins[4];  // 1, 5, 10, 25
ll total_money, to_pay, total_coins = 0;
int main() {
    cin >> to_pay;
    for (int i = 0; i < 4; i++) {
        cin >> n_coins[i];
        total_coins += n_coins[i];
    };
    total_money = n_coins[0] * 1LL + n_coins[1] * 5LL + n_coins[2] * 10LL + n_coins[3] * 25LL;

    // total_money < to_pay => total_money - to_pay < 0
    ll target = total_money - to_pay;
    if (target < 0) {
        cout << "Impossible" << endl;
        return 0;
    }

    ll ans = -1;
    for (ll num_25 = min(n_coins[3], target / 25LL); num_25 >= 0; num_25--) {
        ll target2 = target - num_25 * 25LL;
        ll num_10 = min(n_coins[2], target2 / 10LL);
        target2 -= num_10 * 10LL;
        ll num_5 = min(n_coins[1], target2 / 5LL);
        target2 -= num_5 * 5LL;
        ll num_1 = target2;
        if (num_1 <= n_coins[0]) {
            ans = max(ans, total_coins - (num_25 + num_10 + num_5 + num_1));
        }
    }
    if (ans == -1) {
        cout << "Impossible" << endl;
    } else {
        cout << ans << endl;
    }

    return 0;
}