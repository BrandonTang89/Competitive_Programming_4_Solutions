/**Kattis - aplusb
 * A more annoying generalised version of "all possible sums". We offset all values by 50000 first
 * to account for negative numbers. We keep A as a frequency array with the offset. Then we do a
 * convolution of f on itself to get ff[i] = number of ways to select j, k from A such that j+k=i.
 * Notice that we have Aj+Aj as part of the convolution which we do not want. Thus for each a in A,
 * we will reduce 1 from ff[2*(a+50000)].
 *
 * The main bulk of the answer comes from getting the number of (x, y) such that x + y = a for each
 * a in A, which we know to be ff[a + 2*50000]. However.. notice that if there exist some 0s in A,
 * then it could be that for a, we are doing 0 + x = x. In this case, the 2 x's may be the same Ak
 * for some k, violating the pairwise distinct property.
 *
 * What we need to do is to remove the 0s before we start. We can still get all x+y=a where x,y,a
 * are not 0. However, for the 0s, we have a few cases:
 * 1. -x + x = 0,  the number of such cases is ff[2*50000]*(number of zeros)
 * 2. x + 0 = x, the number of such cases is f[x]*number of zeros*(f[x]-1)
 * 3. 0 + x = x, the number of such cases is number of zeros*f[x]*(f[x]-1)
 * 4. 0 + 0 = 0, the number of such cases is number of zeros*(number of zeros-1)*(number of zeros-2)
 *
 * Time: O(n log n), Space: O(n + A.size()) where n = 100000.
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

vector<ll> f(100001, 0);
vector<ll> A;
ll n, zero_counter = 0;
int main() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        if (a == 0) {
            zero_counter++;
            continue;
        }
        A.emplace_back(a);
        f[a + 50000]++;
    }

    vector<ll> ff = multiply(f, f);

    for (auto a : A) {
        ff[2 * (a + 50000)]--;
    }

    ll ans = 0;
    for (auto a : A) {
        ans += ff[a + 2 * 50000];  // x + y = a
    }
    ans += ff[0 + 2 * 50000] * zero_counter;  // -x + x = 0

    for (int i = 0; i <= 100000; i++) {
        if (f[i] != 0) {
            ans += f[i] * zero_counter * (f[i] - 1) * 2;  // a + 0 = a or 0 + a = a
        }
    }
    ans += (zero_counter * (zero_counter - 1) * (zero_counter - 2));  // 0 + 0 = 0
    cout << ans << endl;

    return 0;
}