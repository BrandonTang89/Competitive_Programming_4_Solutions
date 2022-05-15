/**Kattis - magicallights
 * A pretty interesting problem. First we use DFS to flatten the rooted tree such that each subtree is in a
 * contiguous block of the fenwick tree. However we now need to determine how to represent the colours in
 * the fenwick tree. One way would be to use 100 fenwick trees, one for each colour. However, we notice that
 * we are wasting a lot of space because each fenwick tree element is only either 0 or 1... This will TLE.
 * A better way is to combine this idea with a bitmask idea. Since we don't need the actual range sum but rather
 * just whether the number of each colour at the subtree is odd or not, if we could use a 100 bit long bitmask,
 * finding the number of magical colours just involves finding the number of 1s in the range XOR of the segment
 * of the fenwick tree representing the subtree. However, our longest (at least that I know how to use properly)
 * native datatype is the long long which is only 64 bits long, so we use 2 fenwick trees of long longs. The first
 * will store the bitmask for the first 50 colours while the second will store the bitmask for the last 50 colours.
 * 
 * Study how we modified the fenwick tree to do XOR calculations.
 * 
 * Time: O(N log N + Q log N)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define LSOne(S) ((S) & -(S))                    // the key operation
typedef vector<ll> vll;

class FenwickTree {                              // index 0 is not used
private:
  vll ft;                                        // internal FT is an array
public:
  FenwickTree(int m) { ft.assign(m+1, 0); }      // create an empty FT

  ll rsq(int j) {                                // returns RSQ(1, j)
    ll sum = 0;
    for (; j; j -= LSOne(j))
      sum ^= ft[j];
    return sum;
  }

  ll rsq(int i, int j) { return rsq(j) ^ rsq(i-1); } // inc/exclusion
  void update(int i, ll v) {
    for (; i < (int)ft.size(); i += LSOne(i))
      ft[i] ^= v;
  }
};

int n, q;
vector<int> colours, parents, visited;
vector<vector<int>> adjlist;
vector<pair<int, int>> flatten_section;
vector<FenwickTree> magical_colours;

int label_counter = 1;
void dfs(int u){
    visited[u] = 1;
    flatten_section[u].first = label_counter;
    label_counter++;

    for (int v : adjlist[u]){
        if (!visited[v]){
            dfs(v);
        }
    }
    flatten_section[u].second = label_counter-1;
}


int main(){
    fast_cin();
    cin >> n >> q;
    magical_colours.assign(2, FenwickTree(n));
    colours.resize(n);
    flatten_section.resize(n);
    adjlist.assign(n, vi());
    parents.assign(n, -1);
    for (int i=0; i<n; i++){
        cin >> colours[i];
    }
    for (int i=1; i<n; i++){
        cin >> parents[i];
        parents[i]--;
        adjlist[i].emplace_back(parents[i]);
        adjlist[parents[i]].emplace_back(i);
    }
    visited.assign(n, 0);
    dfs(0);

    for (int i=0; i<n; i++){
        FenwickTree &ft = magical_colours[(colours[i] <= 50) ? 0 : 1];
        int pos = (colours[i] <= 50) ? colours[i] : colours[i]-50;
        ft.update(flatten_section[i].first, 1LL << pos);
    }

    for (int query=0; query<q; query++){
        int a, b; 
        cin >> a >> b;
        if (a == 0){ // query
            b--;
            int num_magic = 0;
            for (int i=0; i<=1; i++){
                num_magic += __builtin_popcountll(magical_colours[i].rsq(flatten_section[b].first, flatten_section[b].second));
            }
            cout << num_magic << endl;
        }
        else{
            b--;
            FenwickTree &ft = magical_colours[(colours[b] <= 50) ? 0 : 1];
            int pos = (colours[b] <= 50) ? colours[b] : colours[b]-50;
            ft.update(flatten_section[b].first, (1LL << pos));

            colours[b] = a;
            FenwickTree &ft2 = magical_colours[(colours[b] <= 50) ? 0 : 1];
            pos = (colours[b] <= 50) ? colours[b] : colours[b]-50;
            ft2.update(flatten_section[b].first, 1LL << pos);
        }
    }


    return 0;
}