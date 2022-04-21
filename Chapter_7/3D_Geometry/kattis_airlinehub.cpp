/**Kattis - airlinehub
 * Maybe difficult without the great circle distance libary code. But since we have that, it's
 * pretty easy. Just remember that we should get the last optimal airport.
 * 
 * Time: O(n^2), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

double gcDist(double pLa, double pLo, double qLa, double qLo, double r) {
    pLa *= M_PI / 180;
    pLo *= M_PI / 180;  // degree to radian
    qLa *= M_PI / 180;
    qLo *= M_PI / 180;
    return r * acos(cos(pLa) * cos(pLo) * cos(qLa) * cos(qLo) +
                    cos(pLa) * sin(pLo) * cos(qLa) * sin(qLo) + sin(pLa) * sin(qLa));
}

int n;
int main(){
    cout << fixed << setprecision(2);
    while (cin >> n){
        vector<pair<double, double>> ports;
        for (int i=0; i<n; i++){
            double la, lo;
            cin >> la >> lo;
            ports.emplace_back(la, lo);
        }

        int best_port = -1;
        double smallest_max_dist = 1e9;
        for (int i=0; i<n; i++){
            double cur_max_distance = 0;
            for (int j=0; j<n; j++){
                if (i == j) continue;
                double dist = gcDist(ports[i].first, ports[i].second, ports[j].first, ports[j].second, 100);
                cur_max_distance = max(cur_max_distance, dist);
            }
            
            // cout << cur_max_distance << endl;
            if (cur_max_distance < smallest_max_dist || fabs(cur_max_distance - smallest_max_dist) < 1e-9){
                smallest_max_dist = cur_max_distance;
                best_port = i;
            }
        }
        auto &[la, lo] = ports[best_port];
        cout << la << " " << lo << endl;
    }


    return 0;
}