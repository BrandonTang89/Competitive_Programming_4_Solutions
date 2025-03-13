#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);


int main(){
    int tc;
    cin >> tc;
    while (tc--){
        int x;
        cin >> x;
        int total_length = 32 - __builtin_clz(x);
        int pc = __builtin_popcount(x);
        if (pc == 1 || pc == total_length) {
            cout << -1 << endl;
            continue;
        }

        // negation and we change a zero to one
        int ans = 0;
        for (int i = 0; i < total_length; i++) {
            if (!(x & (1 << i))) {
                ans |= (1 << i);
            }
        }

        for (int i = 0; i < total_length; i++) {
            if (!(ans & (1 << i))){
                ans |= (1 << i);
                break;
            }
        }

        cout << ans << endl;
        assert((x + ans) > x^ans);
        assert((x ^ ans) + ans > x);
        assert((x ^ ans) + x > ans);
    }

    return 0;
}