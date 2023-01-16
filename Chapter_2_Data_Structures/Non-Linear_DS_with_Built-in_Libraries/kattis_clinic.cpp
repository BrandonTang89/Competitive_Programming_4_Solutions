/**Kattis - clinic
 * My first question in a while. We maintain a minimum heap of tuples (weight, name) where weight =
 * -severity + t*k. Observe that this has the effect that the question requires such that a new
 * patient has more weight than a patient who has been waiting for a long time. We also maintain a
 * hash table of names of people who have been said to leave and we just check that before we send
 * the next patient to the doctor.
 * 
 * Time: O(n log n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

ll n, k, t;
string name;
unordered_set<string> s;  // names of people who have left
priority_queue<tuple<ll, string>, vector<tuple<ll, string>>, greater<tuple<ll, string>>>
    pq;  // our priority queue

int main()
{
    cin >> n >> k;
    for (int q = 0; q < n; q++) {
        int qtype;
        cin >> qtype >> t;

        if (qtype == 1) {
            cin >> name;
            ll severity;
            cin >> severity;
            pq.emplace(-severity + t * k, name);
        }
        else if (qtype == 2) {
            while (true) {
                if (pq.empty()) {
                    cout << "doctor takes a break" << endl;
                    break;
                }
                else {
                    auto [w, name] = pq.top();
                    pq.pop();
                    if (s.find(name) == s.end()) {
                        cout << name << endl;
                        break;
                    }
                    else {
                        s.erase(name);
                    }
                }
            }
        }
        else {
            cin >> name;
            s.insert(name);
        }
    }

    return 0;
}