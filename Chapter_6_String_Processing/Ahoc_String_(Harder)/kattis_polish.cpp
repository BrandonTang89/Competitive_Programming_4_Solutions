/**Kattis - polish
 * Recurxively parse the expression. If exp is of the form OP a b where fn(a) and fn(b) are numbers
 * then we can evaluate it. Else just evaluate the subexpressions and return OP (fn(a)) (fn(b)).
 * Need to make the observation that a subexpression is well formed once num_ops + 1 = num_vals.
 * 
 * Time: O(n^2), Space: O(n)
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

unordered_set<string> ops = {"+", "-", "*"};

vector<string> v;
string fn(int l, int r) {
    if (l == r) {
        return v[l];
    }

    int num_vals = 0;
    int num_ops = 0;

    int left_end = -1;
    for (int i = l + 1; i < r; i++) {
        if (ops.count(v[i])) {
            num_ops++;
        } else {
            num_vals++;
        }

        if (num_ops + 1 == num_vals) {
            left_end = i;
            break;
        }
    }
    assert(left_end != -1);
    // left side is from l+1 to left_end, right side is from left_end+1 to r
    string left = fn(l + 1, left_end);
    string right = fn(left_end + 1, r);

    bool left_is_num = false, right_is_num = false;
    try {
        stoi(left);
        left_is_num = true;
    } catch (...) {
        left_is_num = false;
    }
    try {
        stoi(right);
        right_is_num = true;
    } catch (...) {
        right_is_num = false;
    }

    if (left_is_num && right_is_num) {
        if (v[l] == "+") {
            return to_string(stoi(left) + stoi(right));
        }
        if (v[l] == "-") {
            return to_string(stoi(left) - stoi(right));
        }
        if (v[l] == "*") {
            return to_string(stoi(left) * stoi(right));
        }
        assert(false);
    } else {
        return v[l] + " " + left + " " + right;
    }
}
int main() {
    string line, s;
    int tc = 0;
    while (getline(cin, line)) {  // getline until EOF
        istringstream ss(line);
        v.clear();
        while (ss >> s) {
            v.emplace_back(s);
        }
        cout << "Case " << ++tc << ": " << fn(0, v.size() - 1) << endl;
    }

    return 0;
}