/**Kattis - officespace
 * Since the constraints aren't very tight, we can use a 2D array to simulate the process.
 * If not... we could have probably used a sort of 2D segment tree or something.
 * 
 * Time: O(nwh), Space: O(wh)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int w, h, n;
int x1, yi, x2, y2;
vector<vector<int>> office;
map<int, string> employees;

int count(int thing_to_count){
    int ans = 0;
    for (int i=0; i<h; i++){
        for (int j=0; j<w; j++){
            if (office[i][j] == thing_to_count) ans++;
        }
    }
    return ans;
}
int main(){
    while (cin >> w >> h >> n){
        office.assign(h, vector<int>(w, 0));
        employees.clear();

        for (int e=1; e<n+1; e++){
            string name;
            cin >> name >> x1 >> yi >> x2 >> y2;
            employees[e] = name;

            for (int j=yi; j<y2; j++){
                for (int i=x1; i<x2; i++){
                    office[j][i] = (office[j][i] == 0 ? e : -1);
                }
            }

        }
        printf("Total %d\n", w*h);
        printf("Unallocated %d\n", count(0));
        printf("Contested %d\n", count(-1));
        for (int e=1; e<n+1; e++){
            printf("%s %d\n", employees[e].c_str(), count(e));
        }
        printf("\n");
    }

    return 0;
}