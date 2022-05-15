/**Kattis - golfbot
 * Pretty easy question (if you know about FFT and Convolutions). We just keep a frequency array of where the
 * golf club can hit with 1 shot, and 2 shots (by convolving with itself). then for each hole, check if its
 * reachable.
 * 
 * Time: O(20000 log 20000), Space: O(20000)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

typedef complex<long double> cd;
const double PI = acos(-1.0);

int reverseBit(int x, int m) {  // m is the binary length of A.size()-1
    int ret = 0;
    for (int k = 0; k < m; k++) {
        if (x & (1 << k)) ret |= (1 << (m - 1 - k));
    }
    return ret;
}

void FFT(vector<cd> &A) {  // evaulates A at the nth roots of unity for n = 2^k >= A.size()
    int m = 0;
    while ((1 << m) < (int)A.size()) m++;
    A.resize(1 << m, 0);                       // size of A should be a power of 2, resizes A
    for (int k = 0; k < (int)A.size(); k++) {  // sort to bit-reversal permutation
        if (k < reverseBit(k, m)) swap(A[k], A[reverseBit(k, m)]);
    }

    for (int n = 2; n <= (int)A.size(); n <<= 1) {
        for (int k = 0; 2 * k < n; k++) {
            // we are going to get the kth and k+n/2th element of each length n block
            cd x = cd(cos(2 * PI * k / n), sin(2 * PI * k / n));  // nth root of unity
            for (int j = 0; j < (int)A.size(); j += n) {  // apply to every sub-array of length n
                cd A0k = A[k + j];                        // previously computed
                cd A1k = A[k + j + n / 2];                // previously computed
                A[k + j] = A0k + x * A1k;
                A[k + j + n / 2] = A0k - x * A1k;
            }
        }
    }
}

void IFFT(vector<cd> &A) {  // Size of A should be a power of 2
    for (auto &p : A) p = conj(p);
    FFT(A);
    for (auto &p : A) p = conj(p);  // not needed if IFFT only used for multiplication
    for (auto &p : A) p /= A.size();
}

vector<ll> multiply(vector<ll> p1, vector<ll> p2) {
    int n = 1;
    while (n < (int)p1.size() + (int)p2.size() - 1) n <<= 1;  // n is a power of 2
    vector<cd> A(p1.begin(), p1.end());
    vector<cd> B(p2.begin(), p2.end());
    A.resize(n, 0);
    B.resize(n, 0);

    FFT(A);  // Evaluate A at the nth roots of unity
    FFT(B);  // Evaluate B at the nth roots of unity

    vector<cd> C(n, 0);
    for (int i = 0; i < n; i++)
        C[i] = A[i] * B[i];  // C = A * B, we get C at the nth roots of unity
    IFFT(C);                 // convert back to coefficient form

    vector<ll> ans(n, 0);
    for (int i = 0; i < n; i++) ans[i] = round(C[i].real());
    ans.resize(p1.size() + p2.size() - 1);

    return ans;
}

vector<ll> f(200001, 0);
vector<ll> holes;
int main(){
    int n, m;
    cin >> n;

    for (int i = 0; i < n; i++){
        int a;
        cin >> a;
        f[a]++;   
    }

    ll ans = 0;
    cin >> m;
    for (int i = 0; i < m; i++){
        int a;
        cin >> a;
        holes.push_back(a);
    }

    vector<ll>ff = multiply(f, f);
    for (int i = 0; i < m; i++){
        int a = holes[i];
        if (ff[a] != 0 || f[a] != 0)ans++;
    }

    cout << ans << endl;

    return 0;
}