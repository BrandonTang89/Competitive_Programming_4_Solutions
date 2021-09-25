/* 
Kattis - moviecollection
Time: O(T * r log(m+r)), Mem: O(m+r)
While a O(mr) solution is obvious, the O(r log (m+r)) solution is relatively difficult to find

The code below works by storing the stack state as 
    a fenwick tree board where 
        ft[0] is the bottom of the stack
        ft[i] == 0 if the space is empty and 
        ft[i] == 1 if there exist a disk
    along with a pos arr where
        pos[i] == position in ft where disk i is located

To find how many disks are below disk i, we take the range sum from ft[1] to ft[pos[i]]
    for each disk present below i, there is a corresponding 1 representing the disk in ft[1]
    number of disks above is simply m - number of disks below

To move disk i to the top
    remove disk i by setting ft[pos[i]] = 0
    place disk i above all other disks
        to save time from having to find out the max pos of all other disk, we put the disk at m+r_num+1
        this is because for each request before r_num, we at most increase the board usage by 1 space
        this is done by setting ft[m+r_num+1] = 1, pos[i] = m+r_num+1

this logic is analagous to simulating the stack working without gravity, 
where empty holes are left where the disks were, thus the stack always grows in height
*/


#include <bits/stdc++.h>
using namespace std;

#define LSOne(S) ((S) & -(S))

typedef long long ll;
typedef vector<ll> vll;
typedef vector<int> vi;

class FenwickTree{
    private:
        vll ft;
    public:
        void build(const vll &f){
            int m= (int)f.size() -1;
            ft.assign(m+1, 0);
            for (int i=1;i<=m;i++){
                ft[i] += f[i];
                if (i+LSOne(i) <= m)
                    ft[i+LSOne(i)] += ft[i];
            }
        }

        FenwickTree(const vll &f){build(f); }

        ll rsq(int j){
            ll sum =0;
            for (; j; j -= LSOne(j))
                sum += ft[j];
            return sum;
        }

        ll rsq(int i, int j){return rsq(j) - rsq(i-1);}

        void update(int i, ll v){
            for (int j=i; j<(int)ft.size();j+=LSOne(j))
                ft[j] += v;
        }
};


int T, m, temp, r;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> T;
    for (int tc=0;tc<T; tc++){
        cin >> m >> r;

        vll board;
        board.push_back(0); //ft[0] == 0; 
        for (int i=0;i<m; i++)board.push_back(1);
        for (int i=0;i<r+1;i++)board.push_back(0);

        FenwickTree ft(board);
        vi pos; pos.push_back(0); //we shall start from 1 index
        for (int i=1; i<= m; i++){
            pos.push_back(m-i+1);
        }

        for (int r_no=0; r_no<r; r_no++){
            cin >> temp; //temp stores the index of the disk to move
            ll no_below = ft.rsq(pos[temp]);
            ll no_above = m - no_below;

            ft.update(pos[temp], -1); // disk old position on board;
            pos[temp] = m+r_no+1; // places the disk at above any other previously accessed position
            ft.update(pos[temp], 1); //place disk at new position above any other previously used position

            cout << no_above;
            if (r_no != r-1)cout << " ";
            else cout << endl;
        }

    }

    return 0;
}