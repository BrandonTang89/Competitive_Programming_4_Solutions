/* Kattis - virus
Observation 1:
    To find out where the insertion / removal occured. We just find the first and last difference in the 2 strings.
    The answer is then just the length of the difference in the target!

Time: O(max(length of both string))
Mem: O(length of both strings)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;
 
typedef long long ll;
typedef long double ld; 
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
 
string ori, target;
deque<char> ori_d, tar_d;
int main(){
    cin >> ori >> target;
    for (auto i: ori){
        ori_d.push_back(i);
    }
    for (auto i: target){
        tar_d.push_back(i);
    }


    while (tar_d.front() == ori_d.front()){
        tar_d.pop_front();
        ori_d.pop_front();

        if (tar_d.empty() || ori_d.empty())break;
    }
    if (!(tar_d.empty() || ori_d.empty())){
        while (tar_d.back() == ori_d.back()){
            tar_d.pop_back();
            ori_d.pop_back();
            if (tar_d.empty() || ori_d.empty())break;
        }
    }

    cout << tar_d.size() << endl;
    return 0;
}