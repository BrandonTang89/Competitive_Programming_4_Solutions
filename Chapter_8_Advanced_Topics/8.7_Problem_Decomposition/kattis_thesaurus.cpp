/**Kattis - thesaurus
 * Somewhat interesting problem. We need to substitute each word with the smallest word in the
 * equivalence class. We can do this efficiently using a modified UFDS that unions shorter words
 * above longer words such that the representative of each set is the shortest word in each set.
 * The rest is just a matter of mapping words to indices etc.
 * 
 * Time: O((n + m) * log m), Space: O(n + m)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

unordered_map<string, int> wordToIndex;
vector<string> indexToWord;
class UnionFind {  // OOP style
   private:
    vi p;

   public:
    UnionFind(int N)
    {
        p.assign(N, 0);
        for (int i = 0; i < N; ++i) p[i] = i;
    }

    int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
    bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }

    void unionSet(int i, int j)
    {
        if (isSameSet(i, j)) return;         // i and j are in same set
        int x = findSet(i), y = findSet(j);  // find both rep items
        if (indexToWord[x].length() < indexToWord[y].length())
            swap(x, y);  // keep length x longer than length y
        p[x] = y;        // set x under y
    }
};

vector<string> essay;
int main()
{
    fast_cin();
    int n, m;
    cin >> n >> m;
    essay.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> essay[i];
    }

    int numWords = 0;
    UnionFind uf(m * 2);
    for (int i = 0; i < m; i++) {
        string u, v;
        cin >> u >> v;
        if (wordToIndex.find(u) == wordToIndex.end()) {
            wordToIndex[u] = numWords++;
            indexToWord.push_back(u);
        }
        if (wordToIndex.find(v) == wordToIndex.end()) {
            wordToIndex[v] = numWords++;
            indexToWord.push_back(v);
        }
        uf.unionSet(wordToIndex[u], wordToIndex[v]);
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        string u = essay[i];
        if (wordToIndex.find(u) == wordToIndex.end()) {
            wordToIndex[u] = numWords++;
            indexToWord.push_back(u);
        }
        if (wordToIndex[u] >= 2 * m)
            ans += u.length();
        else
            ans += indexToWord[uf.findSet(wordToIndex[u])].length();
    }
    cout << ans << endl;

    return 0;
}