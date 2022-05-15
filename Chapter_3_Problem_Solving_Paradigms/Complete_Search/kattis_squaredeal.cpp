/* Kattis - Squaredeal

Observation 1:
    The only possible arrangements for the 3 rectangles to form a square are the 2 already given in the task
    I don't really have a rigourous proof for that but fiddling around with rectangles in ur mind 
    might lead you to belive this

    This means that we can just try these 2 arrangements. But we need to try to swap each rectangle around (3!)
    and rotate each rectangle 90 degrees for each arrangement. The hardest part of the task is thus coming up with 
    neat enough code to do this bug free.

Time: O(1), Mem: O(1)
*/
#include <bits/stdc++.h>
using namespace std;

int h0, h1, h2, w0, w1, w2;
int main(){
    cin >> h0 >> w0;
    cin >> h1 >> w1;
    cin >> h2 >> w2;

    pair<int,int> rects[3];
    rects[0] = make_pair(h0, w0);
    rects[1] = make_pair(h1, w1);
    rects[2] = make_pair(h2, w2);

    bool has_valid = false;

    int arr[3] = {0,1,2};
    do{
        //cout << "---" << endl;
        for (int bm=0;bm<(1<<3);bm++){ // if ith bit is set, ith rectangle is flipped
            pair<int,int> rect0 = rects[arr[0]];
            pair<int,int> rect1 = rects[arr[1]];
            pair<int,int> rect2 = rects[arr[2]];

            if (bm & (1<<0)){
                rect0 = make_pair(rect0.second, rect0.first);
            }
            if (bm & (1<<1)){
                rect1 = make_pair(rect1.second, rect1.first);
            }
            if (bm & (1<<2)){
                rect2 = make_pair(rect2.second, rect2.first);
            }

            //printf("(%d, %d) (%d, %d) (%d, %d)\n", rect0.first, rect0.second, rect1.first, rect1.second, rect2.first, rect2.second);

            // check type (1.a)
            int height;
            int width; 
            if ((rect0.second == rect1.second) && (rect0.second == rect2.second)){ // condition for case 1: all widths the same
                height = rect0.first + rect1.first + rect2.first;
                width = rect0.second;
                if (width == height){
                    cout << "YES" << endl;
                    return 0;
                }
            }

            // check type (1.b)
            height = rect0.first + rect1.first;
            if (height != rect2.first) continue; // the height of the last rect must be the height of the thign
            if (rect0.second != rect1.second)continue; // widths of 2 rects must the same
            width = rect0.second + rect2.second;

            if (width == height){
                cout << "YES" << endl;
                return 0;
            }
        }

    }while(next_permutation(arr,arr+3));

    cout << "NO" <<endl;

    return 0;
}