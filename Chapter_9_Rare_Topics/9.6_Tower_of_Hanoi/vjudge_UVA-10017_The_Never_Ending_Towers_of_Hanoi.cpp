/**vjudge - UVA-10017 - the never ending towers of hanoi
 * Recursion + output formatting. Just use the basic recursive algorithm and print at 
 * every stage until we print enough things.
 * 
 * Time: O(m), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int m;
vector<int> A, B, C;
void print_state(){
    cout << "A=>";
    if ((int) A.size() != 0){
        cout << "   " << A[0];
    }
    for (int i=1; i< (int)A.size();i++){
        cout << " " << A[i];
    }
    cout << endl;
    cout << "B=>";
    if ((int) B.size() != 0){
        cout << "   " << B[0];
    }
    for (int i=1; i< (int)B.size();i++){
        cout << " " << B[i];
    }
    cout << endl;
    cout << "C=>";
    if ((int) C.size() != 0){
        cout << "   " << C[0];
    }
    for (int i=1; i< (int)C.size();i++){
        cout << " " << C[i];
    }
    cout << endl;
    cout << endl;
}
void solve(int count, vector<int> &source, vector<int> &dest, vector<int> &intermediate){
    if (m == 0)return;
    if (count == 1){
        dest.push_back(source.back());
        source.pop_back();

        m--;
        print_state();
        return;
    }
    else{
        solve(count-1, source, intermediate, dest);
        solve(1, source, dest, intermediate);
        solve(count-1, intermediate, dest, source);
    }
}
int main(){
    for (int problem=1; ; problem++){
        int n;
        cin >> n >> m;
        if (n == 0 && m == 0)break;
        A.clear();
        B.clear();
        C.clear();

        for (int i=n; i>0;i--){
            A.push_back(i);
        }
        cout << "Problem #" << problem << endl << endl;
        print_state();
        solve(n, A, C, B);
    }


    return 0;
}