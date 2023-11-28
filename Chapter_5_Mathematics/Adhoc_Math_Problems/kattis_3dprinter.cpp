/**Kattis - 3dprinter
 * You are looking at an antique, possibly one of the first Kattis questions I ever did, at time
 * 2018-01-17 18:36:05
 * 
 * Time: O(n), Mem: O(1)
 */
#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int printer = 1;
    int days = 0;
    for (int i = 1; printer < n; i++) {
        printer *= 2;
        days = i;
    }
    cout << days + 1 << endl;
    return 0;
}