/**Kattis - distinctivecharacter
 * Relatively easy problem after making the observation that we should do a multisource BFS from
 * each of the initial numbers and finding the number that is the furthest away. The edges exist
 * between numbers that differ by exactly 1 bit, the nodes are all the numbers in [0 .. 2^k - 1].
 *
 * Time: O(k * 2^k), Mem: O(2^k)
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

int n, k;
queue<int> q;
vector<int> dist;
int main()
{
    fast_cin();
    cin >> n >> k;
    dist.assign((1 << k), 1e9);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        int x = 0;
        for (int j = s.size() - 1; j >= 0; j--) {
            if (s[j] == '1') {
                x |= (1 << (s.size() - j - 1));
            }
        }
        q.push(x);
        dist[x] = 0;
    }

    // Multisource BFS
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = 0; i < k; i++) {
            int y = x ^ (1 << i);
            if (dist[y] > dist[x] + 1) {
                dist[y] = dist[x] + 1;
                q.push(y);
            }
        }
    }

    int ansdist = 0;
    int ans = -1;
    for (int i = 0; i < (1 << k); i++) {
        if (dist[i] > ansdist) {
            ansdist = dist[i];
            ans = i;
        }
    }
    string s = bitset<32>(ans).to_string();
    cout << s.substr(s.size() - k) << endl;

    return 0;
}