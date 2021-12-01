/**Kattis - aliens
 * This question involves first constructing the Suffix array and LCP array. Then we perform
 * 2 concurrent sliding windows on SA (of size k) and on LCP (of size k-1), both windows
 * end at the same element. The minimum of the window on LCP at any point gives the longest
 * common prefix possible from the prefixes in the sliding window on SA. As we slide the windows
 * we keep track of the minimum of the LCP window and if it is larger than our current answer,
 * we update our answer to that, and we update the right most position based on the largest
 * element in the SA window.
 *
 * Implementation wise, we use a multiset for the sliding window on LCP since we can have multiple
 * repeated elements and just a set for the sliding window on SA since we can only have unique
 * elements. We could improve this (to O(n)) by using a proper sliding window with a deque that we
 * maintain sorted order of and perform lazy deletion, but this is overkill and would make the
 * source code even more complex.
 *
 * Time: O(n log m), Space: O(n + m)
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
    vi SA;        // Suffix Array
    vi LCP;       // of adj sorted suffixes

    SuffixArray(string initialT, const int _n) : T(initialT), n(_n) {
        constructSA();  // O(n log n)
        computeLCP();   // O(n)
    }
};

int main() {
    int k;
    string T;
    while (1) {
        cin >> k;
        if (k == 0) break;

        cin >> T;
        if (k == 1) {
            cout << T.size() << " " << 0 << endl;
            continue;
        }
        T += "$";
        SuffixArray SA(T, T.size());
        vi LCP = SA.LCP;

        multiset<int> S_LCP;  // LCP[i],
        set<int> S_SA;        // SA[i]
        for (int i = 1; i < k; i++) S_LCP.insert(LCP[i]);
        for (int i = 0; i < k; i++) {
            S_SA.insert(SA.SA[i]);
        }

        int max_lcp = *S_LCP.begin();
        int max_i = *(--S_SA.end());
        for (int i = k; i < (int)T.size(); i++) {
            S_LCP.erase(S_LCP.find(LCP[i - (k - 1)]));
            S_SA.erase(SA.SA[i - (k)]);
            S_LCP.insert(LCP[i]);
            S_SA.insert(SA.SA[i]);
            if (*S_LCP.begin() > max_lcp) {
                max_lcp = *S_LCP.begin();
                max_i = *(--S_SA.end());
            } else if (*S_LCP.begin() == max_lcp) {
                max_i = max(max_i, *(--S_SA.end()));
            }
        }

        if (max_lcp == 0)
            cout << "none" << endl;
        else
            cout << max_lcp << " " << max_i << endl;
    }

    return 0;
}