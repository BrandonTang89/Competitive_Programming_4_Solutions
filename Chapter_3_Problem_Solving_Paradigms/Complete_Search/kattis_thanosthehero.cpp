/* Kattis - thanosthehero

Observation 1:
    we should go from the last world to the first as going in that order ensures that we don't have to
    revisit the worlds we have already visited and can use the greedy approach.

    If we were to go from world 0 to 2 in {2,2,2} with greedy approachh, we would kill 1 in the first world 
    {1, 2, 2} and 1 in the next {1,1,2} but still need to revist the first world to make the optimal configuration {0,1,2}
    
    Going from the back, greedily minimising the number of people killed so that the world we are visiting has less people
    than the world we just visited results in {2,2,2} -> {2,1,2} -> {0,1,2}. Ie a simple linear approach.

Time: O(n), Mem: O(n) [could be done in O(1) mem but overkill]
*/

#include <bits/stdc++.h>
using namespace std;

int n, temp, change;
long long kills = 0;
vector<int> arr;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> temp;
        arr.emplace_back(temp);
    }
    reverse(arr.begin(), arr.end());

    int max_val = arr[0] - 1;
    bool impossible = false;
    for (int i = 1; i < n; i++) {
        // printf("max val %d\n", max_val);
        if (arr[i] >= max_val) {
            kills += (arr[i] - max_val);
            arr[i] = max_val;
            max_val--;
        } else {
            max_val = arr[i] - 1;
        }

        if (max_val < 0) {
            impossible = true;
            break;
        }
    }

    if (impossible) {
        cout << 1 << endl;
    } else {
        cout << kills << endl;
    }

    return 0;
}