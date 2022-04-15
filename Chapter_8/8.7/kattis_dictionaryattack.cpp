/**Kattis - dictionaryattack
 * This is kinda like a meet in the middle thing. Essentially from the acceptable words, we generate
 * all words that are reachable with <= 3 adjacent transpositions. Then from the candidate words, we
 * generate all words that replace the numbers with some selection of alphabets. Then we check if the
 * candidate word with the replaced numbers is in the acceptable words. Note that we should track
 * the number of moves done / left from either direction.
 * 
 * Time: O(n^3 log n + (26*2)^3 * q log n), Space: O(n^3)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

set<pair<string, int>> unacceptable;
int n;

void process(string s, int moves_left){
    unacceptable.insert({s, moves_left});
    if(moves_left == 0) return;

    // try swapping every adajacent digit
    for(int i = 0; i < (int) s.size(); i++){
        if(i + 1 < (int) s.size() && s[i] != s[i + 1]){
            string t = s;
            swap(t[i], t[i + 1]);
            if(unacceptable.find({t, moves_left-1}) == unacceptable.end()){
                process(t, moves_left - 1);
            }
        }
    }
}

string lower_and_upper_alphabets = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
bool check_acceptable(string s, vector<int>digit_pos, int moves_done){ // return true if accept
    if ((int) digit_pos.size() == moves_done){
        bool acceptable = true;
        for (int i = moves_done; i<=3; i++){
            if (unacceptable.count({s, i})){
                acceptable = false;
                break;
            }
        }
        return acceptable;
    }

    int digit = digit_pos[moves_done];
    string t = s;
    for (auto c: lower_and_upper_alphabets){
        t[digit] = c;
        if (!check_acceptable(t, digit_pos, moves_done+1)){
            return false;
        }
    }
    return true;
}
int main(){
    cin >> n;
    string s;
    for (int i = 0; i < n; i++) {
        cin >> s;
        process(s, 3);
    }

    while (cin >> s){
        int num_digits = 0;
        vector<int> digit_pos;
        for (int i = 0; i < (int) s.size(); i++) {
            if (isdigit(s[i])){
                num_digits++;
                digit_pos.push_back(i);
            }

        }

        if (num_digits > 3 || check_acceptable(s, digit_pos, 0)){
            cout << s << endl;
        }

    }


    return 0;
}