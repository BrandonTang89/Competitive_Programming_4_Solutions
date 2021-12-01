/**Kattis - automatictrading
 * The question is quite easy to understand: just find the length of the longest common prefix
 * between 2 suffixes of the given string. To do so we generate an inverse suffix array and use a
 * sparse table to get RMQ on the LCP array based on the inverse suffix array. (see below)
 *
 * Time: O(n log n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

typedef pair<int, int> ii;
typedef vector<int> vi;

class SuffixArray {
   private:
    vi RA;  // rank array

    void countingSort(int k) {               // O(n)
        int maxi = max(300, n);              // up to 255 ASCII chars
        vi c(maxi, 0);                       // clear frequency table
        for (int i = 0; i < n; ++i)          // count the frequency
            ++c[i + k < n ? RA[i + k] : 0];  // of each integer rank
        for (int i = 0, sum = 0; i < maxi; ++i) {
            int t = c[i];
            c[i] = sum;
            sum += t;
        }
        vi tempSA(n);
        for (int i = 0; i < n; ++i)  // sort SA
            tempSA[c[SA[i] + k < n ? RA[SA[i] + k] : 0]++] = SA[i];
        swap(SA, tempSA);  // update SA
    }

    void constructSA() {  // can go up to 400K chars
        SA.resize(n);
        iota(SA.begin(), SA.end(), 0);  // the initial SA
        RA.resize(n);
        for (int i = 0; i < n; ++i) RA[i] = T[i];  // initial rankings
        for (int k = 1; k < n; k <<= 1) {          // repeat log_2 n times
            // this is actually radix sort
            countingSort(k);  // sort by 2nd item
            countingSort(0);  // stable-sort by 1st item
            vi tempRA(n);
            int r = 0;
            tempRA[SA[0]] = r;           // re-ranking process
            for (int i = 1; i < n; ++i)  // compare adj suffixes
                tempRA[SA[i]] =          // same pair => same rank r; otherwise, increase r
                    ((RA[SA[i]] == RA[SA[i - 1]]) && (RA[SA[i] + k] == RA[SA[i - 1] + k])) ? r
                                                                                           : ++r;
            swap(RA, tempRA);                   // update RA
            if (RA[SA[n - 1]] == n - 1) break;  // nice optimization
        }
    }

    void computeLCP() {
        vi Phi(n);
        vi PLCP(n);
        PLCP.resize(n);
        Phi[SA[0]] = -1;                      // default value
        for (int i = 1; i < n; ++i)           // compute Phi in O(n)
            Phi[SA[i]] = SA[i - 1];           // remember prev suffix
        for (int i = 0, L = 0; i < n; ++i) {  // compute PLCP in O(n)
            if (Phi[i] == -1) {
                PLCP[i] = 0;
                continue;
            }  // special case
            while ((i + L < n) && (Phi[i] + L < n) && (T[i + L] == T[Phi[i] + L]))
                ++L;  // L incr max n times
            PLCP[i] = L;
            L = max(L - 1, 0);  // L dec max n times
        }
        LCP.resize(n);
        for (int i = 0; i < n; ++i)  // compute LCP in O(n)
            LCP[i] = PLCP[SA[i]];    // restore PLCP
    }

   public:
    string T;     // the initial string
    const int n;  // the length of T
    vi SA;        // Suffix Array
    vi LCP;       // of adj sorted suffixes

    SuffixArray(string initialT) : T(initialT), n(initialT.size()) {
        constructSA();  // O(n log n)
        computeLCP();   // O(n)
    }
    vi computeInverseSA() {
        vi inverseSA(n);
        for (int i = 0; i < n; ++i) {
            inverseSA[SA[i]] = i;
        }
        return inverseSA;
    }
};
struct SparseTable {
    vector<vector<int> > ST;
    int N, K;
    SparseTable(vector<int> a) : N(a.size()) {
        K = MSB(N);
        ST.resize(K);
        ST[0] = a;
        for (int k = 1; k < K; ++k)
            for (int i = 0; i + (1 << k) <= N; ++i)
                ST[k].push_back(min(ST[k - 1][i], ST[k - 1][i + (1 << (k - 1))]));  // min
    }

    /* returns most significant bit of an integer */
    inline int MSB(unsigned int x) { return 32 - __builtin_clz(x); }

    /* Min of range (x, x + 2^k-1) and (y-2^k+1, y) */
    int query(int x, int y) {
        int k = MSB(y - x + 1) - 1;
        return min(ST[k][x], ST[k][y - (1 << k) + 1]);  // min
    }
};

string T;
int main() {
    fast_cin();
    cin >> T;
    T += '$';
    SuffixArray SA(T);

    vi inverseSA = SA.computeInverseSA();
    vi LCP = SA.LCP;
    SparseTable ST(LCP);

    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        l = inverseSA[l];
        r = inverseSA[r];
        if (l > r) swap(l, r);
        int ans = ST.query(l + 1, r);
        cout << ans << endl;
    }

    return 0;
}