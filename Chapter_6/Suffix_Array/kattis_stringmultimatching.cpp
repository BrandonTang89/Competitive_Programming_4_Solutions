/**Kattis - stringmultimatching
 * Multiple string matching queries on a big string. We thus use a suffix array to avoid TLE. Using
 * our standard suffix array code, it is not too difficult.
 *
 * Time: O(n log n + q m log n), Space: O(n + m)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

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
    vi SA;        // Suffix Array, SA[i] selects the i-th smallest suffix
    vi LCP;       // LCP of adj sorted suffixes

    SuffixArray(string initialT) : T(initialT), n(initialT.size()) {
        constructSA();  // O(n log n)
        computeLCP();   // O(n)
    }

    // inverseSA[i] is the index of suffix T[i..n-1] in SA ie the rank of the suffix
    vi computeInverseSA() {
        vi inverseSA(n);
        for (int i = 0; i < n; ++i) {
            inverseSA[SA[i]] = i;
        }
        return inverseSA;
    }

    // Returns [lb, up] where matching indices are [SA[i] for i in range(lb, up) inclusive]
    ii stringMatching(string P) {                  // in O(m log n)
        int m = (int)P.size();                     // usually, m < n
        int lo = 0, hi = n - 1;                    // range = [0..n-1]
        while (lo < hi) {                          // find lower bound
            int mid = (lo + hi) / 2;               // this is round down
            int res = T.compare(SA[mid], m, P);    // P in suffix SA[mid]?
            (res >= 0) ? hi = mid : lo = mid + 1;  // notice the >= sign
        }
        if (T.compare(SA[lo], m, P) != 0) return {-1, -1};  // if not found
        ii ans;
        ans.first = lo;
        hi = n - 1;        // range = [lo..n-1]
        while (lo < hi) {  // now find upper bound
            int mid = (lo + hi) / 2;
            int res = T.compare(SA[mid], m, P);
            (res > 0) ? hi = mid : lo = mid + 1;  // notice the > sign
        }
        if (T.compare(SA[hi], m, P) != 0) --hi;  // special case
        ans.second = hi;
        return ans;  // returns (lb, ub)
    }                // where P is found

    // Returns the length and starting position of the longest repeated sequence in T
    ii LRS() {  // (LRS length, index)
        int idx = 0, maxLCP = -1;
        for (int i = 1; i < n; ++i)  // O(n), start from i = 1
            if (LCP[i] > maxLCP) maxLCP = LCP[i], idx = i;
        return {maxLCP, idx};
    }

    // Returns the length and starting position of the longest common substring
    // split_idx is the index of the splitting terminal character
    ii LCS(int split_idx) {  // (LCS length, index)
        int idx = 0, maxLCP = -1;
        for (int i = 1; i < n; ++i) {  // O(n), start from i = 1
            // if suffix SA[i] and suffix SA[i-1] came from the same string, skip
            if ((SA[i] < split_idx) == (SA[i - 1] < split_idx)) continue;
            if (LCP[i] > maxLCP) maxLCP = LCP[i], idx = i;
        }
        return {maxLCP, idx};
    }
};

int num_p;
string T, P;
vector<string> Ps;
vi occurances;
int main() {
    while (cin >> num_p) {
        cin.ignore();
        Ps.clear();
        for (int i = 0; i < num_p; i++) {
            getline(cin, P);
            Ps.push_back(P);
        }
        getline(cin, T);
        T += char(9);
        SuffixArray sa(T);
        for (int i = 0; i < num_p; i++) {
            occurances.clear();
            auto ans = sa.stringMatching(Ps[i]);
            if (ans == make_pair(-1, -1)) {
                cout << endl;
                continue;
            }
            for (int j = ans.first; j <= ans.second; j++) {
                occurances.push_back(sa.SA[j]);
            }
            sort(occurances.begin(), occurances.end());
            for (int j = 0; j < (int)occurances.size(); j++) {
                cout << occurances[j] << " ";
            }
            cout << endl;
        }
    }

    return 0;
}