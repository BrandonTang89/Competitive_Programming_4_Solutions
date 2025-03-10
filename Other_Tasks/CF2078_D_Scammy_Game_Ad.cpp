#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
vector<ll> to_add;
vector<pair<ll, ll>> factor;
vector<vector<ll>> memo;
ll dp(ll idx, int side) {
    if (idx == n) return 1;
    if (memo[idx][side] != -1) return memo[idx][side];

    if (side == 0) {
        return memo[idx][side] = dp(idx + 1, 0) + max(dp(idx + 1, 0), dp(idx + 1, 1)) * (factor[idx].first - 1);
    } else {
        return memo[idx][side] = dp(idx + 1, 1) + max(dp(idx + 1, 1), dp(idx + 1, 0)) * (factor[idx].second - 1);
    }
}

int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n;
        to_add.assign(n, 0);
        factor.assign(n, {0, 0});

        for (int i = 0; i < n; i++) {
            char left_op, right_op;
            ll left_num, right_num;

            cin >> left_op >> left_num >> right_op >> right_num;

            if (left_op == '+') {
                factor[i].first = 1;
                to_add[i] += left_num;
            } else {
                factor[i].first = left_num;
            }

            if (right_op == '+') {
                factor[i].second = 1;
                to_add[i] += right_num;
            } else {
                factor[i].second = right_num;
            }
        }

        memo.assign(n, vector<ll>(2, -1));

        ll onLeft = 1;
        ll onRight = 1;
        for (int i = 0; i < n; i++) {
            ll additional = to_add[i] + (factor[i].first - 1) * onLeft + (factor[i].second - 1) * onRight;
            if (dp(i + 1, 0) > dp(i + 1, 1)) {
                // better value to add to the left
                onLeft += additional;
            } else {
                // better value to add to the right
                onRight += additional;
            }
        }

        cout << onLeft + onRight << endl;
    }

    return 0;
}