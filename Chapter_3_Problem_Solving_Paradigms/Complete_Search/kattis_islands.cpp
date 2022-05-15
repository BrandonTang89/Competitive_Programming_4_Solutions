/* Kattis - islands
An nice problem that allows us to practise our bitmask techniques.

Observation 1:
    There is always only 10 variable bits that be part of islands, and only a small portion (55/1023) of the 2^10 subsets
    of these bits are contiguous and could be an island. As such, we choose to pre-compute the vector of valid bitmasks
    instead of redoing the check for valid bitmasks every test case.

    This could be even more optimised if we just printed the valid bitmasks in one run of the programme and then hardcoded
    the bitmasks into the vector for the submission programme. However this isnt necessary as there are only 1023 bitmasks
    to check and we are using efficient operations to check the bitmasks.

Time: O(55 * 12 * c) = O(c) but with high constant factor that has been optimised
Mem: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

#define LSOne(S) ((S) & -(S))

vector<int> valid_bm;
int least_sig, most_sig, total_set;

void fill_valid_bm(){
    
    for(int bm=1;bm<(1<<10);bm++){
        least_sig = LSOne(bm);
        least_sig = __builtin_ctz(least_sig); // position of least significant bit
        most_sig = (int)(log2(bm)); //position of most significant bit

        total_set = __builtin_popcount(bm);
        if (total_set == (most_sig - least_sig+1)){
            valid_bm.emplace_back(bm);
        }
    }

    //cout << "valid bm size " << valid_bm.size() << endl;
}

int n, c, dummy, islands; // n and case number
int element_before, element_after, max_immediate;
int arr[12];
bool valid;
int main(){
    fill_valid_bm();

    cin >> c;
    for(int c_num=1; c_num<= c; c_num++){
        cin >> dummy;
        for(int i=0;i<12;i++){
            cin >> arr[i];
        }

        islands = 0;
        for(auto bm:valid_bm){
            least_sig = LSOne(bm);
            least_sig = __builtin_ctz(least_sig);
            most_sig = (int) log2(bm);

            valid = true;
            element_before = arr[most_sig+2];
            element_after = arr[least_sig]; //least and most sig from 0 to 9

            max_immediate = max(element_before, element_after);

            for(int i=least_sig+1; i<most_sig+2; i++){
                if (arr[i] <= max_immediate){
                    valid = false;
                    break;
                }
            }

            if (valid)islands++;
        }

        cout << dummy << " " << islands << endl;

    }




    return 0;
}