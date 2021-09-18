// UVa 10388 Snap
// Use basic deque operations and the random() function to simulate a card game
// Annoying presentation errors from printing extra newline chars. Also remember to clean up data structures between test cases!
// Time: O(1) since limited by 1000 moves, Memory: O(N) where N is the number of cards in the game 
#include <bits/stdc++.h>
using namespace std;

deque<char> jane_down, jane_up, john_down, john_up;
int T;
int main(){
    cin >> T;
    for(int tc = 0; tc< T; tc++){
        // Parse Input
        string temp;

        cin >> temp;
        for (auto c: temp){
            jane_down.push_back(c);
        }
        cin >> temp;
        for (auto c: temp){
            john_down.push_back(c);
        }

        // Perform Simuation
        bool finished = false;
        for (int move=1; move<= 1000; move++){
            jane_up.push_front(jane_down.front());
            jane_down.pop_front();
            john_up.push_front(john_down.front());
            john_down.pop_front();

            if (john_up.front() == jane_up.front()){
                bool jane_winner = !(random()/141%2);

                if (jane_winner){
                    while(!john_up.empty()){
                        jane_up.push_front(john_up.back());
                        john_up.pop_back();
                    }

                    cout << "Snap! for Jane: ";
                    for (auto i:jane_up) cout << i;
                    cout << endl;
                }
                else{
                    while(!jane_up.empty()){
                        john_up.push_front(jane_up.back());
                        jane_up.pop_back();
                    }
                    
                    cout << "Snap! for John: ";
                    for (auto i:john_up) cout << i;
                    cout << endl;
                }

            }

            if (jane_down.empty() && jane_up.empty()){
                cout << "John wins." << endl;
                finished = true;
                break;
            }
            if (john_down.empty() && john_up.empty()){
                cout << "Jane wins." << endl;
                finished = true;
                break;
            }
            
            if(jane_down.empty()){
                while(!jane_up.empty()){
                    jane_down.push_front(jane_up.front());
                    jane_up.pop_front();
                }
            }
            if(john_down.empty()){
                while(!john_up.empty()){
                    john_down.push_front(john_up.front());
                    john_up.pop_front();
                }
            }

        }

        if (!finished){
            cout << "Keeps going and going ..." << endl;
        }

        if (tc != T-1)
            cout << endl;

        // Clean up
        jane_down.clear();
        jane_up.clear();
        john_down.clear();
        john_up.clear();

    }

    return 0;
}