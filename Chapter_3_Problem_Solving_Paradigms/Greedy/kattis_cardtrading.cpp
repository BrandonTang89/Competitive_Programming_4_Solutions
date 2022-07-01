/**Kattis - cardtrading
 * For each type of card, we can either buy until 2 or sell all, those are the only optimal options.
 * Now consider the real cost of getting 2 of that card to be the cost to buy until 2 + unrealised
 * reveneue from selling all of that card. Notice that we should just sort the types of cards by this
 * real cost metric and select the card types with the k lowest costs and make up to 2 of those, selling
 * the rest.
 * 
 * Time: O(t log t + n), Space: O(n)
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

int n, t, k;
vector<ll> v;
int main() {
    fast_cin();
    cin >> n >> t >> k;
    vector<ll> cards;
    cards.assign(t, 0);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        x--;
        cards[x]++;
    }

    vector<pair<ll, ll>> costs;
    for (int i = 0; i < t; i++) {
        ll tobuy, tosell;
        cin >> tobuy >> tosell;
        costs.push_back({tobuy, tosell});
    }

    vector<pair<ll, ll>> arr;
    for (int i = 0; i < t; i++) {
        arr.emplace_back((cards[i] * costs[i].second + (2 - cards[i]) * costs[i].first), i);
    }
    sort(arr.begin(), arr.end());

    ll ans = 0;
    for (int i = 0; i < k; i++) {
        ans -= costs[arr[i].second].first * (2 - cards[arr[i].second]);
    }
    for (int i = k; i < t; i++) {
        ans += costs[arr[i].second].second * (cards[arr[i].second]);
    }
    cout << ans << endl;

    return 0;
}