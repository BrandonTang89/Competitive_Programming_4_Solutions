/* Kattis - Bungee Builder

This is rated as a relatively easy question but I found the derivation of the method rather difficult

Observation 1:
    if we process outward from the max height mountain, all mountains we process will be able to build a bridge in the opposite direction of procesing
    this avoids dealing with the nonsense of the start and ends where there are no mountains behind (relative in the processing direction)

Observation 2:
    For any mountain taller than another previously processed mountain, 
    we can attempt to join the taller mountain with the processed mountain
    the max jump height the bridge joining this mountain is arr[m] - s.top().first + s.top().second (try to reason this out on paper)

Observation 3:
    after processing a mountain, all previously processed mountains shorter than the current mountain do not need to be considered (as their effects)
    have been accounted into the second integer in the pair that is put into the stack

Time: O(n) Mem: O(n)
*/
#include <bits/stdc++.h>
using namespace std;

stack<pair<int,int>>s;
int arr[1000009];
int n, max_h, max_h_pos; 
int max_jump=0;

void process_mountain(int m){ // process the mountain at pos m
    //printf("m:%d\n", m);

    int max_j_at_m = 0;
    while (arr[m] >= s.top().first){
        max_j_at_m = max(arr[m] - s.top().first + s.top().second,max_j_at_m);
        //printf("Popping: %d %d\n", s.top().first, s.top().second);
        s.pop();

        if (s.empty())break;

    }
    s.push(make_pair(arr[m], max_j_at_m));
    //printf("Pushing: %d %d\n", arr[m], max_j_at_m);

    max_jump = max(max_jump, max_j_at_m);
}
int main(){
    cin >> n;
    cin >> arr[0];
    max_h = arr[0];
    max_h_pos = 0;

    for (int i=1;i<n;i++){
        cin >> arr[i];
        if (arr[i] > max_h){
            max_h_pos = i;
            max_h = arr[i];
        }
    }    

    //printf("max height pos: %d, max height: %d\n", max_h_pos, max_h);
    // Go from max height mountain towards the left
    s.push(make_pair(max_h, 0));
    for (int i=max_h_pos-1; i>=0; i--){
        
        process_mountain(i);
    }
    while (!s.empty())s.pop();
    s.push(make_pair(max_h, 0));
    for (int i=max_h_pos+1; i<n; i++){
        process_mountain(i);
    }

    cout << max_jump<< endl;

}