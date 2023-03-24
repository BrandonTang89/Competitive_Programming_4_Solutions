/**Kattis - crackerbarrel
 * Mostly quite obvious but tedious DP. The state is just the state of the board. dp(board) returns
 * true if we can win from board or false otherwise. To make the state easier to deal with, we hash
 * it into a long long as a 15 digit integer in base num_colours. We can then use a hashtable to
 * memoize the results.
 *
 * If we haven't computed the result, first we "unroll" the board back into a useable vector
 * (actually can be avoided if we are willing to get the values directly from the hash but thats
 * abit of effort since the hash changes as num_colours changes). Then we check if we only have 1
 * piece left and if that is the target piece (base case). Else, we try moving each piece to all
 * possible places it could go according to a pre-written adjacency list where adjlist[u] containing
 * (c, npos) means we capture the piece in location c and move to location npos.
 * 
 * Time: not that easy to calculate since we visit a very limited subset of the state space.
 * Space: Similarly kinda hard to calculate.
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

unordered_map<string, int> colour_to_idx;
unordered_map<ll, bool> memo;
int target_idx, num_colours;

vector<vector<tuple<int, int>>> adjlist;
ll hash_board(vector<int> &board)
{
    assert(board.size() == 15);
    ll ans = 0;
    for (int i = 0; i < 15; i++) {
        ans = ans * num_colours + board[i];
    }
    return ans;
}

bool dp(ll board)
{
    if (memo.find(board) != memo.end()) return memo[board];  // already calculated
    // unwrap the board
    vector<int> board_vec(15);
    int num_peg = 0;
    for (int i = 14; i >= 0; i--) {
        board_vec[i] = board % num_colours;
        if (board_vec[i] != 0) num_peg++;
        board /= num_colours;
    }
    // if somehow num_peg == 0 we won't be able to move, so we would return false
    if (num_peg == 1) {
        for (int i = 0; i < 15; i++) {
            if (board_vec[i] != 0) {
                return memo[board] = (board_vec[i] == target_idx);
            }
        }
    }

    // try all possible moves
    for (int i = 0; i < 15; i++) {
        if (board_vec[i] != 0) {
            // We try moving this peg
            for (auto &[capture, npos] : adjlist[i]) {
                if (board_vec[capture] != 0 && board_vec[npos] == 0) {
                    // We can move this peg
                    int captured = board_vec[capture];
                    board_vec[npos] = board_vec[i];
                    board_vec[i] = 0;
                    board_vec[capture] = 0;
                    ll new_board = hash_board(board_vec);
                    if (dp(new_board)) {
                        return memo[board] = true;
                    }
                    board_vec[capture] = captured;
                    board_vec[i] = board_vec[npos];
                    board_vec[npos] = 0;
                }
            }
        }
    }
    return memo[board] = false;
}
int main()
{
    adjlist.assign(15, vector<tuple<int, int>>());
    adjlist[0].emplace_back(1, 3);     // capture 1, jump to 3
    adjlist[0].emplace_back(2, 5);     // capture 2, jump to 5
    adjlist[1].emplace_back(3, 6);     // capture 3, jump to 6
    adjlist[1].emplace_back(4, 8);     // capture 4, jump to 8
    adjlist[2].emplace_back(4, 7);     // capture 4, jump to 7
    adjlist[2].emplace_back(5, 9);     // capture 5, jump to 9
    adjlist[3].emplace_back(1, 0);     // capture 1, jump to 0
    adjlist[3].emplace_back(4, 5);     // capture 4, jump to 5
    adjlist[3].emplace_back(6, 10);    // capture 6, jump to 10
    adjlist[3].emplace_back(7, 12);    // capture 7, jump to 12
    adjlist[4].emplace_back(7, 11);    // capture 7, jump to 11
    adjlist[4].emplace_back(8, 13);    // capture 8, jump to 13
    adjlist[5].emplace_back(2, 0);     // capture 2, jump to 0
    adjlist[5].emplace_back(4, 3);     // capture 4, jump to 3
    adjlist[5].emplace_back(8, 12);    // capture 8, jump to 12
    adjlist[5].emplace_back(9, 14);    // capture 9, jump to 14
    adjlist[6].emplace_back(3, 1);     // capture 3, jump to 1
    adjlist[6].emplace_back(7, 8);     // capture 7, jump to 8
    adjlist[7].emplace_back(4, 2);     // capture 4, jump to 2
    adjlist[7].emplace_back(8, 9);     // capture 8, jump to 9
    adjlist[8].emplace_back(4, 1);     // capture 4, jump to 1
    adjlist[8].emplace_back(7, 6);     // capture 7, jump to 6
    adjlist[9].emplace_back(5, 2);     // capture 5, jump to 2
    adjlist[9].emplace_back(8, 7);     // capture 8, jump to 7
    adjlist[10].emplace_back(6, 3);    // capture 6, jump to 3
    adjlist[10].emplace_back(11, 12);  // capture 11, jump to 12
    adjlist[11].emplace_back(7, 4);    // capture 7, jump to 4
    adjlist[11].emplace_back(12, 13);  // capture 12, jump to 13
    adjlist[12].emplace_back(7, 3);    // capture 7, jump to 3
    adjlist[12].emplace_back(8, 5);    // capture 8, jump to 5
    adjlist[12].emplace_back(11, 10);  // capture 11, jump to 10
    adjlist[12].emplace_back(13, 14);  // capture 13, jump to 14
    adjlist[13].emplace_back(8, 4);    // capture 8, jump to 4
    adjlist[13].emplace_back(12, 11);  // capture 12, jump to 11
    adjlist[14].emplace_back(9, 5);    // capture 9, jump to 5
    adjlist[14].emplace_back(13, 12);  // capture 13, jump to 12
    while (1) {
        char tmp[2];
        string target;
        cin >> target;
        if (target == "**") break;

        colour_to_idx.clear();
        memo.clear();
        colour_to_idx["__"] = 0;  // empty space
        num_colours = 1;
        target_idx = num_colours;
        colour_to_idx[target] = num_colours++;

        vector<int> board(15);
        for (int i = 0; i < 15; i++) {
            string colour;
            scanf("%2s", tmp);
            colour = tmp;

            if (colour_to_idx.find(colour) == colour_to_idx.end()) {
                colour_to_idx[colour] = num_colours++;
            }
            board[i] = colour_to_idx[colour];
        }
        if (dp(hash_board(board))) {
            cout << "Possible" << endl;
        }
        else
            cout << "Impossible" << endl;
    }

    return 0;
}