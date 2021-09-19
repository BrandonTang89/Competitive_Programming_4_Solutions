/* Kattis - Just for Sidekicks
A relatively straightforward dynamic RSQ question, using 6 PURQ fenwick trees for the 6 different types
these 6 trees are stored in a vector of FenwickTree objects

Time: O(q log n), Mem: O(n)
*/
#include <bits/stdc++.h>
using namespace std;

#define LSOne(S) ((S) & -(S))                    // the key operation

typedef long long ll;                            // for extra flexibility
typedef vector<ll> vll;
typedef vector<int> vi;

class FenwickTree {                              // index 0 is not used
private:
  vll ft;                                        // internal FT is an array
public:
  FenwickTree(int m) { ft.assign(m+1, 0); }      // create an empty FT

  void build(const vll &f) {
    int m = (int)f.size()-1;                     // note f[0] is always 0
    ft.assign(m+1, 0);
    for (int i = 1; i <= m; ++i) {               // O(m)
      ft[i] += f[i];                             // add this value
      if (i+LSOne(i) <= m)                       // i has parent
        ft[i+LSOne(i)] += ft[i];                 // add to that parent
    }
  }

  FenwickTree(const vll &f) { build(f); }        // create FT based on f

  FenwickTree(int m, const vi &s) {              // create FT based on s
    vll f(m+1, 0);
    for (int i = 0; i < (int)s.size(); ++i)      // do the conversion first
      ++f[s[i]];                                 // in O(n)
    build(f);                                    // in O(m)
  }

  ll rsq(int j) {                                // returns RSQ(1, j)
    ll sum = 0;
    for (; j; j -= LSOne(j))
      sum += ft[j];
    return sum;
  }

  ll rsq(int i, int j) { return rsq(j) - rsq(i-1); } // inc/exclusion

  // updates value of the i-th element by v (v can be +ve/inc or -ve/dec)
  void update(int i, ll v) {
    for (; i < (int)ft.size(); i += LSOne(i))
      ft[i] += v;
  }

  int select(ll k) {                             // O(log m)
    int p = 1;
    while (p*2 < (int)ft.size()) p *= 2;
    int i = 0;
    while (p) {
      if (k > ft[i+p]) {
        k -= ft[i+p];
        i += p;
      }
      p /= 2;
    }
    return i+1;
  }
};

int n,q;
int values[6]; //0  index
char char_arr[200009];
int int_arr[200009];
vector<FenwickTree> trees;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> q;

    for (int i=0;i<6;i++){
        cin >> values[i];
    }
    
    cin >> char_arr;

    for (int i=0;i<n; i++){ //1 index on the board
        int_arr[i+1] = char_arr[i] - '0' - 1;
    }

    /*
    cout << " --- int arr --- \n"; 
    for (int i=1;i<=n;i++){
        cout << int_arr[i] << " ";
    }
    cout << endl;*/

    for (int p=0; p<6;p++){ 
        vll temp_v; temp_v.push_back(0); // ft[0] == 0;
        for (int i=1;i<=n;i++){
            if(int_arr[i] == p)temp_v.push_back(1);
            else temp_v.push_back(0);
        }
        trees.push_back(FenwickTree(temp_v));
    }

    int op, arg1, arg2;
    for (int q_no=0; q_no<q; q_no++){
        cin >> op >> arg1 >> arg2;
        if (op == 1){
            arg2--; //gem types from 0 to 5
            trees[int_arr[arg1]].update(arg1, -1); //delete from ft of the type of initial gem
            /*
            for (int i=1;i<=n;i++){
                cout << trees[int_arr[arg1]].rsq(i,i)<< " ";
            }
            cout << endl;*/

            int_arr[arg1] = arg2;
            trees[int_arr[arg1]].update(arg1, 1);
        }
        else if (op == 2){
            arg1--;
            values[arg1] = arg2; 
        }
        else{
            ll ans=0;
            for (int p=0;p<6;p++){
                ans += trees[p].rsq(arg1, arg2) * values[p];
            }

            cout << ans << endl;
        }
        
    }

    return 0;

}