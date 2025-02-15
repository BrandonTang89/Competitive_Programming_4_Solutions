#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

set<ll> sums;

void processHeights(vector<ll> &h) {
    int n = h.size();
    ll maxSeen = h[n - 1];
    ll minSeen = h[n - 1];

    ll biggestDown = 0;
    ll biggestUp = 0;

    for (int i = n - 2; i >= 0; i--) {
        ll down = minSeen - h[i];
        ll up = maxSeen - h[i];

        biggestDown = min(biggestDown, down);
        biggestUp = max(biggestUp, up);

        minSeen = min(minSeen, h[i]);
        maxSeen = max(maxSeen, h[i]);
    }

    for (ll i = biggestDown; i <= biggestUp; i++) {
        sums.insert(i);
    }
}

int main() {
    fast_cin();
    int tc;
    cin >> tc;
    while (tc--) {
        int n;
        vector<ll> rightActions, leftActions;
        vector<ll> right;
        vector<ll> left;
        sums.clear();

        cin >> n;

        vector<ll> arr(n);
        ll x = 0;
        int xidx = 0;
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
            if (arr[i] > 1 || arr[i] < -1) {
                xidx = i;
            }
        }
        x = arr[xidx];

        leftActions = vector<ll>(arr.begin(), arr.begin() + xidx);
        rightActions = vector<ll>(arr.begin() + xidx + 1, arr.end());

        ll sumLeft = 0;
        for (int i = 0; i < leftActions.size(); i++) {
            sumLeft += leftActions[i];
        }

        left.assign(leftActions.size() + 1, 0);
        left[0] = -sumLeft;
        for (int i = 1; i < left.size(); i++) {
            left[i] = left[i - 1] + leftActions[i - 1];
        }
        assert(left.back() == 0);

        right.assign(rightActions.size() + 1, 0);
        right[0] = 0;
        for (int i = 1; i < right.size(); i++) {
            right[i] = right[i - 1] + rightActions[i - 1];
        }

        processHeights(left);
        processHeights(right);

        ll maxLeft = *max_element(left.begin(), left.end());
        ll minLeft = *min_element(left.begin(), left.end());
        ll maxRight = *max_element(right.begin(), right.end());
        ll minRight = *min_element(right.begin(), right.end());

        ll up = maxRight - minLeft;
        for (int i = 0; i <= up; i++) {
            sums.insert(i + x);
        }

        ll down = minRight - maxLeft;
        for (int i = down; i <= 0; i++) {
            sums.insert(i + x);
        }

        cout << sums.size() << endl;
        for (auto i : sums) {
            cout << i << " ";
        }
        cout << endl;
    }
    return 0;
}