/* Kattis - Deathstar

Observation 1:
    a valid way to generate each number is to do perform a bitwise OR on all numbers in the matrix that it is involved in.

    Proof:
        ai&aj will be at least a[i][j] as ai and aj are both constructed to include all bits in a[i][j]
        What we need to prove is thus that ai&aj will not produce a number larger than a[i][j]

        assume that ai&aj > a[i][j], it would mean there there is a bit at some position t such that bit t is on in both ai and aj but not in a[i][j]
        this means that for some other a[i][k], bit t is on, indicating that ai definitely has bit t on. the same logic can be applied 
        to show that aj definitely has bit t on. Thus it is not possible for a[i][j] to not have bit t on, indicating that this case is impossible

Time: O(n^2), Mem: O(n^2)
*/
#include <bits/stdc++.h>
using namespace std;

int n;
int arr[1001][1001];
int main(){
    cin >> n;
    
    for (int r=0;r<n;r++){
        for (int c=0;c<n;c++){
            cin >> arr[r][c];
        }
    }

    for (int k=0; k<n;k++){
        int a=0; 
        // Along the kth column
        for(int r=0;r<k;r++){
            a = a|arr[r][k];
        }
        // Along the kth row
        for (int c=k+1;c<n;c++){
            a = a|arr[k][c];
        }
        if (k != n-1)
            cout << a << " ";
        else 
            cout << a  << endl;

    }


    return 0;
}