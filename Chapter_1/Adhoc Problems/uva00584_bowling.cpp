// UVa 584 Bowling
// Extremely annoying, lots of edge cases to consider, but not that hard algorithm-wise. Really read carefully and debug properly
// Note the quality of my code is quite shit, a lot of things can be done better to improve readability
// Time: O(1), Mem: O(1)
#include <bits/stdc++.h>
using namespace std;

int main(){
    string raw_input;
    vector<char> frame_scores;
    vector<int> numeric_scores;
    while(true){
        getline(cin, raw_input);
        if (raw_input == "Game Over")break;
        for (auto c: raw_input){
            if (c != ' ' && c != '\n'){
                //if (c == 'X') frame_scores.push_back(0);
                frame_scores.push_back(c);
            }
        }

        for (int i=0; i<frame_scores.size(); i++){
            if (frame_scores[i] == 'X'){
                numeric_scores.push_back(10);
            }
            else if(frame_scores[i] == '/'){
                numeric_scores.push_back(10 - numeric_scores[i-1]);
            }
            else{
                numeric_scores.push_back(frame_scores[i] - '0');
            }

            // cout << numeric_scores[i] << " ";
        }

        // cout << endl;
        

        int score = 0;
        float frame_number = 1;
        for (int i=0; i<frame_scores.size(); i++){
            // cout << frame_number << " ";
            if (frame_number >= 11){
                break;
            }
            if (frame_number > 10 && frame_scores[i-1] == 'X')break;

            if (frame_scores[i] == 'X')frame_number += 1;
            else frame_number += 0.5;

            score += numeric_scores[i];

            if (frame_number)
            if (frame_scores[i] == 'X'){
                if (frame_scores.size() - i > 2){
                    score += numeric_scores[i+1] + numeric_scores[i+2];
                }
                else if (frame_scores.size() - i > 1){
                    score += numeric_scores[i+1];
                }
            }

            if (frame_scores[i] == '/' && i < frame_scores.size() - 1){
                score += numeric_scores[i+1];
            }
            // cout << score << " ";
        }

        cout << score << endl;

        numeric_scores.clear();
        frame_scores.clear();


    }

    

    return 0;
}