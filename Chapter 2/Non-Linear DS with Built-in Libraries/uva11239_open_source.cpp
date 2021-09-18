// UVa 11239 Open Source
// DS Question Map/set
// Time: O(nlog(n))
// Mem: O(n*no_projects)
// Constraints: n <= 10000, no_projects<1000
// Note: Much easier (and faster) solution by just having a map[student] = project and updating it throughout the input and doing processing after
// This provides O(n) for initial processing, O(n) for updating map[project] = no_students, followed by O(no_projects log no_projects) to sort
#include <bits/stdc++.h>
using namespace std;

map<string, set<string>> project_students; // project_students[PROJECT] = {students}
map<string, string> student_projects; // student_projects[STUDENT] = project

string temp, project, cur_proj, input_op;
int main(){
    while(true){
        getline(cin, input_op);

        //cout << input_op << endl;

        if (isupper(input_op[0])){
            cur_proj = input_op;
            project_students[cur_proj].insert("dummy");
            project_students[cur_proj].erase("dummy");
            continue;
        }
        if(input_op == "0"){
            break;
        }
        if(input_op == "1"){
            vector<pair<int, string>> project_vector;
            for (auto i:project_students){
                project_vector.push_back(make_pair(-1 * static_cast<int>(i.second.size()), i.first));
            }
            sort(project_vector.begin(), project_vector.end());

            for (auto i: project_vector){
                cout << i.second << " " << -i.first << endl;
            }

            student_projects.clear();
            project_students.clear();
            continue;
        }

        //input op is new student
        string student_name = input_op;

        if (student_projects.find(student_name) == student_projects.end() || student_projects[student_name] == cur_proj){
            project_students[cur_proj].insert(student_name);
            student_projects[student_name] = cur_proj;
        }
        else{ // student over committed, remove from prior projects 
            student_projects[student_name] = "-1";
            for (map<string, set<string>>::iterator it=project_students.begin(); it != project_students.end(); it++){
                (*it).second.erase(student_name);
            }
        }

    }    
}