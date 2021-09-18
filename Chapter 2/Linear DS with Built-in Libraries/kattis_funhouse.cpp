// Kattis funhouse
// Simulation of a light beam reflecting off 45 degree mirrors in a 2d room
// Time: O(wlt), where t is the number of testcases. 
/*

Could possibly redo the code to use an adjlist where each non-empty cell is broken down into 4 graph nodes (r,c,dir) and store into adjlist
before doing a depth first search from the starting cell to improve efficiency for super sparse rooms

*/
#include <bits/stdc++.h>
using namespace std;

int w, l;
char room[21][21];
int s_r, s_c; //start row and column

int dx[4] ={1,-1,0,0};
int dy[4] = {0,0,1,-1};

int dir;

int change_dir(int init_dir, char mirror){
    if (init_dir == 0){
        if (mirror == '\\')return 2;
        else return 3;
    }
    if (init_dir == 1){
        if (mirror == '\\')return 3;
        else return 2;
    }
    if(init_dir == 2){
        if(mirror == '\\')return 0;
        else return 1;
    }
    if(init_dir == 3){
        if(mirror == '\\')return 1;
        else return 0;
    }
    else return -1;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for (int counter=1;;counter++){
        cin >> w >> l;
        if (w == 0)break;

        for (int r=0; r<l; r++){
            for (int c=0; c<w;c++){
                cin >> room[r][c];
                if (room[r][c] == '*'){
                    s_r = r;
                    s_c = c; 
                }
            }
        }

        // set initial direction
        if (s_c == 0)dir = 0;
        else if (s_c == l-1)dir = 1;
        else if (s_r == 0)dir = 2;
        else dir = 3; 

        int r,c;
        for (r=s_r+dy[dir], c=s_c+dx[dir]; room[r][c] != 'x'; r+=dy[dir], c+=dx[dir]){
            //cout << "r: " << r << " c: " << c << endl;
            if (room[r][c] == '\\' || room[r][c] == '/'){
                dir = change_dir(dir, room[r][c]);
            }
        }

        room[r][c] = '&';
        cout << "HOUSE " << counter << endl;


        for (int r=0; r<l; r++){
            for (int c=0; c<w;c++){
                cout << room[r][c];
            }
            cout << endl;
        }

    }

    return 0;
}