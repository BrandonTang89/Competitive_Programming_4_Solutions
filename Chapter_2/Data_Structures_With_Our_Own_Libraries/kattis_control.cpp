/*  Kattis - control
Time: O(N + M log M), Mem: O(M)
    assuming UFDS operations are O(1)
    worst case scenario is all ingredients in first recipie: M log M for the set.find operations

This problem clearly demands the use of the Union-Find Disjoint Sets data structure
using it smartly results in a relatively easy solve

Debugging:
    note that we can't just store the ingredients in the set, we should store the representative element of the set with the ingredient
    ie store ingredients.findSet(ing) rather than ing
*/
#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

class UnionFind{
    private:
        vi p, rank, setSize;
        int numSets;
    public:
        UnionFind(int N){
            p.assign(N, 0); for (int i=0;i<N;i++)p[i]=i;
            rank.assign(N,0);
            setSize.assign(N,1);
            numSets=N;
        }

        int findSet(int i){return (p[i]==i) ? i : (p[i] = findSet(p[i]));}
        bool isSameSet(int i, int j){return findSet(i) == findSet(j);}
        int numDisjointSets(){return numSets;}
        int sizeOfSet(int i){return setSize[findSet(i)];}

        void unionSet(int i,int j){
            if (isSameSet(i,j))return;
            int x = findSet(i), y=findSet(j);
            if (rank[x] > rank[y])swap(x,y);
            p[x] = y;
            if (rank[x] == rank[y])++rank[y];
            setSize[y] += setSize[x];
            --numSets;
        }
};

int n, m, ing;
UnionFind ingredients(500009);

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    int ans = 0;
    for (int r=0; r<n; r++){
        set<int> s;
        cin >> m;
        int sum_ings=0;
        for (int i=0;i<m;i++){
            cin >> ing;
            if (s.find(ingredients.findSet(ing)) == s.end()){ //if pot containing ing hasnt been used before
                sum_ings+=ingredients.sizeOfSet(ing);
                s.insert(ingredients.findSet(ing));
            }
        }

        //printf("r=%d, m=%d, sum_ings=%d\n", r, m, sum_ings);
        if (sum_ings == m){ //possible to concoct
            int base_set = *s.begin();
            for (auto i:s){
                ingredients.unionSet(base_set, i);
            }
            ans++;
        }
    }
    cout << ans << endl;


    return 0;
}