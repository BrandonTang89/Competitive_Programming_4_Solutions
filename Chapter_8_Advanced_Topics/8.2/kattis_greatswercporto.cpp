/**Kattis - greatswercporto
 * This is a tedious complete search + pruning problem. The basic idea is that we use a recursive backtracking approach
 * to assign numbers to each character, using a bitmask of length 10 determine which numbers have been assigned to some
 * character. At the end of assigning to all of the characters, we do a check to see if the assignment is valid.
 * 
 * This by itself will TLE. We need to prune early. Notice that after we assigned all the units place characters, we can
 * quickly do a check to see if the sum of the last digits of the operands mod 10 is equal to the last digit of the ans.
 * This will prune a large amount of the search space. However, to implement it, we need to ensure that we are assigning
 * all the unit digits first. This means parsing the input twice, once just parsing the last character, and once parsing
 * everything else, thus ensuring that m[some unit char] < m[some non unit char] for character. We also count how many
 * unique unit chars there are and thus know when to run our check_units().
 * 
 * also note to add the exception that we cannot assign a 0 to any of the leftmost characters. We use a hashset to check
 * if a character is a leftmost character whenever the bit to assign is 0.
 * 
 * Time: O(<<10!) due to pruning, Space: O(1) effectively.
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
#define LSOne(S) ((S) & -(S))

int n;
map<char, int> m;
vector<string> words;
int bm = 0, numc = 0, num_unit_chars = 0;
int assignments[10];
unordered_set<int> left_most_digits;
bool check() {
    /*for (int i=0;i<numc;i++){cout << assignments[i] << " ";}cout << endl;*/
    int s = 0;
    for (int i = 0; i < n - 1; i++) {
        vector<int> v;
        for (int j = 0; j < (int)words[i].size(); j++) {
            v.push_back(assignments[m[words[i][j]]]);
        }
        int x = 0;
        for (int i = 0; i < (int)v.size(); i++) {
            x = (x * 10 + v[i]);
        }
        s += x;
    }

    vector<int> v;
    for (int j = 0; j < (int)words[n - 1].size(); j++) {
        v.push_back(assignments[m[words[n - 1][j]]]);
    }
    int x = 0;
    for (int i = 0; i < (int)v.size(); i++) {
        x = (x * 10 + v[i]);
    }

    return s == x;
}

bool check_units() {
    int s = 0;
    for (int i = 0; i < n - 1; i++) {
        s += (assignments[m[words[i][words[i].size() - 1]]]);
        s %= 10;
    }

    return s == assignments[m[words[n - 1][words[n - 1].size() - 1]]];
}
ll count(int k) {  // counts the number of possible assignments
    if (k == num_unit_chars && !check_units()) return 0;
    if (k == numc) return (check() ? 1 : 0);
    ll ans = 0;

    // try each digit that has yet to be assigned
    int mask = bm;
    while (mask > 0) {
        int two_pow_i = LSOne(mask);
        mask -= two_pow_i;

        int bit = __builtin_ctz(two_pow_i);
        if (bit == 0 && (left_most_digits.count(k))) continue;

        assignments[k] = bit;  // ith bit is set
        bm -= two_pow_i;
        ans += count(k + 1);
        bm += two_pow_i;
    }
    return ans;
}
int main() {
    fast_cin();
    cin >> n;
    words.resize(n);

    for (int i = 0; i < n; i++) {
        cin >> words[i];
        if (m.find(*--words[i].end()) == m.end()) {
            m[*--words[i].end()] = numc;
            numc++;
        }
    }
    num_unit_chars = numc;
    for (int i = 0; i < n; i++) {
        for (auto c : words[i]) {
            if (m.find(c) == m.end()) {
                m[c] = numc;
                numc++;
            }
        }
        left_most_digits.insert(m[words[i][0]]);
    }

    bm = (1 << 10) - 1;
    ll ans = count(0);
    cout << ans << endl;
    return 0;
}