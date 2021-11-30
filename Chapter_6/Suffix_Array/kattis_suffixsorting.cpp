/**Kattis - suffixsorting
 * My first string processing with "hardcore" data structures! Note that while not explicitly
 * referred to in the constructSA method, a terminal character is required to deal with sorting in
 * the situation where a suffix is a prefix of another suffix. With a terminal character, this will
 * never happen since the terminal character is only present once in the string at the end. At least
 * I think thats why the terminal character is required. Other than that, just copy
 * code from CP4 for suffix array construction.
 * 
 * Note that our string can have any number of funny characters, so we use the annoying getline
 * function along with char(9) as our terminal character since it is guaranteed to be smaller
 * than any other character that can be in the string.
 * 
 * Time: O(n log n + num_q), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;

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

   public:
    const char* T;  // the input string
    const int n;    // the length of T
    vi SA;          // Suffix Array

    SuffixArray(const char* initialT, const int _n) : T(initialT), n(_n) {
        constructSA();  // O(n log n)
    }
};

#define MAX_N 200000
char s[MAX_N];

int main() {
    while (cin.getline(s, MAX_N)) {
        // printf("hello\n");
        int n = strlen(s);
        // printf("%s %d\n", s, n);
        s[n++] = char(9);
        SuffixArray sa(s, n);

        int num_q, q;
        cin >> num_q;
        for (int q_num = 0; q_num < num_q; q_num++) {
            cin >> q;
            if (q_num > 0) cout << " ";
            cout << sa.SA[q + 1];
        }
        cout << endl;

        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        memset(s, 0, sizeof(s));
    }

    return 0;
}