/**Kattis - dvaput
 * "Simple" question that just asks for longest repeated substring. Since we already know how to use
 * the suffix array, we just build one and use the LCP array to get the LRS.
 * 
 * Time: O(n log n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

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
    string T;       // the initial string
    const int n;    // the length of T
    vi SA;          // Suffix Array
    vi LCP;         // of adj sorted suffixes

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


    ii LRS() {  // (LRS length, index)
        int idx = 0, maxLCP = -1;
        for (int i = 1; i < n; ++i)  // O(n), start from i = 1
            if (LCP[i] > maxLCP) maxLCP = LCP[i], idx = i;
        return {maxLCP, idx};
    }

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


int main(){
    int n;
    string T;
    cin >> n;
    cin >> T;
    T += '$';
    SuffixArray sa(T);
    cout << sa.LRS().first << endl;

    return 0;
}