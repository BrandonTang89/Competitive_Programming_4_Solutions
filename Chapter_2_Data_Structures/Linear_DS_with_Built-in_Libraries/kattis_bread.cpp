/* Kattis - Bread
Abridged Problem Statement: Given an initial and a final permutation of {1..N}, can we convert the initial into the final with just the operation (abc->cab)

Observation 1:
    to simplify, we can relabel both permutations such that the final permutation is merely 1,2,..,N in ascending order
    this is done with the map below

Observation 2:
    As any 2 bubble sort swaps can be accomplished by some sequence of (abc -> cab) moves (proof is left as an exercise to the reader)
    It is possible to sort with the given conditions if inversion_index %2 == 0

    An odd number inversion index obviously indicates that any sequence (abc -> cab) will be nable to sort the relabeled initial permutation as 
    (abc -> cab) is equivalent to 2 adjacent bubble sort swaps

    with these 2 combined, the sort is possible if and only if inversion index is even
    
Solution:
    Modifed merge sort to count inversion index

    Time: O(n log n) Mem: O(n)

*/ 

#include <bits/stdc++.h>
using namespace std;

map<int, int> m;
int n;
int initial[100009], target[100009];

long long merge_sort(int arr[100009], int l, int r){
    
    if (l+1 == r){
        if (arr[l] > arr[r]){
            swap(arr[l], arr[r]);
            return 1;
        }
        return 0;
    }
    if (l == r){
        return 0;
    }

    int middle = (l+r)/2;
    
    long long inversion_index = 0;
    inversion_index += merge_sort(arr, l, middle);
    inversion_index += merge_sort(arr, middle+1, r);

    // printf("L: %d, R: %d, Middle:%d\n", l, r, middle); 
    //for (int i=0;i<n;i++){cout << arr[i] << " ";}
    //cout << endl;

    int temp[100009];
    int l_i=l, r_i=middle+1;
    for (int i=l; i<=r;i++){
        if (l_i <= middle && r_i <= r){
            if (arr[l_i] <= arr[r_i]){
                temp[i] = arr[l_i];
                l_i++;
            }
            else{
                temp[i] = arr[r_i];
                r_i++;
                inversion_index += (middle-l_i+1);
            }
        }
        else if (r_i > r){ // right empty
            temp[i] = arr[l_i];
            l_i++;
        }
        else{ // left empty
            temp[i] = arr[r_i];
            r_i++;
        }
        
    }
    for (int i=l; i<=r; i++){
        arr[i] = temp[i];
    }

    return inversion_index;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for (int i=0;i<n;i++)cin >> initial[i];
    for (int i=0;i<n;i++){
        cin >> target[i];
        m[target[i]] = i+1;
        target[i] = i+1;
    }
    for (int i=0;i<n;i++){
        initial[i] = m[initial[i]];
    }

    long long inversion_index = merge_sort(initial, 0, n-1);

    /*
    for (int i=0;i<n;i++){cout << initial[i] << " ";}
    cout << endl;
    cout << inversion_index << endl;*/
    
    if (inversion_index % 2 == 0){
        cout << "possible\n";
    }
    else cout << "impossible\n";

    return 0;
}
