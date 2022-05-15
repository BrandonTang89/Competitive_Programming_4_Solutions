/**Kattis - seti
 * Gaussian elimination within a finite field of the residue classes modulo a prime p. We just adjust the equations
 * to have constants in the field and replace division with doubles with modulo multiplicative inverse.
 * 
 * Time: O(n^3), Space: O(n^2)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int mod(int a, int n) { return (a % n + n) % n; }
int extEuclid(int a, int b, int &x, int &y) {  // pass x and y by ref
    ll xx = y = 0;
    ll yy = x = 1;
    while (b) {  // repeats until b == 0
        ll q = a / b;
        tie(a, b) = tuple(b, a % b);
        tie(x, xx) = tuple(xx, x - q * xx);
        tie(y, yy) = tuple(yy, y - q * yy);
    }
    return a;  // returns gcd(a, b)
}
int modInverse(int a, int n) {  // returns modular inverse of a mod n
    int x, y;
    extEuclid(a, n, x, y);
    return mod(x, n);
}

const int MAX_N = 80;  // adjust as needed
struct AugmentedMatrix {
    int mat[MAX_N][MAX_N + 1];
};
struct ColumnVector {
    int vec[MAX_N];
};

ColumnVector GaussianElimination(int N, AugmentedMatrix Aug, int p) {
    // input: N, Augmented Matrix Aug, output: Column vector X, the answer
    for (int i = 0; i < N - 1; ++i) {  // forward elimination
        int l = i;
        for (int j = i + 1; j < N; ++j)                            // row with max col value
            if (fabs(Aug.mat[j][i]) > fabs(Aug.mat[l][i])) l = j;  // remember this row l
        // swap this pivot row, reason: minimize floating point error
        for (int k = i; k <= N; ++k) swap(Aug.mat[i][k], Aug.mat[l][k]);
        for (int j = i + 1; j < N; ++j)  // actual fwd elimination
            for (int k = N; k >= i; --k){
                Aug.mat[j][k] -= mod(mod(Aug.mat[i][k] * Aug.mat[j][i], p) * modInverse(Aug.mat[i][i], p), p);
                Aug.mat[j][k] = mod(Aug.mat[j][k], p);
            }
    }

    ColumnVector Ans;                   // back substitution phase
    for (int j = N - 1; j >= 0; --j) {  // start from back
        int t = 0;
        for (int k = j + 1; k < N; ++k){
            t += mod(Aug.mat[j][k] * Ans.vec[k], p);
            t = mod(t, p);
        }
        Ans.vec[j] = (Aug.mat[j][N] - t) * modInverse(Aug.mat[j][j], p);  // the answer is here
        Ans.vec[j] = mod(Ans.vec[j], p);
    }
    return Ans;
}

int main(){
    int num_tc;
    cin >> num_tc;
    while (num_tc--){
        int p, n;
        string s;
        cin >> p >> s;
        n = s.size();
        vector<int> f(n+1, 0);
        for (int i=0; i<n; i++){
            if (s[i] == '*') f[i] = 0;
            else f[i] = (s[i] - 'a') + 1;
        }

        AugmentedMatrix Aug;
        for (int i=0; i<n; i++){
            Aug.mat[i][0] = 1;
            for (int j=1; j<n; j++){
                Aug.mat[i][j] = Aug.mat[i][j-1] * (i+1);
                Aug.mat[i][j] = mod(Aug.mat[i][j], p);
            }
            Aug.mat[i][n] = f[i];
        }

        ColumnVector Ans = GaussianElimination(n, Aug, p);

        for (int i=0; i<n; i++){
            cout << Ans.vec[i] << " ";
        }
        cout << endl;
    }


    return 0;
}