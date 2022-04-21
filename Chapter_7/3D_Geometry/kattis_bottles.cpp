/**Kattis - bottles
 * Another simpson's rule based question, combine with BSTA. This is relatively easy for a
 * world final's question.
 * 
 * Time: O(n*degree*log(x_hi - x_lo)), Space: O(n + degree)
 */
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

int degree;
vector<ld> poly;

int n = 1e5;  // number of terms
vector<int> coefficients;
ld fsquared(ld x) {
    ld t = 0, cur = 1;
    for (int i=0; i<(int) poly.size(); i++){
        t += poly[i] * cur;
        cur *= x;
    }
    return t * t;
}

ld cal_vol(ld x_lo, ld x_hi) { // volume of revolution
    ld dx = (x_hi - x_lo) / ((ld) n);  // n + 1 = nt
    ld sum = 0;
    for (int i = 0; i <= n; i++) {
        ld x = x_lo + i * dx;
        sum += coefficients[i] * fsquared(x);
    }
    return M_PI * sum * dx / 3.0;
}


int case_counter = 0;
int main() {
    cout << fixed << setprecision(2);
    // Generate Simpson's Rule Coefficients
    coefficients.emplace_back(1);
    for (int i = 1; i < n; i++) {
        coefficients.emplace_back((i % 2) ? 4 : 2);
    }
    coefficients.emplace_back(1);  

    while (cin >> degree){
        poly.resize(degree + 1);
        for (int i=0; i<=degree; i++) cin >> poly[i];
        ld x_lo, x_hi;
        cin >> x_lo >> x_hi;
        ld difference;
        cin >> difference;

        cout << "Case " << ++case_counter << ": " << cal_vol(x_lo, x_hi) << endl;

        ld target = 0;
        
        for (int i=0; i<8; i++){
            // BSTA for where to mark
            target += difference;
            ld lo = x_lo, hi = x_hi + 10, mid;
            while (hi - lo > 1e-9){
                mid = (lo + hi) / 2;
                if (cal_vol(x_lo, mid) > target) hi = mid;
                else lo = mid;
            }
            if (lo > x_hi){
                if (i == 0) cout << "insufficient volume";
                break;
            }
            else{
                cout << lo - x_lo << " ";
            }
        }
        cout << endl;

    }
    return 0;
}