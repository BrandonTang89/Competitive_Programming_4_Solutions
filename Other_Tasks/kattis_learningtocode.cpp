/**Kattis - learningtocode
 * Writing a recursive parser. Not too hard except for the traps.
 * 1. $ can be part of the string without {
 * 2. The variables can be super long, but if such variables exist, they will not be used for
 * printing so we can just stop computing their values
 *
 * Other than that, we should replace spaces so we can use istringstream while considering the
 * spaces. Then we can put them back when we are printing the result
 *
 * Time: O(n), Space: O(?)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

unordered_map<string, string> envt;

const int MAXLENGTH = 10001;
pair<string, bool> expr(istringstream &iss)
{  // The prefix of iss should be an expression, returns whether the expr is a variable
    char c;
    iss >> c;
    if (c == '`' || c == '\"') {
        string s = "";
        while (iss >> c && c != '`' && c != '\"' && s.length() < MAXLENGTH) {
            if (c == '$' && iss.peek() == '{') {
                iss >> c;  // {
                auto [res, is_var] = expr(iss);
                if (!is_var) {
                    iss >> c;  // }
                }
                s += res;
            }
            else {
                s += c;
            }
        }
        return make_pair(s, false);
    }
    else {  // must be a variable
        string var = "";
        var += c;
        while (iss >> c && (isalpha(c) || c == '_')) {
            var += c;
        }

        if (envt.find(var) == envt.end()) {
            throw "Variable " + var + " not found";
        }

        return make_pair(envt[var], true);
    }
}
int main()
{
    string line;
    while (true) {
        getline(cin, line);
        if (line == "end.") break;
        bool isdecl = (line[0] == 'v');
        if (isdecl) {
            line = line.substr(4, line.length() - 4);
        }
        else {
            line = line.substr(6, line.length() - 6);
        }
        line = line.substr(0, line.length() - 1);  // remove the ;
        line = regex_replace(line, regex(" "), "~");

        istringstream iss(line);
        string temp;
        if (isdecl) {
            string var, val;
            char c;
            while (iss >> c && c != '~') {
                var += c;
            }
            iss >> c;  // =
            iss >> c;  // ~

            val = expr(iss).first;
            envt[var] = val;
        }
        else {
            string res = expr(iss).first;
            res = regex_replace(res, regex("~"), " ");
            cout << res << endl;
        }
    }

    return 0;
}