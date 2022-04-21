#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

// we try to calculate pi [Integrate (e^(-x^2) + 2 * sqrt(x))^2 from 0 to h]
int nt = 1e5 + 1;  // number of terms
vector<int> coefficients;
ld fsquared(ld a, ld b, ld x) {
    ld t = (a * pow(M_E, -1 * x * x) + b * sqrt(x));
    return t * t;
}

ld cal_vol(ld a, ld b, ld h) {
    ld dx = h / ((ld) (nt - 1));  // n + 1 = nt
    ld sum = 0;
    for (int i = 0; i < nt; i++) {
        ld x = i * dx;
        sum += coefficients[i] * fsquared(a, b, x);
    }
    return M_PI * sum * dx / 3.0;
}

ld target;
int n;
int main() {
    fast_cin();
    // Generate Simpson's Rule Coefficients
    coefficients.emplace_back(1);
    for (int i = 1; i < nt - 1; i++) {
        coefficients.emplace_back((i % 2) ? 4 : 2);
    }
    coefficients.emplace_back(1);

    int cur_best = -1;
    ld cur_best_diff = INT_MAX;
    cin >> target >> n;

    for (int i = 0; i < n; i++) {
        ld a, b, h;
        cin >> a >> b >> h;
        ld vol = cal_vol(a, b, h);
        ld diff = abs(vol - target);
        if (diff < cur_best_diff) {
            cur_best_diff = diff;
            cur_best = i;
        }
    }
    cout << cur_best << endl;

    return 0;
}