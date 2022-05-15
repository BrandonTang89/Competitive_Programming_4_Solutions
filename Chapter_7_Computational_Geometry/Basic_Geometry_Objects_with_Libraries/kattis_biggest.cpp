/**Kattis - biggest
 * Simulate the process of cutting. Use an array that loops back around. Ensure the first cut
 * is at 0 to prevent a slice occuring from the back to the front. Ensure sufficient precision
 * in output. Also Python 3 was too slow for me. So I used C++.
 * 
 * Time: O(min(n, 360*60*60)), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long double ld;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

bool arr[60*60*360];
int num_tc, r, n, a, b, c;
int cur_max, global_max;
int main(){
    cout.precision(std::numeric_limits<double>::digits10);
    cin >> num_tc;
    for (int tc=0; tc<num_tc; tc++){
        memset(arr, 0, sizeof(arr));
        cin >>r >> n >> a >> b >> c;
        int theta = 3600*a + 60*b + c;
        int pos = 0;
        for (int i=0; i<n; i++){
            if (arr[pos])
                break;
            arr[pos] = 1;
            pos += theta;
            if (pos >= 60*60*360)
                pos -= 60*60*360;
        }

        cur_max = 1;
        global_max = 0;
        for (int i=0; i<60*60*360; i++){
            if (!arr[i]){
                cur_max += 1;
            }
            else{
                global_max = max(global_max, cur_max);
                cur_max = 1;
            }
            
        }
        global_max = max(global_max, cur_max);
        cout << (ld) global_max / (ld) (60*60*360) * M_PI*r*r << endl;
    }
    return 0;
}