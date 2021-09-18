/* UVa 11340 Newspaper
   DS Question that I used map to solve
   Needs to use the cin/cout speed up techniques as well as formatting for 2dp output
   Time: O( N * (M*J*log k)) where N is nunber of test cases, M is the number of lines, J is the number of chars per line (ie log k per char)
   Mem: O(K) for the map*/

#include <bits/stdc++.h>
using namespace std;

map<char, int> m;
int N, k, n;
char char_key;
int int_value;

int main(){
    //Note the following important and infrequently used statements
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(2) << fixed;

    cin >> N;
    for (int t=0; t<N; t++){
        cin >> k;
        for (int i=0; i<k; i++){
            cin >> char_key >> int_value;
            m[char_key] = int_value;
        }


        int no_lines; //number of lines
        string line;
        long long ans = 0;

        cin >> no_lines; cin.ignore();
        for (int l=0; l<no_lines; l++){
            getline(cin, line);
            for (auto c: line){
                if (m.count(c) == 1){
                    ans += m[c];
                }
            }
        }

        //cout << ans << endl;
        double final = (double) ans/ (double) 100;
        cout << final << "$" << endl;

        m.clear();
    }




    return 0;
}