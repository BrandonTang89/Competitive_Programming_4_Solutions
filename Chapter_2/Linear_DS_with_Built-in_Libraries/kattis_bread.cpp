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

    int temp[100009];
    int middle = (l+r)/2;
    
    long long inversion_index = 0;
    inversion_index += merge_sort(arr, l, middle);
    inversion_index += merge_sort(arr, middle+1, r);


    // printf("L: %d, R: %d, Middle:%d\n", l, r, middle); 
    //for (int i=0;i<n;i++){cout << arr[i] << " ";}
    //cout << endl;

    int l_i=l, r_i=middle+1;
    for (int i=l; i<=r;i++){
        /*
        for (int j=0;j<n;j++){cout << temp[j] << " ";}
        cout << endl;*/
        
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
        else{
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
    cout << endl;*/ 

    //cout << inversion_index << endl;
    
    if (inversion_index % 2 == 0){
        cout << "possible\n";
    }
    else cout << "impossible\n";







}
