/* Kattis - pagelayout

Observation 1:
    There are many opportunities for pruning. Not a rigourous proof but heres an example:
    If ad[i] and ad[j] cannot coexist, we can prune off (2^(n-2)) options right away, making the
    generative solution much better than the bitmask filter. This is especially important given how there
    are up to 500 test cases per input. Meaning that expected time complexity is important rather than just upperbound
    time complexity.

Debugging:  
    When doing recursive functions, it might be important to declare variables within the function scope so that they
    do not get overwritten by other function calls during the recursion..

Time: O(2^N * N), Mem: O(N)

*/
#include <bits/stdc++.h>
using namespace std;

int n;
int w, h, x, y;
tuple<int,int,int,int> ads[20];

int state[20]; // 0 for nothing yet, -1 for dont include, 1 for include
bool finished, valid;

bool isintersecting(int w1, int h1, int x1, int y1, int w2, int h2, int x2, int y2){
    if (x1 > x2){ // ad 1 on the left of add 2
        swap(x1,x2);
        swap(y1,y2);
        swap(w1,w2);
        swap(h1,h2);
    }

    if (x1 + w1 - 1 < x2)return false; // right edge of ad1 left of left edge of ad 2
    if (y1 + h1 - 1 < y2)return false; // bottom edge of ad1 above top edge of ad 2
    if (y2 + h2 - 1 < y1)return false; // bottom edge of ad2 above top edge of ad 1

    return true;
}
int backtrack(int state[20], int space_covered){
    //for (int i=0;i<n;i++){cout << state[i] << " ";}cout << endl;
    //cout << "space: " << space_covered << endl;
    finished = true;
    int next_ad;
    for (int i=0;i<n;i++){
        if (state[i] == 0){
            finished = false;
            next_ad = i;
            break;
        }
    }

    if(finished){
        return space_covered;
    }

    // attempt to include the next add (note that only the ads from 0 to next_ad-1 inclusive have been added)
    valid = true; 
    const auto[w1, h1, x1, y1] = ads[next_ad];
    for (int i=0;i<next_ad; i++){
        if (state[i] == 1){
            const auto[w2, h2, x2, y2] = ads[i]; //c++ 17 structured bindings
            if (isintersecting(w1, h1, x1, y1, w2, h2, x2, y2)){
                valid = false;
                break;
            }
        }
    }

    int max_space_covered = 0;

    if (valid){ // try to put the ad there and continue the backtrack
        state[next_ad] = 1;
        max_space_covered = backtrack(state, space_covered + w1*h1);
    }

    
    state[next_ad] = -1;
    //cout << "|: "; for (int i=0;i<n;i++){cout << state[i] << " ";}cout << endl;
    max_space_covered = max(max_space_covered, backtrack(state, space_covered));
    
    state[next_ad] = 0;

    return max_space_covered;
}


int main(){
    while (true){
        scanf("%d", &n);
        
        if (n == 0)break;
        for (int i=0;i<n;i++){
            scanf("%d %d %d %d",&w, &h, &x, &y);
            ads[i] = make_tuple(w,h,x,y);
        }
        //cout << n << endl;
        for(int i=0;i<n;i++)state[i] = 0;
        printf("%d\n", backtrack(state, 0));
    }
    return 0;
}