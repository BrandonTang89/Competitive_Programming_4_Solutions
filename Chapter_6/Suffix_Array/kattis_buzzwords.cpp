/**Kattis - buzzwords
 * This an interesting application of suffix array. Notice that if in the LCP vector, we have a 3
 * long contiguous subarray that is at least 1, then we have 3+1=4 suffixes with the same length 1
 * prefix. This is because the first 2 have the same length 1 prefix, and the third has the same
 * length 1 prefix as the second, meaning the first 3 have the same length 1 prefix and so on so
 * forth.
 *
 * Now, since common prefixes in suffixes implies repeated substrings, to find the largest
 * number of repetitions of a x length substring, we just find the longest contiguous subarray
 * of LCP with a value >= x.
 * 
 * Time: O(n^2), Space: O(n)
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

string s;
int main() {
    while (true) {
        getline(cin, s);
        if (s == "") break;
        s.erase(remove_if(s.begin(), s.end(), ::isspace), s.end());
        s += char(9);

        int n = s.size();
        SuffixArray sa(s, n);
        vi LCP = sa.LCP;

        for (int i = 1; i <= n; i++) {  // find the longest subarray in LCP with elements at least i
            int cur = 0, maxi = 0;
            for (int j = 0; j < n; j++) {
                if (LCP[j] >= i) {
                    cur++;
                    maxi = max(maxi, cur);
                } else {
                    cur = 0;
                }
            }
            if (maxi >= 1) {
                cout << maxi + 1 << endl;
            } else {
                break;
            }
        }
        cout << endl;
    }

    return 0;
}