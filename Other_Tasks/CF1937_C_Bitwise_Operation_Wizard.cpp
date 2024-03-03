#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);


int main(){
    int tc;
    cin >> tc;
    while (tc--){
        int n;
        cin >> n;
        int maxIdx = 0;
        for (int i=1; i<n; i++){
            cout << "? " << maxIdx << " " << maxIdx << " " << i << " " << i << endl;
            cout.flush();

            char c;
            cin >> c;
            assert(c != '=');
            if (c == '<'){
                maxIdx = i;
            }
        }

        // maxIdx is the index of the maximum element

        vector<int> candidates = {0};
        int bestCandidate = 0;
        for (int i=1; i<n; i++){
            if (i == maxIdx) continue;
            cout << "? " << maxIdx << " " << bestCandidate << " " << maxIdx << " " << i << endl;
            cout.flush();

            char c;
            cin >> c;
            if (c == '='){
                candidates.push_back(i);
            }
            else if (c == '<'){
                bestCandidate = i;
                candidates.clear();
                candidates.push_back(i);
            }
        }

        // candidates contain indices such that a[candidate[i]] | a[maxIdx] = MAXIMUM

        // we find the minimum of the candidates
        int minCandidate = candidates[0];
        for (int i=1; i< (int) candidates.size(); i++){
            cout << "? " << minCandidate << " " << minCandidate << " " << candidates[i] << " " << candidates[i] << endl;
            cout.flush();

            char c;
            cin >> c;
            if (c == '>'){
                minCandidate = candidates[i];
            }
        }

        cout << "! " << minCandidate << " " << maxIdx << endl;
        cout.flush();
    }

    return 0;
}