/**Kattis - substringswitcheroo
 * In this question, we need to be able to quickly check if there exist a common substring anagram
 * of length k between 2 strings. Rather than worrying about hashing our direct addressing table in
 * our function, we opt to use a binary search tree. Since the vector is of fixed size, comparisions
 * are O(1), allowing for O(log n) insertion and find. As we process all the substrings of length k
 * for both A and B and attempt insert / find the vector in the BST, our time complexity for the
 * function is O(n log n). Since we try all values of k from n to 1 we get:
 * 
 * Time Complexity: O(n^2 log n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

pair<bool, int> find_length_k_common_anagram(string A, string B, int k) {
    // O(n log n) returns whether can, and index in B
    if (k == 0) return {true, 0};
    int n = A.size();          // same length
    set<vector<int>> seen;     // set of seen anagrams
    vector<int> count(26, 0);  // DAT
    for (int i = 0; i < k; i++) {
        count[A[i] - 'a']++;
    }
    seen.insert(count);
    for (int i = k; i < n; i++) {  // anagram starts from i in A
        count[A[i - k] - 'a']--;
        count[A[i] - 'a']++;
        seen.insert(count);
    }

    count.assign(26, 0);
    for (int i = 0; i < k; i++) {
        count[B[i] - 'a']++;
    }
    if (seen.count(count)) return {true, 0};
    for (int i = k; i < n; i++) {
        count[B[i - k] - 'a']--;
        count[B[i] - 'a']++;
        if (seen.count(count)) return {true, i-k+1};
    }

    return {false, -1};
}

int num_tc;
string A, B;
int main() {
    fast_cin();
    cin >> num_tc;
    for (int tc = 0; tc < num_tc; tc++) {
        cin >> A >> B;

        // Binary search for largest k
        bool done = false;
        for (int l = A.size(); l > 0; l--) {
            pair<bool, int> ans = find_length_k_common_anagram(B, A, l); // Swap A and B since we want index in A
            if (ans.first) {
                cout << A.substr(ans.second, l) << endl;
                done = true;
                break;
            }
        }
        if (done) {
            continue;
        }
        cout << "NONE\n";
    }

    return 0;
}
