/* Kattis - flowergarden
A combination problem that involves counting total length of the path and binary searching
the prime list to find the largest prime <= the maximum number of flowers he reach.

Be careful of double comparision errors. And also edge cases like when he can reach all or none of
the flowers.

Time: O(n log log n), Space: O(n)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

#define EPS 1e-9
typedef long long ll;
typedef vector<ll> vll;

ll _sieve_size;
bitset<10000010> bs;
vll primes = {0}; // since we can choose 0 as well...

// Able to handle 1e7 in < 1s
void sieve(ll upperbound){
    _sieve_size = upperbound + 1;
    bs.set();
    bs[0] = bs[1] = 0;
    for(ll i = 2; i <= _sieve_size; i++){
        if(bs[i]){
            for(ll j = i * i; j <= _sieve_size; j += i){
                bs[j] = 0;
            }
            primes.push_back(i);
        }
    }
}

vector<pair<int, int>> flowers;
double euclidian_distance(int flower_a, int flower_b){
    int x1 = flowers[flower_a].first;
    int y1 = flowers[flower_a].second;
    int x2 = flowers[flower_b].first;
    int y2 = flowers[flower_b].second;
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
double max_dist;
int num_tc, n, x, y;

int main(){
    sieve(200009);
    cin >> num_tc;

    for (int tc=0; tc<num_tc; tc++){
        cin >> n >> max_dist;
        flowers.clear();
        flowers.emplace_back(0, 0);
        for (int i=0; i<n; i++){
            cin >> x >> y;
            flowers.push_back(make_pair(x, y));
        }
        
        double total_dist = 0;
        int max_watered = 0;
        bool done = false;
        for (int i=1; i<n+1; i++){
            total_dist += euclidian_distance(i-1, i);
            //cout << "total Dist:  " << total_dist << " max_Dist: " << max_dist << endl;
            if (total_dist - max_dist > EPS){ // greater than max_dist
                // cout << "i : " << i << endl;
                done = true;
                max_watered = i-1;
                break;
            }
        }
        if (!done){
            max_watered = n;
        }

        if (max_watered == 0){
            cout << 0 << endl;
            continue;
        }
        int pos = upper_bound(primes.begin(), primes.end(), max_watered) - primes.begin() - 1;
        cout << primes[pos] << endl;

    }

    return 0;
}