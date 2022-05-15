/* Kattis - Dobra
This could be difficult or intimidating to those new to recursive backtracking (like the me who wrote this).
The concept itself is pretty simple, just gotta make sure to write the code carefully to not run into bugs

Debugging:
    - since there can be up to (10^26) different ways to make the words (obviously not all will be valid),
      use long long where needed
    - Don't need to reset s[first_pos] to '_' since we do the recursion from left to right and deeper levels
      will have already had s[first_pos] set to the correct values

Optimisations:
    - the use of the has_l bool variable ensures there no need to do a linear scan for each verification
    - prune early (before calling backtrack instead of during verification) to ensure maximal efficienc

Time: O(3^num_of_underscore), Mem: O(len(s))
*/

#include <bits/stdc++.h>
using namespace std;

unordered_set<char> cons = {'B', 'C', 'D', 'F', 'G', 'H', 'J',
                            'K', 'M', 'N', 'P', 'Q', 'R',  // removed L
                            'S', 'T', 'V', 'W', 'X', 'Y', 'Z'};

unordered_set<char> vowels = {'A', 'E', 'I', 'O', 'U'};

bool iscons(char c) {
    if (c == 'C' || c == 'L') return true;
    return false;
}

bool isvowel(char c) {
    if (c == 'V') return true;
    return false;
}

long long backtrack(string s, bool has_l) {
    // cout << "S: " << s << endl;
    int n = s.length();
    int first_pos = -1;
    for (int i = 0; i < n; i++) {
        if (s[i] == '_') {
            first_pos = i;
            break;
        }
    }

    if (first_pos == -1) {  // check for validity
        if (has_l)
            return 1;
        else
            return 0;
    }

    // check restrictions
    bool other_2_vowels = false;
    bool other_2_cons = false;
    if (first_pos <= n - 3) {  // check with _AA pattern
        if (iscons(s[first_pos + 1]) && iscons(s[first_pos + 2])) {
            other_2_cons = true;
        }
        if (isvowel(s[first_pos + 1]) && isvowel(s[first_pos + 2])) {
            other_2_vowels = true;
        }
    }
    if (first_pos >= 2) {  // check with AA_
        if (iscons(s[first_pos - 1]) && iscons(s[first_pos - 2])) {
            other_2_cons = true;
        }
        if (isvowel(s[first_pos - 1]) && isvowel(s[first_pos - 2])) {
            other_2_vowels = true;
        }
    }
    if (first_pos >= 1 && first_pos <= n - 2) {  // check with A_A
        if (iscons(s[first_pos - 1]) && iscons(s[first_pos + 1])) {
            other_2_cons = true;
        }
        if (isvowel(s[first_pos - 1]) && isvowel(s[first_pos + 1])) {
            other_2_vowels = true;
        }
    }

    long long valids = 0;
    if (!other_2_cons) {
        s[first_pos] = 'C';
        valids += backtrack(s, has_l) * 20;
        s[first_pos] = 'L';
        valids += backtrack(s, true);
    }
    if (!other_2_vowels) {
        s[first_pos] = 'V';
        valids += backtrack(s, has_l) * 5;
    }

    return valids;
}

string init;
int main() {
    cin >> init;

    bool has_l = false;
    for (int i = 0; i < init.length(); i++) {
        if (init[i] == 'L') {
            has_l = true;
            continue;
        }
        if (cons.find(init[i]) != cons.end()) {
            init[i] = 'C';
        } else if (vowels.find(init[i]) != vowels.end()) {
            init[i] = 'V';
        }
    }
    cout << backtrack(init, has_l) << endl;

    return 0;
}