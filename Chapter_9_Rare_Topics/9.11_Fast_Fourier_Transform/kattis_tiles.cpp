/**Kattis - tiles
 * Note that if we let the lengths of the triangles in the 4 corners be of length a,b,c,d such that we have
 * 2 triangles (a,b) 2 triangles (c,d), the area of the parallogram is (a+d)(b+c) - ab - cd = ac + bd. So we
 * are looking for the number of (ac, bd) such that n = ac + bd. We can see that somehow using convolutions
 * helps us. But we need to know how many ways we can represent x = ac for some integers ac, but this is just
 * the number of divisors of x. So we can just do the convolution on the array of number of divisors for
 * each integer! Then we're more or less done.
 * 
 * Time: O(50000 log 50000 + num_tc * 500000), Space: O(500000)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

vector<ll> numDivisors;
void fill_numDivisors(int _upperbound=500001){
    numDivisors.assign(_upperbound+1, 0);
    for (int i=1; i<= _upperbound; i++){
        for (int j=i; j<= _upperbound; j+=i){
            numDivisors[j] += 1;
        }
    }
}
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

int main(){
    fill_numDivisors();

    vector<ll> ff = multiply(numDivisors, numDivisors);

    int num_tc;
    cin >> num_tc;
    while (num_tc--){
        ll max_idx = -1, max_val = -1;
        int lo, hi;
        cin >> lo >> hi;
        for (int i=lo; i<=hi; i++){
            if (ff[i] > max_val){
                max_val = ff[i];
                max_idx = i;
            }
        }
        cout << max_idx << " " << max_val << endl;
    }
    return 0;
}