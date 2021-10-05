/* Kattis - almostunionfind

Observation 0:
  the main issue with moving i to the set containing j directly is that other elements with parent i will get screwed over
  unless we change their parent to another element which could take up to O(n) time
  
Idea 1:
  Instead of doing that, we can actually make a new element in its own set with the value of i and
  reduce the size of the set of i by 1 and its sum by i and leave the orignal element in its set 
  (but with 0 size and value)

  This would be equivalent to a "lazy" removal of i from its original set. After which is just simply union the new element
  to the set of j

  To accomplish this, we simply need to keep track of which element represents i for each i from 0 to N-1. This is done with
  m[i] and is updated whenever a move is called on (i, j)

  All these results in an O(1) time to implement the move operation assuming that all other UFDS operations are O(1)

Debugging:
  The sum of sets overflows an integer, thus long long is used
  Note that there are actually multiple test cases... 

  Take note of whether to use (p,q) or (m[p], m[q]) for each UFDS operation

Time per operation: Essentially O(1), Mem: O(n)
*/ 

#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef long long ll;
typedef vector<ll> vll;

class UnionFind {                                // OOP style
private:
  vi p, rank, setSize;                           // vi p is the key part
  vll vals, setSum;
  int counter;
  
public:
  vi m;
  UnionFind(int N) {
    p.assign(N, 0); for (int i = 0; i < N; ++i) p[i] = i;
    rank.assign(N, 0);                           // optional speedup
    setSize.assign(N, 1);                        // optional feature
    m.assign(N, 0);
    vals.assign(N, 0);
    setSum.assign(N, 0);
    for (int i=0;i<N;i++){
      m[i] = i;
      vals[i] = i+1;
      setSum[i] = vals[i];
    }
    counter = N;
  }


  int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
  bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }

  int sizeOfSet(int i) {
    return setSize[findSet(i)];
    } // optional
  
  ll sumOfSet(int i){
    return setSum[findSet(i)];
  }

  void unionSet(int i, int j) {
    if (isSameSet(i, j)) return;                 // i and j are in same set
    int x = findSet(i), y = findSet(j);          // find both rep items
    if (rank[x] > rank[y]) swap(x, y);           // keep x 'shorter' than y
    p[x] = y;                                    // set x under y
    if (rank[x] == rank[y]) ++rank[y];           // optional speedup
    setSize[y] += setSize[x];                    // combine set sizes at y
    setSum[y] += setSum[x];
  }

  // the only method that i and j should be un preprocessed
  void moveSet(int i, int j){
    if (isSameSet(m[i],m[j]))return;
    // Make a new element counter in its own set
    p.push_back(counter);
    rank.push_back(0);                           // optional speedup
    setSize.push_back(1);                        // optional feature
    vals.push_back(vals[i]);
    setSum.push_back(vals[i]);

    // remove val from old set
    setSize[findSet(m[i])]--;
    setSum[findSet(m[i])] -= vals[i];

    m[i] = counter;
    counter++;

    unionSet(m[i], m[j]);
  }


};

int n, m, op, p, q;
int main() {
    
    while(scanf("%d %d", &n, &m) != EOF){
      UnionFind UF(n);
      for (int tc=0;tc<m;tc++){
          scanf("%d", &op);
          //printf("OP : %d tc: %d\n", op, tc);
          if (op == 1){
              // union
              scanf("%d %d", &p, &q);
              p--; q--;
              UF.unionSet(UF.m[p], UF.m[q]);
          }
          else if (op == 2){
              // Move
              scanf("%d %d", &p, &q);
              p--; q--;
              UF.moveSet(p, q);
          }
          else if (op == 3){
              scanf("%d", &p);
              p--;
              printf("%d %lld\n", UF.sizeOfSet(UF.m[p]), UF.sumOfSet(UF.m[p]));
          }
          
          for (int i=0;i<n;i++){
              int j =0;
              //printf("i: %d, m[i]: %d, findset(m[i]): %d, setSum: %d\n",i, UF.m[i],UF.findSet(UF.m[i]), UF.sumOfSet(UF.m[i]));
          }
      }
    }

}