/**Kattis - commiteeassignment
 * Complete Search! For each person, we try all existing committees that we can add them to.
 * We also try to make a new committee. We use an array of hashtables to keep track of the
 * people each person dislikes for fast-ish determination of whether a person can be in
 * a specific committee. We also prune useless solutions with the global best. 
 * 
 * Time: O(? hard to analyse), Space: O(n^2)
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

int n, m;
int INF = 15;
string nameu, namev;
unordered_map<string, int> name_to_index;
vi coms[15];
unordered_set<int> dislikes[15];

int num_com;
int global_best;
int search(int k){ // considering the kth person, 0 index
    //cout << "k " << global_best << endl;
    if (num_com >= global_best)return INF;
    if (k == n){
        global_best = min(global_best, num_com);
        return num_com;
    }
    int ans = INF;

    // Try putting in existing com
    for (int i = 0; i < num_com; i++){ // O(num_com * n) amortized
        bool skip = false;
        for (auto person: coms[i]){
            if (dislikes[k].count(person)){
                skip = true; // if the person is disliked by k, skip
                // cout << "person " << k << " dislikes " << person << endl;
                break;
            }
        }
        if (!skip){
            coms[i].push_back(k);
            ans = min(ans, search(k + 1));
            coms[i].pop_back();
        }
    }

    // Try creating new com
    coms[num_com].push_back(k);
    num_com++;
    ans = min(ans, search(k + 1));
    num_com--;
    coms[num_com].pop_back();

    return ans;
}


int main() {
    fast_cin();
    while (true) {
        cin >> n >> m;
        if (n == 0 && m == 0) break;

        for (int i=0;i<15;i++){
            dislikes[i].clear();
            coms[i].clear();
        }
        name_to_index.clear();
        num_com = 0;
        global_best = INF;

        int names = 0;
        for (int i = 0; i < m; i++) {
            cin >> nameu >> namev;

            if (name_to_index.find(nameu) == name_to_index.end()) {
                name_to_index[nameu] = names;
                names++;
            }
            if (name_to_index.find(namev) == name_to_index.end()) {
                name_to_index[namev] = names;
                names++;
            }

            dislikes[name_to_index[nameu]].insert(name_to_index[namev]);
            dislikes[name_to_index[namev]].insert(name_to_index[nameu]);

        }

        cout << search(0) << endl;
    }

    return 0;
}