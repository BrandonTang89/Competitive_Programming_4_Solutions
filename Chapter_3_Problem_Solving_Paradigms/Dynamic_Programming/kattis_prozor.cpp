/* Kattis - prozor

Basic 2D Static Sum with a fixed sub rectangle size. Also some pretty easy and nice looking output formatting.

Time: O(n^2), Mem: O(n^2)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef long double ld;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int max_r, max_c, k; // row, height, net length
bool got_fly;
char pt;
vector<vector<int>> arr; //arr[i][j] contains the nunber of flies from (0,0) to (i,j) inclusive

vector<vector<char>> ans_grid;

int rsq(int r1, int c1, int r2, int c2){ // top left, bottom right
    if (r1 < 0 || c1 < 0 || r2 >= max_r-1 || c2 >= max_c-1)return 0; // boundary condition check

    if (r1 == 0 && c1 == 0) return arr[r2][c2];
    if (r1 == 0) return arr[r2][c2] - arr[r2][c1-1];
    if (c1 == 0) return arr[r2][c2] - arr[r1-1][c2];
    
    return(arr[r2][c2] - arr[r2][c1-1] - arr[r1-1][c2] + arr[r1-1][c1-1]);
}
int main(){
    cin >> max_r >> max_c >> k;

    for (int r=0;r<max_r;r++){
        vector<int> j;
        arr.push_back(j);

        vector<char> i;
        ans_grid.push_back(i);
        for (int c=0;c<max_c;c++){
            cin >> pt;
            ans_grid[r].push_back(pt);
            if (pt == '.')got_fly = false;
            else{
                got_fly = true;
            }
            arr[r].push_back(got_fly);
            
            // 2D Static Prefix Sum Preprocesing
            if (r == 0 && c == 0)continue;
            if (r == 0){
                arr[r][c] += arr[r][c-1];
            }
            else if (c == 0){
                arr[r][c] += arr[r-1][c];
            }
            else{
                arr[r][c] += (arr[r-1][c] + arr[r][c-1] - arr[r-1][c-1]);
            }
        }
    }

    int ans = 0, cur;
    int mc=0, mr = 0;
    
    for (int r=1; r<max_r;r++){
        for(int c=1; c<max_c; c++){
            cur = rsq(r, c, r+k-3, c+k-3);
            if (ans < cur){
                ans = cur;
                mc = c;
                mr = r;
            }
        }
    }
    //printf("mc: %d, mr: %d\n", mc, mr);
    cout << ans << endl;


    // output formatting
    int tlc = mc-1;
    int tlr = mr-1;
    int brc = mc+k-2;
    int brr = mr+k-2;

    ans_grid[tlr][tlc] = '+';
    ans_grid[tlr][brc] = '+';
    ans_grid[brr][tlc] = '+';
    ans_grid[brr][brc] = '+';

    for (int c=tlc+1;c<brc;c++){
        ans_grid[tlr][c] = ans_grid[brr][c] = '-';
    }
    for (int r=tlr+1;r<brr;r++){
        ans_grid[r][tlc] = ans_grid[r][brc] = '|';
    }

    for (int r=0;r<max_r;r++){
        for (int c=0;c<max_c;c++){
            cout << ans_grid[r][c];
        }
        cout << endl;
    }

   return 0;
}