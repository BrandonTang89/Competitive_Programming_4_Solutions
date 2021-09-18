// UVa 255 Correct Move
// Basic checking of moves
// Time: O(TC), Mem: O(1)
#include <bits/stdc++.h>
using namespace std;

int king_init, queen_init, queen_new;
pair<int,int> king_init_2d, queen_init_2d, queen_new_2d;

int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,-1,1};

pair<int, int> two_d_index(int index){
    return make_pair(index/8, index%8);
}

int main(){
    while (cin >> king_init){
        cin >> queen_init >> queen_new;

        if (king_init == queen_init){
            cout << "Illegal state" << endl;
            continue;
        }

        king_init_2d = two_d_index(king_init);
        queen_init_2d = two_d_index(queen_init);
        queen_new_2d = two_d_index(queen_new);

        if (queen_new_2d.first != queen_init_2d.first && queen_init_2d.second != queen_new_2d.second){
            cout << "Illegal move" << endl;
            continue;
        }

        if (queen_init == queen_new){
            cout << "Illegal move" << endl;
            continue;
        }

        if (queen_init_2d.first == king_init_2d.first && queen_new_2d.first == king_init_2d.first){
            int bigger_value = max(queen_init_2d.second, queen_new_2d.second);
            int smaller_value = min(queen_init_2d.second, queen_new_2d.second);

            if (king_init_2d.second <= bigger_value && king_init_2d.second >= smaller_value){
                cout << "Illegal move" << endl;
                continue;
            }
        }

        if (queen_init_2d.second == king_init_2d.second && queen_new_2d.second == king_init_2d.second){
            int bigger_value = max(queen_init_2d.first, queen_new_2d.first);
            int smaller_value = min(queen_init_2d.first, queen_new_2d.first);

            if (king_init_2d.first <= bigger_value && king_init_2d.first >= smaller_value){
                cout << "Illegal move" << endl;
                continue;
            }
        }

        // Check if king can jump onto new queen
        bool allowed = true;
        for (int i=0;i<4;i++){
            pair<int, int>king_new_2d = make_pair(king_init_2d.first + dx[i], king_init_2d.second + dy[i]);
            if (king_new_2d == queen_new_2d){
                allowed = false;
                break;
            }
        }
        if (!allowed){
            cout << "Move not allowed" << endl;
            continue;
        }

        if (queen_new == 49 && king_init == 56){
            cout << "Stop" << endl;
            continue;
        }
        if (queen_new == 9 && king_init == 0){
            cout << "Stop" << endl;
            continue;
        }
        if (queen_new == 14 && king_init == 7){
            cout << "Stop" << endl;
            continue;
        }
        if (queen_new == 54 && king_init == 63){
            cout << "Stop" << endl;
            continue;
        }

        cout << "Continue" << endl;
        
    }

    return 0;
}