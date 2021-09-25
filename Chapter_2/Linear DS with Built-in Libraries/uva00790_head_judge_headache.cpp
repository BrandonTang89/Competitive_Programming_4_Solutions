// UVA 790 Head Judge Headache - Not accepted
// Badly set question with unclear input and output formatting :(
#include <bits/stdc++.h>
using namespace std;

pair<int,bool> problem_log[27][7]; // problem_log[team_number][problem_number] == (number_of_solutions, solved_previously?)

int problem_char_to_int(char n){
    return n - 'A';
}

struct team {
    int no_problems_solved;
    int total_time;
    int team_number;
};

team teams[27];

bool sort_teams(team a, team b){
    if (a.no_problems_solved > b.no_problems_solved)return true;
    if (b.no_problems_solved > a.no_problems_solved)return false;

    if (a.total_time < b.total_time)return true;
    if (b.total_time < a.total_time)return false;

    return (a.team_number < b.team_number);
}

int main(){

    int team_number, hour, minute, problem_number, time_thus_far;
    char problem_letter, accepted_char;
    string time_string, input_string;
    bool accepted;

    int TC;
    cin >> TC;
    string temp;
    getline(cin, temp); // flush the empty line
    getline(cin, temp); // flush the empty line

    for (int k=0;k<TC;k++){
        int max_team = 0;

        for (int i=1; i <= 26; i++){
            teams[i].no_problems_solved = 0;
            teams[i].total_time = 0;
            teams[i].team_number = i;

            //cout << "TEAM NUNBER  " << teams[i].team_number << endl;

            
            for(int j=0;j<7;j++){
                problem_log[i][j] = make_pair(0,false);
            }
        }

        /*
        for (int i=1;i<=26;i++)
        cout << "TEST " << teams[i].team_number << endl;*/
        

        while (true){

            getline(cin, input_string);
            //cout << "input string" << input_string << "--" << endl;
            if (input_string == "")break;

            istringstream ss(input_string);
            ss >> team_number >> problem_letter >> time_string >> accepted_char;
            // cout << "team number " << team_number << endl;

            // 1 A 0:50 N
            max_team = max(max_team, team_number);

            hour = time_string[0] - '0';
            minute = (time_string[2] - '0')*10 + (time_string[3] - '0');
            time_thus_far = hour*60 + minute;
            //cout << "time thus far " << hour << endl; 

            if (accepted_char == 'Y')accepted = true;
            else accepted = false;
            problem_number = problem_char_to_int(problem_letter);

            if (problem_log[team_number][problem_number].second)continue; // ignore if problem solved before

            if (!accepted){
                problem_log[team_number][problem_number].first++; // Add to failure count
            }
            else{
                problem_log[team_number][problem_number].second = true;
                teams[team_number].no_problems_solved++;
                teams[team_number].total_time += 20*problem_log[team_number][problem_number].first + time_thus_far;
            }

        }

        //cout << "TEST " << teams[2].team_number << endl;
        sort(teams+1, teams+1+max_team, sort_teams);


        cout << "RANK TEAM PRO/SOLVED TIME" << endl;

        for (int i=1; i<= max_team; i++){
            if (teams[i].no_problems_solved > 0)
            cout << i << " " << teams[i].team_number << " " << teams[i].no_problems_solved << " " << teams[i].total_time << endl;

            else
            cout << i << " " << teams[i].team_number << endl;
        }
        cout << endl;


    }
    



    return 0;
}