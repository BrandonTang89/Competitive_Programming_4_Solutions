/**Kattis - units
 * Graph + mathematics. We are dealing with fractions here. Doing it without fractions is just a
 * huge waste of time (I tried). So we define our fraction libary properly and just DFS from any
 * arbitary unit to all other units, and we determine which is the smallest unit.
 *
 * We do another DFS from the smallest unit to get the actual numbers that we want. Then we kinda
 * play around with the numbers until we get the output we require (im sure you can figure that
 * out!)
 *
 * Time: O(V log V), Space: O(V)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
class fraction {
   public:
    ll num, den;

    fraction(ll n)
    {
        num = n;
        den = 1;
    }
    fraction(ll n, ll d)
    {
        num = n;
        den = d;
        reduce();
    }

    fraction operator+(fraction f)
    {
        ll n = num * f.den + f.num * den;
        ll d = den * f.den;
        return fraction(n, d);
    }
    fraction operator-(fraction f)
    {
        ll n = num * f.den - f.num * den;
        ll d = den * f.den;
        return fraction(n, d);
    }
    fraction operator*(fraction f)
    {
        ll n = num * f.num;
        ll d = den * f.den;
        return fraction(n, d);
    }
    fraction operator/(fraction f)
    {
        ll n = num * f.den;
        ll d = den * f.num;
        return fraction(n, d);
    }
    bool operator==(const fraction f) { return (f.num == num && f.den == den); }
    bool operator!=(const fraction f) { return (f.num != num || f.den != den); }
    bool operator<(const fraction f) { return (num * f.den < f.num * den); }
    bool operator>(const fraction f) { return (num * f.den > f.num * den); }

   private:
    void reduce()
    {
        ll g = __gcd(num, den);
        num /= g;
        den /= g;

        if (den < 0) {  // if negaive, numerator negative
            num *= -1;
            den *= -1;
        }
    }
};

ostream &operator<<(ostream &os, const fraction &f) { return os << f.num << "/" << f.den; }

int n;
vector<vector<tuple<int, int, bool>>> adjlist;  // adjlist[u][i] = (v, is_u_larger_than_v)
map<string, int> unit_to_idx;
vector<string> idx_to_unit;
vector<fraction> dist;

void dfs(int u)
{
    for (auto &[v, w, is_u_larger_than_v] : adjlist[u]) {
        if (dist[v] != fraction(-1)) continue;
        if (is_u_larger_than_v) {
            dist[v] = dist[u] / w;
            dfs(v);
        }
        else {
            dist[v] = dist[u] * fraction(w);
            dfs(v);
        }
    }
}
int main()
{
    while (true) {
        cin >> n;
        if (n == 0) break;
        adjlist.assign(n, vector<tuple<int, int, bool>>());
        idx_to_unit.resize(n);
        unit_to_idx.clear();
        for (int i = 0; i < n; i++) {
            string s;
            cin >> s;
            unit_to_idx[s] = i;
            idx_to_unit[i] = s;
        }
        for (int i = 0; i < n - 1; i++) {
            string a, b;
            int w;
            cin >> a >> b >> w >> b;
            int u, v;
            u = unit_to_idx[a];
            v = unit_to_idx[b];

            adjlist[u].emplace_back(v, w, true);
            adjlist[v].emplace_back(u, w, false);
        }
        dist.assign(n, fraction(-1));
        dist[0] = fraction(1);
        dfs(0);

        int min_unit = 0;
        for (int i = 1; i < n; i++) {
            if (dist[i] < dist[min_unit]) {
                min_unit = i;
            }
        }

        dist.assign(n, fraction(-1));
        dist[min_unit] = fraction(1);
        dfs(min_unit);

        vector<tuple<int, int>> v(n);
        for (int i = 0; i < n; i++) {
            v[i] = make_tuple(dist[i].num, i);
        }
        sort(v.begin(), v.end(), greater<tuple<int, int>>());
        ll biggest_factor = get<0>(v[0]);
        for (int i = 0; i < n; i++) {
            auto &[x, idx] = v[i];
            cout << biggest_factor / x << idx_to_unit[idx] << (i == n - 1 ? "\n" : " = ");
        }
    }

    return 0;
}