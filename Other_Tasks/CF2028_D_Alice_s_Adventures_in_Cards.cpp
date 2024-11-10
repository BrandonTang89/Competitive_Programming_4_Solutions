#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int main() {
    fast_cin();
    int tc;
    cin >> tc;
    while (tc--) {
        int n;
        cin >> n;
        vector<pair<int, int>> arr(n);
        for (int i = 0; i < n; i++) {
            cin >> arr[i].first;
            arr[i].first -= 1;
            arr[i].second = i;
        }

        vector<pair<int, int>> brr(n);
        for (int i = 0; i < n; i++) {
            cin >> brr[i].first;
            brr[i].first -= 1;
            brr[i].second = i;
        }

        vector<pair<int, int>> crr(n);
        for (int i = 0; i < n; i++) {
            cin >> crr[i].first;
            crr[i].first -= 1;
            crr[i].second = i;
        }

        vector<tuple<int, int, int>> cards;
        for (int i = 0; i < n; i++) {
            cards.push_back({arr[i].first, brr[i].first, crr[i].first});
        }

        auto [a, b, c] = cards[0];
        int maxa = 0;
        int maxb = 0;
        int maxc = 0;

        sort(arr.begin(), arr.end());
        sort(brr.begin(), brr.end());
        sort(crr.begin(), crr.end());

        vector<bool> unlocked(n, false);
        vector<pair<int, char>> unlocker(n, {-1, -1});
        unlocked[0] = true;
        for (int i = 0; i < n; i++) {
            if (!unlocked[i]) continue;

            auto [newmaxA, newmaxB, newmaxC] = cards[i];

            for (int a = maxa; a <= newmaxA; a++) {
                if (unlocked[arr[a].second]) continue;
                unlocked[arr[a].second] = true;
                unlocker[arr[a].second] = {i, 'q'};
            }
            for (int b = maxb; b <= newmaxB; b++) {
                if (unlocked[brr[b].second]) continue;
                unlocked[brr[b].second] = true;
                unlocker[brr[b].second] = {i, 'k'};
            }
            for (int c = maxc; c <= newmaxC; c++) {
                if (unlocked[crr[c].second]) continue;
                unlocked[crr[c].second] = true;
                unlocker[crr[c].second] = {i, 'j'};
            }

            maxa = max(maxa, newmaxA);
            maxb = max(maxb, newmaxB);
            maxc = max(maxc, newmaxC);
        }

        if (unlocked[n - 1]) {
            cout << "YES" << endl;
            vector<pair<char, int>> ans;
            int cur = n - 1;
            while (cur != 0) {
                ans.push_back({unlocker[cur].second, cur});
                cur = unlocker[cur].first;
            }

            reverse(ans.begin(), ans.end());
            cout << ans.size() << endl;
            for (auto [c, i] : ans) {
                cout << c << " " << i + 1 << endl;
            }
        } else {
            cout << "NO" << endl;
        }
    }

    return 0;
}