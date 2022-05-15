/**Kattis - favourable
 * Another simple dp counting problem. We just use a map because its more convenient, we can use other data
 * structures if we felt like it.
 * 
 * Time: O(401), Space: O(401)
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

int num_tc;
int n;
map<int, vector<int>> adjlist;
map<int, int> type;  // 0 for internal, 1 for favourable, 2 for unfavourable

ll memo[401];
ll dp(int page){
    if (memo[page] != -1) return memo[page];
    if (type.find(page) != type.end()){
        if (type[page] == 1) return 1;
        else return 0;
    }

    return memo[page] = dp(adjlist[page][0]) + dp(adjlist[page][1]) + dp(adjlist[page][2]);

}
int main() {
    fast_cin();
    cin >> num_tc;
    for (int tc = 0; tc < num_tc; tc++) {
        cin >> n;
        adjlist.clear();
        type.clear();
        memset(memo, -1, sizeof memo);
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        for (int i = 0; i < n; i++) {
            string s, line; // split line by spaces
            getline(cin, line);
            vector<string> v;
            istringstream ss(line);
            while (ss >> s) {
                v.emplace_back(s);
            }

            if (v.size() == 2) {
                type[stoi(v[0])] = (v[1] == "favourably") ? 1 : 2;
            } else {
                adjlist[stoi(v[0])].emplace_back(stoi(v[1]));
                adjlist[stoi(v[0])].emplace_back(stoi(v[2]));
                adjlist[stoi(v[0])].emplace_back(stoi(v[3]));
            }
        }
        cout << dp(1) << endl;
    }


    return 0;
}