/**Kattis - moretriangles
 * Kinda similar to the rest of the all possible sums questions. Here we just operate on modulo n.
 * Also, we have the condition that A <= B.. We could just divide the answer by 2, but what about the cases
 * where A = B? We need to not remove them. So how? Well we can just add the number of cases where A + A = C
 * then after that divide by 2.
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
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

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
    // for (auto &p : A) p = conj(p);  // not needed if IFFT only used for multiplication
    for (auto &p : A) p /= A.size();
}


vector<ll> square(vector<cd> &A) {
    int n = 1;
    int inital_size = A.size();
    int output_size = 2*inital_size - 1;
    while (n < output_size) n <<= 1;  // n is a power of 2
    A.resize(n, 0);

    FFT(A);  // Evaluate A at the nth roots of unity

    vector<cd> C(n, 0);
    for (int i = 0; i < n; i++)
        C[i] = A[i] * A[i];  // C = A^2, we get C at the nth roots of unity
    IFFT(C);                 // convert back to coefficient form

    vector<ll> ans(output_size, 0);
    for (int i = 0; i < output_size; i++) ans[i] = round(C[i].real());

    return ans;
}


int main(){
    int n;
    cin >> n;
    vector<cd>f(n, 0);
    for (ll i=1; i<n; i++){
        f[(i*i)%n] += 1;
    }
    vector<ll> ff = square(f);
    
    for (ll i=n; i < (ll) ff.size(); i++){
        ff[i%n] += ff[i];
    }
    // now we only consider 1 to n-1
    for (ll i=1; i<n; i++){
        ff[(2*i*i) % n]++; // add extra A + A = C
    }

    ll ans = 0;
    for (ll i=1; i<n; i++){
        ans += ff[(i*i) % n]; // A + B = I mod n
    }
    ans /= 2;
    cout << ans <<endl;


    return 0;
}