/**Kattis - animal
 * This was a difficult but worthy problem to solve.
 * So here we are trying to compare for common different groups ie same subset of animals.
 * However notice that compared to regular string matching, here there are many brackets and
 * the order within each set should not be considered, so we can't just use the rolling hash
 * we have learnt about directly,
 *
 * So how should we represent the sets of animals? Well the idea is to use a binary string
 * representation of the set, where the ith bit represents the ith animal. This is valid since each
 * animal can only be either present or not present in each set. But now how do we hash the
 * binary string? We can simply use the rolling hash alogrithm we learnt before! But it wouldn't
 * be fast to keep using the rolling hash again and again after constructing different sets.
 *
 * We need to observe that the rolling hash is just the sum of p^i mod M for all the i that are
 * set. This means that if we want to merge 2 disjoint sets, we can just sum their hashes, this
 * property is key since we will only ever be summning disjoint sets for this problem. This way we
 * avoid manipulating actual strings or even worse: actual sets.
 * 
 * The overall idea is thus fairly straight forward: For each subset in A, add the hash of the set to
 * a hashtable. For each subset in B, check if the hash of the set is present in the hashtable.
 * 
 * The other half of the challenge is the implementation, we use a double stack based approach
 * where a stack stores the actual hashes which the other stores how many hashes to "union"
 * upon reaching a ')' bracket, representing the number of hashes within the current bracket.
 * Whenever we reach a ')' bracket, we sum up the relevant hashes, this forms a unique subset.
 * 
 * Note that since the numbers have more than 1 digit, we need to use a string variable (cur) to
 * accumulate digits that form 1 number before hashing the binary representation of the set
 * with just that number. This is slightly tricky, but will work fine.
 * 
 * However, we note a WA verdict when we just apply the above.. this is due to collisions and thus
 * we need to actually do 2 hashes with different p values and for each subset, generate the pair
 * of 2 hashes and store it in our unordered_set. This greatly reduces the probability of collisons,
 * allowing the code to work. Note that C++ does not natively support hashing a pair for use in
 * unordered_set, so we need to use a custom hash function (yes ik very confusion cos multiple hashes).
 * 
 * Time: O(n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
struct pair_hash {
    inline std::size_t operator()(const std::pair<int, int>& v) const {
        return v.first * 31 + v.second;
    }
};
typedef long long ll;

const ll M = (1LL << 31) - 1;
const ll p1 = 131, p2 = 313;
vector<ll> p1powers, p2powers;  // 2^i mod M
void computePpowers(int n) {
    p1powers.push_back(1);
    for (int i = 1; i <= n; i++) {
        p1powers.push_back((p1powers[i - 1] * p1) % M);
    }
    p2powers.push_back(1);
    for (int i = 1; i <= n; i++) {
        p2powers.push_back((p2powers[i - 1] * p2) % M);
    }
}
ll fhash(int i, ll p) { return (p == p1) ? p1powers[i] : p2powers[i]; }

int n, ans = 0;
string A, B, cur;
stack<pair<int, int>> st;  // contains the hashes
stack<int> num_sets_at_level;
unordered_set<pair<int, int>, pair_hash> hashes;  // contains hashes of sub trees of a
int main() {
    cin >> n;
    computePpowers(n + 9);
    cin >> A >> B;

    for (int i = 0; i < (int)A.length(); i++) {
        if (A[i] == '(') {
            num_sets_at_level.push(1);
        } else {
            if (A[i] != ')' && A[i] != ',') {  // num char
                cur += A[i];
            } else {
                if (cur.length() > 0) {
                    st.push(make_pair(fhash(stoi(cur), p1), fhash(stoi(cur), p2)));
                    cur = "";
                }

                if (A[i] == ',') {
                    num_sets_at_level.top()++;
                } else {  // A[i] == ')'
                    ll temp1 = 0, temp2 = 0;
                    for (int i = 0; i < num_sets_at_level.top(); i++) {
                        temp1 += (ll)st.top().first;
                        temp1 %= M;
                        temp2 += (ll)st.top().second;
                        temp2 %= M;

                        st.pop();
                    }
                    hashes.insert(make_pair(temp1, temp2));

                    st.push(make_pair(temp1, temp2));
                    num_sets_at_level.pop();
                }
            }
        }
    }
    for (int i = 0; i < (int)B.length(); i++) {
        if (B[i] == '(') {
            num_sets_at_level.push(1);
        } else {
            if (B[i] != ')' && B[i] != ',') {  // num char
                cur += B[i];
            } else {
                if (cur.length() > 0) {
                    st.push(make_pair(fhash(stoi(cur), p1), fhash(stoi(cur), p2)));
                    cur = "";
                }

                if (B[i] == ',') {
                    num_sets_at_level.top()++;
                } else {  // A[i] == ')'
                    ll temp1 = 0, temp2 = 0;
                    for (int i = 0; i < num_sets_at_level.top(); i++) {
                        temp1 += (ll)st.top().first;
                        temp1 %= M;
                        temp2 += (ll)st.top().second;
                        temp2 %= M;

                        st.pop();
                    }

                    if (hashes.find(make_pair(temp1, temp2)) != hashes.end()) {
                        ans++;
                    }
                    st.push(make_pair(temp1, temp2));
                    num_sets_at_level.pop();
                }
            }
        }
    }

    cout << ans + n << endl;
    return 0;
}