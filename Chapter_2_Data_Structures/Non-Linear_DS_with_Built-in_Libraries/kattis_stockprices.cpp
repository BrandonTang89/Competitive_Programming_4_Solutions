#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

priority_queue<pair<int,int> > bids; // price, quantity, max heap
priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>> > asks; // price, quantity, min heap
int stock_price = -1;

int num_tc, n;
string op, d;
int q, p;
int main(){
    fast_cin();
    cin >> num_tc;
    for (int tc=0;tc<num_tc;tc++){
        while (!bids.empty()) bids.pop();
        while (!asks.empty()) asks.pop();
        stock_price = -1;

        cin >> n; 
        for (int i=0;i<n;i++){
            cin >> op >> q >> d >> d >> p;
            if (op == "buy"){
                bids.push(make_pair(p, q));
            }
            else{
                asks.push({p, q});
            }

            while ((!(asks.empty() || bids.empty())) && asks.top().first <= bids.top().first){
                int ask_price = asks.top().first;
                int bid_price = bids.top().first;
                int ask_quantity = asks.top().second;
                int bid_quantity = bids.top().second;
                asks.pop();
                bids.pop();
                
                int q_transacted = min(ask_quantity, bid_quantity);
                stock_price = ask_price;
                if (q_transacted < ask_quantity){
                    asks.push({ask_price, ask_quantity - q_transacted});
                }
                if (q_transacted < bid_quantity){
                    bids.push({bid_price, bid_quantity - q_transacted});
                }
            }

            if (asks.empty()){
                cout << "- ";
            }
            else cout << asks.top().first << " ";
            if (bids.empty()){
                cout << "- ";
            }
            else cout << bids.top().first << " ";
            if (stock_price == -1){
                cout << "-\n";
            }
            else cout << stock_price << "\n";
        }
    }
    return 0;
}