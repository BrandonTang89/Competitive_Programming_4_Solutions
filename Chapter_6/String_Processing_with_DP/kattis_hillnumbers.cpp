/**Kattis - hillnumbers
 * A rather tedious question. One needs to be very meticulous in ensuring the right transitions
 * are made. The idea isn't hard but the specifics can be tricky to debug :(
 * 
 * Time: O(log10(n)), Space: O(1)
 */

#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
string s;

bool ishillnumber(string n){
    bool rising = true;
    for (int i=1; i< (int) n.size(); i++){
        if (n[i]<n[i-1]) rising = false;
        if (rising == false){
            if (n[i] > n[i-1]) return false;
        }
    }

    return true;
}
ll memo[19][10][2][2];
ll dp(int pos, int prev_digit, bool is_rising, bool is_lower){
    if (pos == (int) s.size()) return 1;
    auto &ans = memo[pos][prev_digit][is_rising][is_lower];
    if (ans != -1) return ans;

    
    ans = 0;
    if (is_rising){
        if (is_lower){
            // cur digit must be at least as great as the prev_digit
            for (int i=0; i<=9; i++){
                if (i >= prev_digit) ans += dp(pos+1, i, true, true);
                else ans += dp(pos+1, i, false, true);
            }
        }
        else {
            // cur digit ranges from prev_digit to s[pos]
            for (int i=0; i<=9; i++){
                if (i > s[pos]-'0') break;
                if (i == s[pos]-'0'){
                    if (i >= prev_digit) ans += dp(pos+1, i, true, false);
                    else ans += dp(pos+1, i, false, false);
                }
                else {
                    if (i >= prev_digit) ans += dp(pos+1, i, true, true);
                    else ans += dp(pos+1, i, false, true);
                }
            }
        }
    }
    else{ // is_rising == false
        if (is_lower){
            // cur digit lower to equal to prev digit
            for (int i=0; i<=prev_digit; i++){
                ans += dp(pos+1, i, false, true);
            }
        }
        else{
            // cur digit ranges from 0 to minimum of prev_digit and s[pos]
            for (int i=0; i<=min(prev_digit, s[pos]-'0'); i++){
                if (i == s[pos]-'0') ans += dp(pos+1, i, false, false);
                else ans += dp(pos+1, i, false, true);
            }
        }
    }
    // printf("%d %d %d %d %lld\n", pos, prev_digit, is_rising, is_lower, ans);
    return ans;
}
int main(){
    /*
    assert(ishillnumber("1234"));
    assert(ishillnumber("1243"));
    assert(ishillnumber("33322111"));*/
    cin >> s;
    if (!ishillnumber(s)){
        cout << -1 << endl;
        return 0;
    }
    memset(memo, -1, sizeof memo);
    ll ans = dp(0, 0, true, false);

    ans -= 1; // 000...000
    cout << ans << endl;
    return 0;
}