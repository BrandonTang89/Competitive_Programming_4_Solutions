/* Kattis - Abinitio
This is actually "easy" in concept but you need to be quite careful when implementing the queries

Observation 1:
    Obviously transposing / complementing G for every type 5/6 query results in O(V^2) time for those 2 queries...

    However, note that tranpose: t(G) and complement: c(G) are self-inverse, ie tt(G) = G and cc(G) = G
    Furthermore, t and c are commutative, ie tc(G) = ct(G).

    Thus we can use both of the above properties to derive the fact that we can use state variables "complement" 
    and "tranpose" to determine if G will be tranposed / complemented at the end, assuming all the queries are 
    relative to the original G.

    This results in 4 possible "variations" of G. Neutral, transpose, complement and complement transpose

    We can keep track of the 4 variants of G as separate graphs. 
    This will not MLE (4000*4000 * 4 bits << 1024 MB)
    Whenever we update G in queries 1-4, we can do a O(v) or better update on each of the 3 other variants as well.

    For query type 5/6, just apply the logical "not" to the transpose and complement state variables

    at the end, we just output from the correct selection of one of the 4 graphs.

Observation 2:
    After a 5/6 query, all subsequent queries are done relative to the new graph.
    e.g. if a query 6 is followed by 1, G is complemented and a new vertex is added but is unconnected.
        if we just add a new vertex to G, it would mean adding a fully connected vertex to G_c
        thus in reality, we need to add a fully connected vertex to G and an unconnected vertex to G_c
    
    Dealing with this is easy by noting that if we set a edge to w subset {0,1} in G, it is set to !w in G_c and G_ct
    if the edge is from u->v in G, it is from v->u in G_t and G_ct. Thus if the change is done relative to the G_c,
    we simply set w = !w and apply the change normally relative to G. Similar logic can be used for queries relative
    to G_c and G_ct

Debugging:
    Remember to
    - use long long for the muliplier and answer variables.
    - use mod frequently
    - let the size of ur adjmats be 4000 == 2000 (v) + 2000 (q)

Time: O(qv), Mem: O((v+q)^2)
*/ 
#include <bits/stdc++.h>
using namespace std;

int v, e, q, op, u, n;
bool w;
long long mod = 1e9+7;
bool G[4001][4001], G_t[4001][4001], G_c[4001][4001], G_ct[4001][4001];
bool tranpose=false, complement=false;
// Assign w to G(u,v) 
void assign(int u, int v, bool w){
    G[u][v] = w;
    G_t[v][u] = w;
    G_c[u][v] = !w;
    G_ct[v][u] = !w;
}

void print_G(bool Ga[4001][4001]){
    vector<int> adjlist[4001];
    
    for (int u=0;u<n;u++){
        long long ans = 0, multiplier = 1;
        for (int v=0;v<n;v++){
            //printf("%d", Ga[u][v]);
            if (u == v)continue;
            
            if (Ga[u][v]){
                adjlist[u].emplace_back(v);
                ans += multiplier*v;
                ans %= mod;
                multiplier*=7;
                multiplier%=mod;
            }
            
        }//printf("\n");

        printf("%lld %lld\n", (long long) adjlist[u].size(), ans);
    }
}
int main(){
    scanf("%d %d %d", &n, &e, &q);
    for (int i=0;i<4000;i++){
        for (int j=0;j<4000;j++){
            G_c[i][j] = 1;
            G_ct[i][j] = 1;
        }
    }

    for (int i=0;i<e;i++){
        scanf("%d %d", &u, &v);
        assign(u,v,1);
        
    }

    for (int t=0; t<q;t++){
        scanf("%d",&op);
        if (op == 1){
            n++;
            w = 0;
            if (complement){
                w = !w;
            }
            for (int v=0;v<n-1;v++){
                assign(n-1,v,w);
                assign(v,n-1,w);
            }
        }
        else if (op == 2){
            scanf("%d %d", &u, &v);
            w = 1;
            if (complement){
                w = !w;
            }
            if (tranpose){
                swap(u,v);
            }
            assign(u,v,w);
        }
        else if (op == 3){
            scanf("%d", &u);
            w = 0;
            if (complement){
                w = !w;
            }
            for (int v=0;v<n;v++){
                if (u == v)continue;
                assign(u, v, w);
                assign(v, u, w);
            }
        }
        else if (op == 4){
            scanf("%d %d", &u, &v);
            w = 0;
            if (complement){
                w = !w;
            }
            if (tranpose){
                swap(u,v);
            }
            assign(u,v,w);
        }
        else if (op == 5){
            tranpose = !tranpose;
        }
        else if (op == 6){
            complement = !complement;
        }

        //print adjmat
        /*
        printf("%d\n", n);
        if (complement && tranpose){
            print_G(G_ct);
        }
        else if (complement){
            print_G(G_c);
        }
        else if (tranpose){
            print_G(G_t);
        }
        else{
            print_G(G);
        }*/
        
    }

    //print adjmat hash
    printf("%d\n", n);
    if (complement && tranpose){
        print_G(G_ct);
    }
    else if (complement){
        print_G(G_c);
    }
    else if (tranpose){
        
        print_G(G_t);
    }
    else{
        
        print_G(G);
    }
}