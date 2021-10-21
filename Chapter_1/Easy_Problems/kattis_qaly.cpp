/* kattis - qaly
Introduction to double and for loops.

Time: O(n), Mem: O(1)
*/
#include <bits/stdc++.h>
using namespace std;

int n;
long double a, b, ans;
int main(){
  cin >> n;
  ans = 0;
  for(int i=0;i<n;i++){
    cin >> a >> b;
    ans += a*b;
  }
  cout << ans << endl;
  return 0;
}
