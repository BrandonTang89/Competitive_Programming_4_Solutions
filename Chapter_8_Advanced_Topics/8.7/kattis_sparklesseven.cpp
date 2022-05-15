/**Kattis - sparklesseven
 * Abit of a vague clue for this problem. Firstly I believe that it should be decently clear that we need
 * to do a state space search, and that we should use bitmask to represent states. The real question was how
 * to determine the transitions / adjacent states. I had to do it in a way to minimise reptitions. I don't
 * know if the way I did it was really the best or what, but it works and I think is decently efficient.
 * At least it doesn't waste time in filtering whether a specific person can do a specific task because
 * we use the LSOne method to loop through the people.
 * 
 * Time: O(2^7 + 2^7), Space O(2^7);
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define LSOne(S) (S & (-S))
vector<int> people;
unordered_set<int> adjlist(int mask){
    unordered_set<int> ans;
    
    for (int p0=(1<<7)|(mask&people[0]); p0; p0=p0^(LSOne(p0))){
        int b0 = LSOne(p0);
        for (int p1=(1<<7)|(mask&people[1]&(~b0)); p1; p1=p1^(LSOne(p1))){
            int b1 = LSOne(p1);
            for (int p2=(1<<7)|(mask&people[2]&(~b0&~b1)); p2; p2=p2^(LSOne(p2))){
                int b2 = LSOne(p2);
                for (int p3=(1<<7)|(mask&people[3]&(~b0&~b1&~b2)); p3; p3=p3^(LSOne(p3))){
                    int b3 = LSOne(p3);
                    for (int p4=(1<<7)|(mask&people[4]&(~b0&~b1&~b2&~b3)); p4; p4=p4^(LSOne(p4))){
                        int b4 = LSOne(p4);
                        for (int p5=(1<<7)|(mask&people[5]&(~b0&~b1&~b2&~b3&~b4)); p5; p5=p5^(LSOne(p5))){
                            int b5 = LSOne(p5);
                            for (int p6=(1<<7)|(mask&people[6]&(~b0&~b1&~b2&~b3&~b4&~b5)); p6; p6=p6^(LSOne(p6))){
                                int b6 = LSOne(p6);
                                ans.insert((b0|b1|b2|b3|b4|b5|b6) & ((1 << 7) -1));

                            }
                        }
                    }
                }
            }
        }
    }
    return ans;
}
vector<int> gettransition(int u, int v){
    int change = u^v;
    // cout << "Change "<< change << endl;
    for (int p0=(1<<7)|(u&people[0]); p0; p0=p0^(LSOne(p0))){
        int b0 = LSOne(p0);
        for (int p1=(1<<7)|(u&people[1]&(~b0)); p1; p1=p1^(LSOne(p1))){
            int b1 = LSOne(p1);
            for (int p2=(1<<7)|(u&people[2]&(~b0&~b1)); p2; p2=p2^(LSOne(p2))){
                int b2 = LSOne(p2);
                for (int p3=(1<<7)|(u&people[3]&(~b0&~b1&~b2)); p3; p3=p3^(LSOne(p3))){
                    int b3 = LSOne(p3);
                    for (int p4=(1<<7)|(u&people[4]&(~b0&~b1&~b2&~b3)); p4; p4=p4^(LSOne(p4))){
                        int b4 = LSOne(p4);
                        for (int p5=(1<<7)|(u&people[5]&(~b0&~b1&~b2&~b3&~b4)); p5; p5=p5^(LSOne(p5))){
                            int b5 = LSOne(p5);
                            for (int p6=(1<<7)|(u&people[6]&(~b0&~b1&~b2&~b3&~b4&~b5)); p6; p6=p6^(LSOne(p6))){
                                int b6 = LSOne(p6);
                                if (change == ((b0|b1|b2|b3|b4|b5|b6) & ((1 << 7) -1)))
                                    return {{b0, b1, b2, b3, b4, b5, b6}};
                            }
                        }
                    }
                }
            }
        }
    }

    return {-1};
}

string characters[7] = {
    "Twilight Sparkle", 
    "Applejack", 
    "Rarity", 
    "Pinkie Pie", 
    "Fluttershy", 
    "Rainbow Dash",
    "Spike"
};

queue<int> q;
int dist[1<<8], parent[1<<8];
int main(){
    int k;
    people.assign(7, 0);
    for (int i=0; i<7; i++){
        for (int j=0; j<7; j++){
            cin >> k;
            people[i] |= (k << j);
        }
    }
    memset(dist, -1, sizeof(dist));
    q.push((1 << 7)-1);
    dist[(1 << 7)-1] = 0;
    parent[(1 << 7)-1] = -1;

    while (!q.empty()){
        int u = q.front();
        // cout << "u: " << u << endl;
        q.pop();

        if (u == 0)break;
        for (auto m : adjlist(u)){
            // cout << "m: " << m << endl;
            int v = u ^ m;
            if (dist[v] == -1){
                dist[v] = dist[u] + 1;
                parent[v] = u;
                q.push(v);
            }
        }
    }


    if (dist[0] == -1){
        cout << "IMPOSSIBLE" << endl;
    }
    else{
        cout << dist[0] << endl;
        int cur = 0;
        while (cur != (1 << 7)-1){
            int next = parent[cur];
            // cout << "cur "<< cur << " next " << next << endl;
            
            vector<int> transition = gettransition(next, cur);
            int counter = 0;
            for (int i=0; i<7; i++){
                transition[i] = __builtin_ctz(transition[i]);
                if (transition[i] != 7){
                    counter++;
                }
            }
            cout << counter << endl;
            for (int i=0; i<7; i++){
                if (transition[i] != 7){
                    cout << characters[i] << " " << transition[i]+1 << endl;
                }
            }
            cur = next;
        }
    }

    return 0;
}