/**Kattis - sound
 * A sliding window with deque question. Use the multiply by -1 trick to get the maximum
 * value at each subarray position. Remember to ouput NONE is no answer.
 * 
 * Time: O(n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n, k, c;

vector<int> SlidingWindow(vector<int> &A, int n, int K){
    vector<int> ans;
    deque<pair<int, int>> window;
    for (int i=0; i<n; ++i){
        while (!window.empty() && window.back().first >= A[i]){
            window.pop_back();
        }
        window.push_back({A[i], i});
        while (window.front().second <= i-K){
            window.pop_front();
        }
        if (i+1 >= K){
            ans.push_back(window.front().first);
        }
    }
    return ans;
}
int main(){
    cin >> n >> k >> c;
    vector<int> V;
    for (int i=0; i<n; ++i){
        int x;
        cin >> x;
        V.push_back(x);
    }

    vector<int> ans = SlidingWindow(V, n, k);
    for (int i=0; i<n; i++){
        V[i] *= -1;
    }
    vector<int> ans2 = SlidingWindow(V, n, k);

    bool none = true;
    for (int i=0; i<(int) ans.size(); ++i){
        ans2[i] *= -1;
        if (ans2[i] - ans[i] <= c){
            cout << i+1 << endl;
            none = false;
        }
    }
    if (none){
        cout << "NONE" << endl;
    }
    return 0;
}