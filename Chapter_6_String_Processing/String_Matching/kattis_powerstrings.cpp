/**Kattis - powerstrings
 * Observation 1:
 *  if a^n = s, then a is the string prefix of s such that it has length equal to the number of
 *  chars before the second match of s in s+s.
 *  
 *  Proof: Initially we just know that A is the prefix of S+S
 *  S+S : A----
 *  S   : ----
 *  but that means its also the prefix of S
 *  So we get 
 *  A-----
 *   A----
 *  Since the strings match, AA must be a prefix of S+S
 *  So we get
 *  AA----
 *   A----
 *  thus meaning that AA is a prefix of S. 
 * 
 *  We continue this repeatedly ending with s = aaaaaa..aaa
 * 
 *  Time: O(len(s)), Space: O(len(s))
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

vector<int> KMP(string T, string P) {  // Return indices of matches of P in T
    int n = T.size();
    int m = P.size();
    vector<int> b(m + 1, 0), ans;

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
            if ((int) ans.size() == 2)return ans; // speed up since we only need the second match
        }
    }

    return ans;
}

string s;
int main(){
    fast_cin();
    while (1){
        cin >> s;
        if (s == ".")break;
        cout << s.length()/KMP(s+s, s)[1] << endl;
    }
    return 0;
}