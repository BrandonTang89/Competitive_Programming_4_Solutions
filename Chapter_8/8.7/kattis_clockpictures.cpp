/**Kattis - clockpictures
 * This is a pretty straightforward question. Only thing new is the concept of
 * minimum lexicographic rotation. I will learn about the algorithm in the future,
 * it is apparently a modification of KMP. But for now.. the copy pasted from
 * wikipedia version works decently well!
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
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int n;
vector<int> v1, v2, d1, d2;

int least_rotation(vector<int> v) {
    for (int i = 0; i < n; i++) {
        v.emplace_back(v[i]);
    }

    int len = v.size();
    vector<int> f = vector<int>(len, -1);
    int k = 0;
    for (int j = 1; j < len; j++) {
        int sj = v[j];
        int i = f[j - k - 1];
        while (i != -1 && sj != v[k + i + 1]) {
            if (sj < v[k + i + 1]) k = j - i - 1;
            i = f[i];
        }
        if (sj != v[k + i + 1]) {
            if (sj < v[k]) k = j;
            f[j - k] = -1;
        } else {
            f[j - k] = i + 1;
        }
    }
    return k;
}
int main() {
    cin >> n;
    v1.resize(n);
    v2.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> v1[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> v2[i];
    }
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());

    for (int i = 1; i < n; i++) {
        d1.push_back(v1[i] - v1[i - 1]);
    }
    d1.push_back(360000 - (v1[n - 1] - v1[0]));
    for (int i = 1; i < n; i++) {
        d2.push_back(v2[i] - v2[i - 1]);
    }
    d2.push_back(360000 - (v2[n - 1] - v2[0]));


    rotate(d1.begin(), d1.begin() + least_rotation(d1), d1.end());
    rotate(d2.begin(), d2.begin() + least_rotation(d2), d2.end());
    
    if (d1 == d2) {
        cout << "possible" << endl;
    } else {
        cout << "impossible" << endl;
    }

    return 0;
}