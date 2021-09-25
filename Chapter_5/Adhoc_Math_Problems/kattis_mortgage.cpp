/* Kattis - Mortage
Don't be scared of the "relatively" high difficulty rating of the question, its actually not too bad.

Observation 1:
    Obviously this question about interest and payments has been covered in standard high school math.
    As such, we can work out the formula instead of simulating which would take forever.

Design 1:
    Due to potentially large values of n, we should use fast exponentiation

Design 2:
    Due to high I/O, unsync cin/cout with stdio

Debugging:
    Special case when r=0.00, in such a case, the formula doesn't work, so we just make a special if case for it

Time: O(T * log N)

*/ 
#include <bits/stdc++.h>
using namespace std;

long double fexp(long double b, long long p){
    if (p == 0)return 1;
    if (p == 1)return b;

    if (p & 1){
        return fexp(b, p>>1)*fexp(b, p>>1)*b;
    }
    else{
        return fexp(b, p>>1)*fexp(b, p>>1);
    }
}

// Calculates the amount owned from pricipal of X, with monthly payment of Y, for N years with interest r% per annum
long double amount_owned(long long X, long long Y, long long N, long double r){
    N *= 12; // convert N to number of months
    r /= 1200; // convert r to per month out of 1 instead of percent
    r += 1; // so that every month, just times r
    long double r_pow_n = fexp(r, N);
    long double ans = X * r_pow_n - Y * (r_pow_n - 1)/(r-1);

    //printf("r_pow_n: %Le\n",r_pow_n);
    //printf("amt owned for %lld, %lld, %lld, %Le : %Le\n", X,Y,N,r,ans);
    return (ans);
}

int main(){
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long X, Y, N;
    long double r;

    while (true){
        cin >> X >> Y >> N >> r;
        if (X == 0 && Y ==0)break;

        if (r == (long double) 0.00){
            if (X - Y*N*12 < 0)
                cout << "YES\n";
            else cout << "NO\n";
            continue;
        }
        if (amount_owned(X,Y,N,r) <= (long double) 0){
            cout << "YES" << endl;
        }
        else{
            cout << "NO" << endl;
        } 
    }

    return 0;
}