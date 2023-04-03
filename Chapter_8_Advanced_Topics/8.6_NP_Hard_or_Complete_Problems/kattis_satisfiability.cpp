/**Kattis - satisfiability
 * Mostly an input parsing problem...
 * The actual satisfiability is just using a 2^n iterative brute force where we check whether each
 * clause is satisfied in each state. The input parsing is a matter of removing the 'v's, split by
 * spaces, then get rid of the negation sign and convert the rest to int.
 * Time: O(2^n * nc), Space: O(n*c)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int n, c;
vector<vector<int>> negated, val;  // negated[i] = 1 if negated, 0 otherwise
int main()
{
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n >> c;
        negated.assign(c, vector<int>());
        val.assign(c, vector<int>());
        cin.ignore();

        for (int i = 0; i < c; i++) {
            string s;
            getline(cin, s);
            s.erase(remove(s.begin(), s.end(), 'v'), s.end());

            istringstream ss(s);
            string term;
            while (ss >> term) {
                if (term[0] == '~') {
                    negated[i].push_back(1);
                    term.erase(term.begin());
                }
                else {
                    negated[i].push_back(0);
                }
                term.erase(term.begin());
                val[i].push_back(stoi(term) - 1);
            }
        }

        bool canbesat = false;
        for (int i = 0; i < (1 << n); i++) {
            bool sat = true;
            for (int j = 0; j < c; j++) {
                bool clause_sat = false;
                for (int k = 0; k < (int)val[j].size(); k++) {
                    if (negated[j][k] == 0 && (i & (1 << (val[j][k]))) != 0) {
                        clause_sat = true;
                        break;
                    }
                    else if (negated[j][k] == 1 && (i & (1 << (val[j][k]))) == 0) {
                        clause_sat = true;
                        break;
                    }
                }
                if (!clause_sat) {
                    sat = false;
                    break;
                }
            }
            if (sat) {
                cout << "satisfiable" << endl;
                canbesat = true;
                break;
            }
        }
        if (!canbesat) {
            cout << "unsatisfiable" << endl;
        }
    }

    return 0;
}