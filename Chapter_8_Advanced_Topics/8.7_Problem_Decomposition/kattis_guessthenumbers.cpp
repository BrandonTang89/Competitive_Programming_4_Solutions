/**Kattis - guessthenumbers
 * Again!!! Remember to sort the vector before doing the do while loop!!!! Other than that,
 * implement a easy version of shunting yard and post fix calculator.
 * 
 * Time: O(n! * k), Space: O(k) where k is the expression size
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
vector<char> shunting_yard(string &s) {
    int var_counter = 0;
    vector<char> ans;
    stack<char> st;
    for (auto &c : s) {
        if (isalpha(c)) {
            ans.push_back('0' + var_counter);
            var_counter++;
        } else if (c == '(') {
            st.emplace(c);
        } else if (c == ')') {
            ans.emplace_back(st.top());
            st.pop();
            st.pop();
        } else {  // operator
            st.emplace(c);
        }
    }
    while (!st.empty()) {
        ans.emplace_back(st.top());
        st.pop();
    }
    return ans;
}

int substitute(vector<int> &vars, vector<char> &expr) {
    stack<int> st;
    int a, b;
    for (auto &c : expr) {
        if (isdigit(c)) {
            st.emplace(vars[c - '0']);
        } else if (c == '+') {
            a = st.top();
            st.pop();
            b = st.top();
            st.pop();
            st.emplace(a + b);
        } else if (c == '-') {
            a = st.top();
            st.pop();
            b = st.top();
            st.pop();
            st.emplace(b - a);
        } else if (c == '*') {
            a = st.top();
            st.pop();
            b = st.top();
            st.pop();
            st.emplace(a * b);
        }
    }
    return st.top();
}
int n, target;
vector<int> vars;
int main() {
    while (true) {
        cin >> n;
        if (n == 0) break;
        vars.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> vars[i];
        }
        cin >> target;
        string s;
        cin >> s;
        auto v = shunting_yard(s);

        bool possible = false;
        sort(vars.begin(), vars.end());
        do {
            if (substitute(vars, v) == target) {
                cout << "YES" << endl;
                possible = true;
                break;
            }
        } while (next_permutation(vars.begin(), vars.end()));
        if (!possible) cout << "NO" << endl;
    }

    return 0;
}