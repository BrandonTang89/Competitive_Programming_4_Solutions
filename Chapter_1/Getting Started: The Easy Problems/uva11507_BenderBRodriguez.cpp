// UVa 11507 Bender B. Rodriguez Problem
// Easy question that involves simulation of a wire bending in 3d space
// Time: O(TC * n), Mem: O(1)
#include <bits/stdc++.h>
using namespace std;

map <string, string> opp; // opp[direction] == opposite_direction
string update_dir(string initial, string operation){ //updates the direction of the wire from initial via operation
    if (operation == "No"){
        return initial;
    }
    if (initial == "+x"){
        return operation;
    }
    if (initial == "-x"){
        return opp[operation];
    }

    if (initial == "+y"){
        if (operation == "+y") return "-x";
        if (operation == "-y") return "+x";
        if (operation == "+z" || operation == "-z") return "+y";
    }

    if (initial == "-y"){
        if (operation == "+y") return "+x";
        if (operation == "-y") return "-x";
        if (operation == "+z" || operation == "-z") return "-y";
    }

    if (initial == "+z"){
        if (operation == "+z") return "-x";
        if (operation == "-z") return "+x";
        if (operation == "+y" || operation == "-y") return "+z";
    }

    if (initial == "-z"){
        if (operation == "+z") return "+x";
        if (operation == "-z") return "-x";
        if (operation == "+y" || operation == "-y") return "-z";
    }

}

int main(){
    opp["+x"] = "-x";
    opp["-x"] = "+x";
    opp["+y"] = "-y";
    opp["-y"] = "+y";
    opp["+z"] = "-z";
    opp["-z"] = "+z";

    int l;
    while (true){
        cin >> l;
        if (l == 0)break;

        string state = "+x";
        string op;
        for (int i=0; i<l-1; i++){
            cin >> op;
            state = update_dir(state, op);
        }
        cout << state << endl;
    }
    return 0;
}