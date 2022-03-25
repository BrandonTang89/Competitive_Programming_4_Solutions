/**Shopee Code League 2021 Question 2
 * We are asked to count the number of continous subarrays with average >= k. We can minus k from each element
 * to reduce the problem to number of continous subarrays with sum >= 0. We can then compute the static sum from
 * 0 to i to get a new array Sum where Sum[i] = Sum[i-1] + A[i]. We then try to find the number of (i, j) such that
 * i < j and Sum[j] - Sum[i] >= 0 --> Sum[j] >= Sum[i]. 
 * 
 * We can count the number of Sum[j] > Sum[i] by sorting Sum in descending order and counting the inversion index.
 * We can count the number of Sum[j] == Sum[i] using a linear pass with a hash table. 
 * 
 * Time: O(n log n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);


// Merge_sort with inversion index
long long merge_sort(int arr[100009], int l, int r) {
    if (l + 1 == r) {
        if (arr[l] > arr[r]) {
            swap(arr[l], arr[r]);
            return 1;
        }
        return 0;
    }
    if (l == r) {
        return 0;
    }

    int temp[100009];
    int middle = (l + r) / 2;

    long long inversion_index = 0;
    inversion_index += merge_sort(arr, l, middle);
    inversion_index += merge_sort(arr, middle + 1, r);

    int l_i = l, r_i = middle + 1;  // left and right indicators
    for (int i = l; i <= r; i++) {  // index for the temp array

        if (l_i <= middle && r_i <= r) {
            if (arr[l_i] <= arr[r_i]) {
                temp[i] = arr[l_i];
                l_i++;
            } else {
                temp[i] = arr[r_i];
                r_i++;
                inversion_index +=
                    (middle - l_i + 1);  // have to bubble swap over all the left elements
            }
        } else if (r_i > r) {  // right empty
            temp[i] = arr[l_i];
            l_i++;
        } else {  // left empty
            temp[i] = arr[r_i];
            r_i++;
        }
    }
    for (int i = l; i <= r; i++) {  // copy temp to arr
        arr[i] = temp[i];
    }

    return inversion_index;
}

int n, k;
int ori, arr[100009];
int main() {
    cin >> n >> k;
    cin >> arr[0];
    arr[0] -= k;
    for (int i = 1; i < n; i++) {
        cin >> ori;
        ori -= k;
        arr[i] = ori + arr[i-1];
    }

    map <int, int> mp;
    ll ans = 0;
    for (int i=0; i<n; i++){
        ans += mp[arr[i]];
        mp[arr[i]]++;
        arr[i] *= -1;
        // cout << arr[i] << endl;
    }

    cout << merge_sort(arr, 0, n-1) + ans << endl;

    return 0;
}