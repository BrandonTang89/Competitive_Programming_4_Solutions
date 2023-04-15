/**Kattis - wordladder2
 * Meet in the middle BFS + string manipulation. We first do a BFS from the source word to all words
 * reachable that are in the dictionary or of hamming distance 1 from a word in the dictionary. Then
 * we do a BFS from the target word in the same way. Then we check for each word that is hamming
 * distance 1 from a word in the dictionary, if we can get a better path from the source word to
 * that word and from that word to the target word. If we can, we update the answer.
 *
 * Time: O(26*8*N), Space: O(26*8*N) // roughly the size of the extended dictionary, assume sparse
 * graph
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

int n;
set<string> extended_dict;
vector<string> v;
unordered_set<string> initial_dict;
unordered_map<string, vector<string>> adjlist;
unordered_map<string, int> dist, dist2;
queue<string> q;
int main()
{
    fast_cin();
    cin >> n;
    v.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        initial_dict.insert(v[i]);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (int)v[i].size(); j++) {
            string s = v[i];
            for (char c = 'A'; c <= 'Z'; c++) {
                s[j] = c;
                extended_dict.insert(s);
                adjlist[v[i]].push_back(s);
                adjlist[s].push_back(v[i]);
            }
        }
    }
    dist[v[0]] = 0;
    q.push(v[0]);
    while (!q.empty()) {
        string s = q.front();
        q.pop();

        for (auto &x : adjlist[s]) {
            if (dist.find(x) == dist.end()) {
                dist[x] = dist[s] + 1;
                if (initial_dict.find(x) != initial_dict.end()) q.push(x);
            }
        }
    }
    dist2[v[1]] = 0;
    q.push(v[1]);
    while (!q.empty()) {
        string s = q.front();
        q.pop();

        for (auto &x : adjlist[s]) {
            if (dist2.find(x) == dist2.end()) {
                dist2[x] = dist2[s] + 1;
                if (initial_dict.find(x) != initial_dict.end()) q.push(x);
            }
        }
    }

    string word = "0";
    int ans = (dist.find(v[1]) == dist.end()) ? 1e8 : dist[v[1]];
    for (auto &x : extended_dict) {
        if (initial_dict.find(x) != initial_dict.end()) continue;
        if (dist.find(x) == dist.end()) continue;
        if (dist2.find(x) == dist2.end()) continue;
        if (dist[x] + dist2[x] < ans) {
            ans = dist[x] + dist2[x];
            word = x;
        }
    }

    if (ans == 1e8) {
        cout << "0\n-1" << endl;
    }
    else {
        cout << word << endl;
        cout << ans << endl;
    }

    return 0;
}