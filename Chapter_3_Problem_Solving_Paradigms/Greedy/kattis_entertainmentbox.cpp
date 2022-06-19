/**Kattis - entertainmentbox
 * 99% similar to kattis-classrooms, just that here we can have one slot take 2 shows such that the
 * first show ends exactly when the second starts. This is reflected by a change from using
 * upperbound to lowerbound. Look at kattis_classroms.cpp for more details.
 * 
 * Time: O(n log n), Space: O(n + k)
 */
#include <bits/stdc++.h>
using namespace std;

int n, k, s, f;
vector<pair<int, int>> v;
multiset<int> ms;
int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &s, &f);
        v.emplace_back(make_pair(f, s));
    }

    sort(v.begin(), v.end());
    for (int i = 0; i < k; i++) ms.insert(0);

    int counter = 0;
    for (auto a : v) {
        f = a.first;
        s = a.second;

        // printf("considering activity: %d %d\n", s, f);
        auto it = ms.lower_bound(-s);
        if (it == ms.end()) continue;  // cannot fit this activity

        ms.insert(-f);
        ms.erase(it);
        counter++;
    }

    printf("%d\n", counter);
    return 0;
}