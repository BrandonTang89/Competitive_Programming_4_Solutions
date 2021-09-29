/* Kattis - Calculatingdartscores
A "fun" problem that is solvable with just 6 for loops and abit of adhoc code
Note the use of return 0; in the loop to avoid having other ancilliary code to break out of the 6 loops...

Time: O(1), Mem: O(1)
*/
#include <bits/stdc++.h>
using namespace std;

int n;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n; 
    
    //n = a*b + c*d + e*f
    string words[3] = {"single", "double", "triple"};
    for (int a=1; a<=3;a++){
        for (int b=1; b<= 20; b++){
            for (int c=0; c<=3;c++){
                for (int d=1; d<= 20; d++){
                    for (int e=0; e<=3;e++){
                        for (int f=1; f<= 20; f++){
                            if (n == a*b + c*d + e*f){
                                cout << words[a-1] << " " << b << endl;
                                if (c != 0)
                                cout << words[c-1] << " " << d << endl;
                                if (e != 0)
                                cout << words[e-1] << " " << f << endl;

                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }

    cout << "impossible" << endl;

    return 0;
}