/* Kattis - ladice
On first read, the question sounds pretty hard.. but with some observations we can solve it with somewhat little code
(that we write ourselves)

Observation 1:
    We can model the lockers as a graph with edges between a,b for all items in the lockers.
    If we choose to add a new item into a connected subset of the lockers, as long as there is an empty locker in the 
    connected subset, we are able to move the items around to accomodate the new item... Thus the actual position of the
    items in the subset of lockers is not important, rather we only need to care about the number of lockers 
    in the connected subset and the number of empty lockers.

Idea 1:
    we can represent the lockers as elements in a UFDS structure. Whenever a item with a=i and b=j is processed,
    we join the sets of i and j. this will represent the fact that if we later on need to put a new item in i, the old item
    can move over to j.

    For each set, we can keep a count of how many empty lockers are present. Initially, all the lockers are in their
    individual sets with setEmpty[i] = 1 (ie 1 empty locker).

    when processing a new element with (a,b), if we choose to put it into set a, we reduce the number of empty lockers 
    of set a by 1 and then join set a and b. Similar thing if we choose to put it into set b

Time: O(1) per operation, Mem: O(n)
*/
#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

class UnionFind {                                // OOP style
private:
  vi p, rank, setSize;                           // vi p is the key part
  vi setEmpty;
  int numSets;
public:
  UnionFind(int N) {
    p.assign(N, 0); for (int i = 0; i < N; ++i) p[i] = i;
    rank.assign(N, 0);                           // optional speedup
    setSize.assign(N, 1);                        // optional feature
    numSets = N;                                 // optional feature
    setEmpty.assign(N, 1);
  }

  int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
  bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }

  int numDisjointSets() { return numSets; }      // optional
  int sizeOfSet(int i) { return setSize[findSet(i)]; } // optional
  int numEmptyOfSet(int i){return setEmpty[findSet(i)];}

  void unionSet(int i, int j) {
    if (isSameSet(i, j)) return;                 // i and j are in same set
    int x = findSet(i), y = findSet(j);          // find both rep items
    if (rank[x] > rank[y]) swap(x, y);           // keep x 'shorter' than y
    p[x] = y;                                    // set x under y
    if (rank[x] == rank[y]) ++rank[y];           // optional speedup
    setSize[y] += setSize[x];                    // combine set sizes at y
    --numSets;                                   // a union reduces numSets
    setEmpty[y] += setEmpty[x];
  }

  void fillSet(int i){
      setEmpty[findSet(i)]--;
  }
};

int n, l, a, b;
int main(){
    cin >> n >> l;
    UnionFind UF(l);
    for (int item=0; item<n; item++){
        for (int i=0;i<l;i++){
            int j=0;
            //printf("i: %d, findset(i): %d, setEmpty: %d\n",i, UF.findSet(i), UF.numEmptyOfSet(i));
        }
        cin >> a >> b;
        a--; b--;
        bool cannot_fit = false;
        if (UF.sizeOfSet(a) == 1){
            UF.fillSet(a);
            UF.unionSet(a, b);
        }
        else if (UF.sizeOfSet(b) == 1){
            UF.fillSet(b);
            UF.unionSet(a, b);
        }
        else if (UF.numEmptyOfSet(a) > 0){
            UF.fillSet(a);
            UF.unionSet(a, b);
        }
        else if (UF.numEmptyOfSet(b) > 0){
            UF.fillSet(b);
            UF.unionSet(a, b);
        }
        else{
            cannot_fit = true;
        }
        if (cannot_fit){
            cout << "SMECE\n";
        }
        else cout << "LADICA\n";

        
    }


    return 0;
}