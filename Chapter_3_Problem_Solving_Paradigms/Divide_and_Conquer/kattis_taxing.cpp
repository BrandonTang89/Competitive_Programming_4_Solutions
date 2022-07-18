/**Kattis - taxing
 * Observe that we can calculate the real money given as money_after_tax(initial + nominal_given) -
 * money_after_tax(inital). As the real money given increases linearly with the nominal given and we
 * can compute the money_after_tax(some money) quite quickly, we can binary search for the ideal
 * nominal given.
 * 
 * Time: O(fb log (1000)), Space: O(f + b)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int b;
long double p;
vector<pair<long double, long double>> taxes;  // (tax size, tax rate)
long double calculate_money(long double money_before_tax) {
    long double money_after_tax = 0;
    for (auto &[size, rate] : taxes) {
        if (money_before_tax >= size) {
            money_after_tax += size * (1.0 - rate);
            money_before_tax -= size;
        } else {
            money_after_tax += money_before_tax * (1 - rate);
            money_before_tax = 0;
        }
    }
    if (money_before_tax > 0) money_after_tax += money_before_tax * (1 - p);
    return money_after_tax;
}
int main() {
    cin >> b;
    for (int i = 0; i < b; i++) {
        long double size, rate;
        cin >> size >> rate;
        taxes.push_back({size, rate / 100.0});
    }
    cin >> p;
    p /= 100.0;

    int f;
    cin >> f;
    for (int i = 0; i < f; i++) {
        long double initial_money, target_give;
        cin >> initial_money >> target_give;
        long double low = 0, high = 1e12, mid; // note that high needs to be quite high
        for (int j = 0; j < 1000; j++) {
            mid = (low + high) / 2;
            long double real_give =
                calculate_money(initial_money + mid) - calculate_money(initial_money);
            if (real_give < target_give)
                low = mid;
            else
                high = mid;
        }
        cout << fixed << setprecision(10) << mid << endl;
    }

    return 0;
}