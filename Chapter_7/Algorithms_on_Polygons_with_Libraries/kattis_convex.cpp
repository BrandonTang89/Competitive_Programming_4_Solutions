/**Kattis - convex
 * A theoratically challenging problem! First obvserve that our polygon can only have points turning
 * all in 1 direction, and its shape should resembling something like a badly formed circle.
 *
 * We used ideas from https://cglab.ca/~sander/misc/ConvexGeneration/convex.html.
 * Essentially, realise that if we have a bunch of non-parallel vectors, we can join them together
 * to make a polygon. We can represent each vector by its height and width. To know which vectors
 * are good vectors to select, we know that if we select vector a/b, then it would make sense to
 * select vector b/a as well (for symmetry since our board is symmetrical). The cost (in terms of
 * increase in length of polygon) of both a/b and b/a is actually 2*(a+b) for a quadrant of a
 * polygon. So we can actually view the cost of a vector as a+b. So we should generate the vectors
 * in increasing a+b. How to do this? we use the zigzag pattern seen in the proof that the set of
 * rational numbers is countable! While doing so, we use GCD to skip over vectors that are parrallel
 * to previous vectors. We know this is the case if GCD(a, b) is not 1.
 *
 * Okay notice that actually we should generate like a ton of vectors, but due to symmetry, we only
 * need to generate 1/4 of the vectors (for 1 quadrant). But actually we don't even need that, we
 * use the above GCD process to generate 1/8 of the vectors for 1/8 of the polygon, then we add
 * vector a/b if b/a was generated to from all the vectors for 1 quadrant. Then for the rest of the
 * 3, we can just apply a direction multiplier to the vector.
 *
 * Once we have the vectors for 1 quadrant, we can sort based on the angle. We know this by taking
 * the a/b to be 1/gradient (i should have done b/a but its too late for that). We can then figure
 * out whether to take the vectors from left to right or right to left for the different parts of
 * the polygon.
 *
 * Using these ideas, we can walk around the polygon and generate points until we generate enough
 * points. At which point, the polygon will probably be out of the boundary, so we find the minimum
 * y value and translate the entire polygon upwards. Note that the x values will be positive.
 *
 * Implementation wise, theres some loose ends to tie up, like how to know how many vectors to
 * generate, how to join the parts of hte polygon together, etc. Just read to find out.
 *
 * Time: O(n log n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int n;
vector<pair<int, int>> starting_vector = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
vector<pair<int, int>> dir = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
vector<pair<int, int>> generate_vector() {
    int target_num_vectors = ceil(n / 8.0);
    vector<pair<int, int>> vecs;
    for (int j = 1; (int)vecs.size() < target_num_vectors; j++) {
        for (int den = 1; j - den + 1 >= den; den++) {
            int num = j - den + 1;
            // cout << num << "/" << den << endl;
            if (__gcd(num, den) == 1) {
                vecs.push_back(make_pair(num, den));
                if ((int)vecs.size() == target_num_vectors) break;
            }
        }
    }
    // Get the reciprocal of the vectors, excluding 1/1 -> 1/1
    for (int i = 1; i < target_num_vectors; i++) {
        vecs.push_back(make_pair(vecs[i].second, vecs[i].first));
    }
    return vecs;
}

bool comp(pair<int, int> a, pair<int, int> b) {
    return (a.first / (double)a.second >
            b.first / (double)b.second);  // 1/gradient of a > 1/gradient of b
}

int main() {
    cin >> n;
    vector<pair<int, int>> vecs = generate_vector();
    sort(vecs.begin(), vecs.end(), comp);

    int x = 0, y = 0;
    vector<pair<int, int>> ans;
    for (int part = 0; part < 4 && ((int)ans.size() < n); part++) {
        x += starting_vector[part].first;
        y += starting_vector[part].second;

        ans.push_back(make_pair(x, y));

        for (int i = 0; i < (int)vecs.size() && ((int)ans.size() < n); i++) {
            int index = (part % 2 == 0) ? (vecs.size() - i - 1) : i;
            x += dir[part].first * vecs[index].first;
            y += dir[part].second * vecs[index].second;
            ans.push_back(make_pair(x, y));
        }
    }
    int minimum_y = INT_MAX;
    for (int i = 0; i < (int)ans.size(); i++) {
        minimum_y = min(minimum_y, ans[i].second);
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i].first << " " << -minimum_y + ans[i].second << endl;
        assert(ans[i].first <= 4e7);
    }

    return 0;
}