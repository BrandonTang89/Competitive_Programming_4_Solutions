/**Kattis - boggle
 * Recursive backtracking is used for each possible starting location and for each word.
 * Take note to prune ASAP and to reset the board before returning values also note that words
 * could be of <= 2 length, in which case return 0 score.
 * 
 * Time: O(w*b), Space: O(w)
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

int w, b;
vector<string> words;
char board[4][4];
bool board_used[4][4];  // 1 if used
int dr[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dc[] = {0, 1, 1, 1, 0, -1, -1, -1};

bool can_find(int r, int c, int word_index, int char_index) {
    if (r < 0 || r >= 4 || c < 0 || c >= 4 || board_used[r][c]) {
        return false;
    }
    if (board[r][c] != words[word_index][char_index]) {
        return false;
    }
    if (char_index == (int)words[word_index].size() -1) {
        return true;
    }
    board_used[r][c] = true;
    for (int i = 0; i < 8; i++) {
        if (can_find(r + dr[i], c + dc[i], word_index, char_index + 1)) {
            board_used[r][c] = false;
            return true;
        }
    }
    board_used[r][c] = false;
    return false;
}

int score(string s) {
    if (s.size() <= 2) return 0;
    if (s.size() == 3 || s.size() == 4) return 1;
    if (s.size() == 5) return 2;
    if (s.size() == 6) return 3;
    if (s.size() == 7) return 5;
    return 11;
}

string getlongerstring(string s1, string s2) {
    if (s1.size() > s2.size()) {
        return s1;
    }
    if (s1.size() < s2.size()) {
        return s2;
    }
    return s1 < s2 ? s1 : s2;
}
int main() {
    fast_cin();
    cin >> w;
    for (int i = 0; i < w; i++) {
        string s;
        cin >> s;
        words.push_back(s);
    }

    cin >> b;
    for (int board_num = 0; board_num < b; board_num++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                cin >> board[i][j];
            }
        }
        memset(board_used, 0, sizeof(board_used));
        int num_words = 0;
        int max_score = 0;
        string longest_string = "";
        for (int i = 0; i < w; i++) {
            bool found = false;
            for (int r = 0; r < 4; r++) {
                for (int c = 0; c < 4; c++) {
                    if (can_find(r, c, i, 0)) {
                        found = true;
                        break;
                    }
                }
                if (found) {
                    break;
                }
            }
            if (found) {
                num_words++;
                max_score += score(words[i]);
                longest_string = getlongerstring(longest_string, words[i]);
            }
        }

        cout << max_score << " " << longest_string << " " << num_words << endl;
    }

    return 0;
}