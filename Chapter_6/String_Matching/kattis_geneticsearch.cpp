/**Kattis - geneticsearch
 * It is probably overkill to use KMP for this string matching problem, but since it is an easy
 * problem, its a good cchance to write a proper KMP implementation.
 * 
 * Time: O((n + m) * m), Space: O(m^2 + n)
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

vector<int> KMP(string T, string P) {  // Return indices of matches of P in T
    int n = T.size();
    int m = P.size();
    vector<int> b(m + 1, 0), ans;

    // KMP Preprocessing
    int i = 0, j = -1;
    b[0] = -1;
    while (i < m) {
        while ((j >= 0) && (P[i] != P[j])) j = b[j];
        i++;
        j++;
        b[i] = j;  // i is up to 1 larger than m
    }

    // KMP Searching
    i = 0;
    j = 0;
    while (i < n) {
        while ((j >= 0) && (T[i] != P[j])) j = b[j];
        i++;
        j++;
        if (j == m) {
            ans.push_back(i - j);
            j = b[j];
        }
    }

    return ans;
}

string P, T;
unordered_set<string> s;
int main() {
    while (true) {
        cin >> P;
        if (P == "0") break;
        cin >> T;

        int ans1 = 0, ans2 = 0, ans3 = 0;

        ans1 = KMP(T, P).size();

        for (int i = 0; i < (int)P.size(); i++) {
            s.insert(P.substr(0, i) + P.substr(i + 1));  // Remove i-th character
        }
        for (auto it = s.begin(); it != s.end(); it++) {
            ans2 += KMP(T, *it).size();
        }

        s.clear();
        char avail[] = {'A', 'T', 'C', 'G'};
        for (int i = 0; i <= (int)P.size(); i++) {
            for (int j = 0; j < 4; j++) {
                // insert avail[j] into the ith position
                // cout << P.substr(0, i) + avail[j] + P.substr(i) << endl;
                s.insert(P.substr(0, i) + avail[j] + P.substr(i));
            }
        }
        for (auto i : s) {
            ans3 += KMP(T, i).size();
        }
        s.clear();

        cout << ans1 << " " << ans2 << " " << ans3 << endl;
    }

    return 0;
}
