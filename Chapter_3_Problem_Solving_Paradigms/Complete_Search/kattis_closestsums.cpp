/* Kattis - Closestsums

Another relatively easy complete search question. Just at least try to optimise abit, like sorting the sums array
and using binary search for each query.

Time per test case: O(n^2 log n + q log n), n^2 log n from the sort of the sums arr
Mem: O(n^2)
*/ 
#include <bits/stdc++.h>
using namespace std;

int n, m;
int arr[1000];
int sums[1000009];
int main(){
    int case_no = 1;
    while (scanf("%d",&n) != EOF){
        printf("Case %d:\n", case_no);
        case_no++;

        for (int i=0;i<n;i++){
            scanf("%d", &arr[i]);
        }
        int counter =0;
        for (int i=0;i<n;i++){
            for (int j=0;j<n;j++){
                if (i == j) continue;
                sums[counter] = arr[i] + arr[j];
                counter++;
            }
        }

        sort(sums,sums+counter);

        int k;
        int min_diff_index = 0;
        scanf("%d", &m);
        for (int q=0;q<m;q++){
            scanf("%d", &k);
            
            min_diff_index = lower_bound(sums, sums+counter, k) - sums;
            if (min_diff_index > 0){
                if (abs(sums[min_diff_index] - k) > abs(sums[min_diff_index-1] -k)){
                    min_diff_index--;
                }
            }
            if (min_diff_index == counter){
                min_diff_index--;
            }
            printf("Closest sum to %d is %d.\n", k, sums[min_diff_index]);
        }

    }
    
    

    return 0;
}