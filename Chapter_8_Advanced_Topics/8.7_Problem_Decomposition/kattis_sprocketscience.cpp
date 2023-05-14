/**Kattis - sprocketscience
 * Math + Iterative Complete Search. Relatively alright question. We just test all ways to partition
 * the 12 gear ratios into 2 parts of 6 each. Each part corresponds to each of the front gears. We
 * then scale all the gear ratios in each part to have the same numerator, then sort the
 * denominators. Assuming our partition will lead to a valid solution, the ratio den1[i]/den2[i]
 * will be constant for all i. We check this property and scale all the gears such that den1[0] =
 * den2[0] (look at the LCM and scale). We then check if all numbers are within the right range and
 * report a valid solution if so.
 * 
 * Time: O(2^12), Space: O(1)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);
#define LSOne(S) (S & (-S))
int num[12];
int den[12];
vector<int> num1, num2, den1, den2;
int main()
{
    fast_cin();
    for (int i = 0; i < 12; i++) {
        char c;
        cin >> num[i] >> c >> den[i];
        int g = __gcd(num[i], den[i]);
        num[i] /= g;
        den[i] /= g;
    }

    for (int bm = 0; bm < (1 << 12); bm++) {
        if (__builtin_popcount(bm) != 6) continue;
        num1.resize(6);
        num2.resize(6);
        den1.resize(6);
        den2.resize(6);

        int idx1 = 0, idx2 = 0;
        int lcmn1 = 1, lcmn2 = 1;
        for (int i = 0; i < 12; i++) {
            if (bm & (1 << i)) {
                num1[idx1] = num[i];
                den1[idx1] = den[i];
                lcmn1 = lcm(lcmn1, num[i]);
                idx1++;
            }
            else {
                num2[idx2] = num[i];
                den2[idx2] = den[i];
                lcmn2 = lcm(lcmn2, num[i]);
                idx2++;
            }
        }
        for (int i = 0; i < 6; i++) {
            den1[i] *= lcmn1 / num1[i];
            num1[i] *= lcmn1 / num1[i];
            assert(num1[i] == lcmn1);

            den2[i] *= lcmn2 / num2[i];
            num2[i] *= lcmn2 / num2[i];
            assert(num2[i] == lcmn2);
        }
        sort(den1.begin(), den1.end());
        sort(den2.begin(), den2.end());

        int lcmfirst = lcm(den1[0], den2[0]);
        int topmultiplier = lcmfirst / den1[0];
        int botmultiplier = lcmfirst / den2[0];
        // scale all to this amount
        for (int i = 0; i < 6; i++) {
            num1[i] *= topmultiplier;
            den1[i] *= topmultiplier;

            num2[i] *= botmultiplier;
            den2[i] *= botmultiplier;
        }

        // check if all are valid
        if (num1[0] > 10000 || num2[0] > 10000) continue;
        bool isvalid = true;
        for (int i = 0; i < 6; i++) {
            if (num1[i] > 10000 || num2[i] > 10000) {
                isvalid = false;
                break;
            }
        }
        if (!isvalid) continue;

        // check if all are equal
        bool allequal = true;
        for (int i = 0; i < 6; i++) {
            if (den1[i] != den2[i]) {
                allequal = false;
                break;
            }
        }
        if (allequal) {
            cout << num1[0] << " " << num2[0] << endl;
            for (int i = 0; i < 6; i++) {
                cout << den1[i] << " ";
            }
            cout << endl;
            return 0;
        }
    }
    cout << "impossible" << endl;

    return 0;
}