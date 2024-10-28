#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

template <typename T=ll>
struct StaticSum {
    const int n;
    vector<T> pfs;  // arr[i] contains the range sum from 0 to i inclusively

    T rsq(int l, int r) const {            // range sum from l to r inclusively
        if (l < 0 || r >= n) assert(false);  // boundary condition check
        if (l == 0) return pfs[r];
        return (pfs[r] - pfs[l - 1]);
    }

    StaticSum(const vector<T>& arr) : n(arr.size()), pfs(arr) {
        for (int i = 1; i < n; i++) {
            pfs[i] += pfs[i - 1];
        }
    }
};

StaticSum<>* ss_brr_ptr;
vector<ll> brr;
vector<ll> segmentSums;              // segmentSums[i] = sum of all a[j][k] within the segment i
int n;


pair<ll, ll> getComponents(ll idx){
    ll firstComponent = lower_bound(ss_brr_ptr->pfs.begin(), ss_brr_ptr->pfs.end(), idx) - ss_brr_ptr->pfs.begin();
    ll secondComponent = (firstComponent == 0 ? idx : idx - ss_brr_ptr->pfs[firstComponent-1]) - 1;
    return {firstComponent, secondComponent};
}

ll topOfSegment(ll segmentIdx, ll includedRows, StaticSum<>& ss_ss_arr, StaticSum<>& ss_arr){ // gets the first sum of the first includedRows of the segment Idx
    ll ans = ss_ss_arr.rsq(0, segmentIdx+includedRows-1);
    if (segmentIdx > 0){
        ans -= ss_ss_arr.rsq(0, segmentIdx-1);
        ans -= (ss_arr.rsq(0, segmentIdx-1)) * (includedRows);
    }
    return ans;
}


ll getUntil(ll idx, StaticSum<>& ss_ss_arr, StaticSum<>& ss_arr, StaticSum<>& ss_segmentSums){ // inclusive of this current one...
    pair<ll, ll> components = getComponents(idx);
    // cerr << "components: " << components.first << " " << components.second << endl;
    ll ans = 0;
    if (components.first == 0){
        ans = topOfSegment(components.first, components.second+1, ss_ss_arr, ss_arr);
    }
    else{
        ans = ss_segmentSums.rsq(0, components.first-1) + topOfSegment(components.first, components.second+1, ss_ss_arr, ss_arr);
        // cerr << "top part " << topOfSegment(components.first, components.second+1, ss_ss_arr, ss_arr) << endl;
    }
    return ans;
    
}
int main(){
    cin >> n;
    vector<ll> arr(n);
    for (int i=0; i<n; i++){
        cin >> arr[i];
    }

    StaticSum<> ss_arr(arr);
    StaticSum<> ss_ss_arr(ss_arr.pfs);

    segmentSums.assign(n, 0);
    segmentSums[0] = ss_ss_arr.rsq(0, n-1); // sum of prefixes
    for (int i=1; i<n; i++){
        segmentSums[i] = segmentSums[i-1] - (n-i+1) * arr[i-1];
    }
    // cerr << "segmentSums: ";
    // for (int i=0; i<n; i++){
    //     cerr << segmentSums[i] << " ";
    // }
    // cerr << endl;
    StaticSum<> ss_segmentSums(segmentSums);

    assert(segmentSums[n-1] == arr[n-1]);

    brr.assign(n, 0);
    for (int i=0; i<n; i++){
        brr[i] = n-i;
    }
    ss_brr_ptr = new StaticSum<>(brr);


    int q;
    cin >> q;
    while (q--){
        ll top, bottom;
        cin >> top >> bottom;

        if (top == 1){
            cout << getUntil(bottom, ss_ss_arr, ss_arr, ss_segmentSums) << endl;
        }
        else{
            cout << getUntil(bottom, ss_ss_arr, ss_arr, ss_segmentSums) - getUntil(top-1, ss_ss_arr, ss_arr, ss_segmentSums) << endl;
        }
    }




    return 0;
}