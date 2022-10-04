/**Kattis - dream
 * Quite a tedious question, or maybe I'm just rusty. The basic idea is first to have a map to map
 * the event names to indices. Then, we should keep track of the order of the dreams. There are
 * several different cases that can result in a plot error, the most major is when we need to remove
 * an event that happens before an event that we cannot remove... The rest are honestly edge cases
 * that you need to slowly figure out.
 *
 * Time: O(n), Space: O(n)
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

int n;
vector<int> s;                  // s[position on stack] = event index
vector<int> pos;                // pos[event index] = position on stack (0 indexed)
unordered_map<string, int> mp;  // mp[event string] = event index
vector<string> v;               // v[event index] = event string

int main() {
    fast_cin();
    cin >> n;
    pos.assign(n, -1);
    for (int e = 0; e < n; e++) {
        char c;
        cin >> c;
        if (c == 'E') {
            string event;
            cin >> event;
            if (mp.find(event) == mp.end()) {
                mp[event] = v.size();
                v.push_back(event);
            }
            s.push_back(mp[event]);
            pos[mp[event]] = s.size() - 1;
        } else if (c == 'D') {
            int x;
            cin >> x;
            for (int i = 0; i < x; i++) {
                pos[s.back()] = -1;
                s.pop_back();
            }
        } else {
            int x;  // number of conditions
            cin >> x;
            bool ploterror = false;
            int stack_lte = s.size();
            int stack_gte = -1;
            for (int i = 0; i < x; i++) {
                string event;
                cin >> event;
                if (ploterror) continue;

                bool negate = false;
                if (event[0] == '!') {
                    negate = true;
                    event = event.substr(1);
                }

                if (negate == false) {  // event must happen
                    if (mp.find(event) == mp.end() || pos[mp[event]] == -1) {
                        ploterror = true;
                        continue;
                    }
                    int event_index = mp[event];
                    stack_gte = max(stack_gte, pos[event_index]);  // we must not cross this one

                } else {  // event must not happen
                    if (mp.find(event) == mp.end() || pos[mp[event]] == -1) {
                        continue;
                    }
                    stack_lte = min(stack_lte, pos[mp[event]]);  // we must cross this one
                }
            }

            if (ploterror) {
                cout << "Plot Error" << endl;
            } else if (stack_lte > stack_gte) {
                if ((int)s.size() == stack_lte) {
                    cout << "Yes" << endl;
                } else {
                    cout << s.size() - stack_lte << " Just A Dream" << endl;
                }
            } else {
                cout << "Plot Error" << endl;
            }
        }
    }

    return 0;
}