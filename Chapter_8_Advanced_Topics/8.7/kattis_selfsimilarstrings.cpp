/**Kattis - selfsimilarstrings
 * Using KMP is overkill for this question, but since we have the library code already,
 * this is easier. We could do a binary search for the answer, but thats also overkill. So
 * overall we just try all answers from d=1 to d=length s -1. For each potential answer,
 * we check if all substrings of that length can be matched at least twice in S.
 * 
 * Time: O(length(S)^3), Space: O(length s)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

vector<int> KMP(string T, string P) {  // Return indices of matches of P in T
    int n = T.size();
    int m = P.size();
    vector<int> b(m + 1, 0), ans;      // Back Table

    // KMP Preprocessing
    int i = 0, j = -1;
    b[0] = -1;
    while (i < m) {
        while ((j >= 0) && (P[i] != P[j])) j = b[j];
        i++;
        j++;
        b[i] = j;  // i is up to 1 larger than m
    }

    // KMP Searching
    i = 0;
    j = 0;
    while (i < n) {
        while ((j >= 0) && (T[i] != P[j])) j = b[j];
        i++;
        j++;
        if (j == m) {
            ans.push_back(i - j);
            j = b[j];
        }
    }

    return ans;
}

int main() {
    string s;
    while (cin >> s) {
        int d = 0;
        bool fail = false;
        for (d = 1; d <= (int)s.size() && !fail ; d++) {
            for (int i=0; i<= (int) s.size() - d; i++){
                string T = s.substr(i, d);
                vi matches = KMP(s, T);

                if (matches.size() == 1){
                    fail = true;
                    break;
                };
            }
            
        }
        cout << d-2 << endl;
    }

    return 0;
}