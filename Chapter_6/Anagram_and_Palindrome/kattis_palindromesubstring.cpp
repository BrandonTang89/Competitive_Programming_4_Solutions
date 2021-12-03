/**Kattis - palindromesubstring
 * Here we are checking for all non-trivial palindrome substrings in a given string. Since there
 * are multiple overlapping sub-problems when checking for palindromic substrings, we use DP
 * with state (i,j) which are the starting and ending points of the substring. Then for each possible
 * substring, we check if it is a palindrome. If it is, we add it to a set which is used to sort
 * and make the results unique.
 * 
 * Time: O(n^2), Space: O(n^2)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

string s;
int memo[1009][1009];
bool isPali(int i, int j){ // determine if the substring i, j is palindrome (DP)
    if (i == j) return true;
    if (i + 1 == j) return (memo[i][j] = (s[i] == s[j]));
    if (memo[i][j] != -1) return memo[i][j];
    memo[i][j] = ((s[i] == s[j]) && (isPali(i + 1, j - 1)));
    return memo[i][j];
}

int main(){
    set<string> ans;
    while (cin >> s){
        ans.clear();
        memset(memo, -1, sizeof memo);
        for (int l=0; l< (int) s.size(); l++){
            for (int r=l+1; r< (int) s.size(); r++){
                if (isPali(l, r)){
                    ans.insert(s.substr(l, r-l+1));
                }
            }
        }
        for (auto it: ans){
            cout << it << endl;
        }
        cout << endl;
    }
    return 0;
}