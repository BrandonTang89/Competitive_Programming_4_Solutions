/**Kattis - guessthedatastructure
 * Straightforward. Just simulate each structure and constantly update if it can be each structure then print out the answer.
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

int main()
{
    int n;
    while (cin >> n) {
        bool canBeStack = true, canBeQueue = true, canBePQ = true;
        stack<int> st;
        queue<int> q;
        priority_queue<int> pq;

        for (int i = 0; i < n; i++) {
            int op, val;
            cin >> op >> val;
            if (op == 1) {
                st.push(val);
                q.push(val);
                pq.push(val);
            }
            else {
                if (st.empty() || st.top() != val)
                    canBeStack = false;
                if (q.empty() || q.front() != val)
                    canBeQueue = false;
                if (pq.empty() || pq.top() != val)
                    canBePQ = false;
                if (!st.empty())
                    st.pop();
                if (!q.empty())
                    q.pop();
                if (!pq.empty())
                    pq.pop();
            }
        }
        if (canBeStack && !canBeQueue && !canBePQ)
            cout << "stack" << endl;
        else if (!canBeStack && canBeQueue && !canBePQ)
            cout << "queue" << endl;
        else if (!canBeStack && !canBeQueue && canBePQ)
            cout << "priority queue" << endl;
        else if (!canBeStack && !canBeQueue && !canBePQ)
            cout << "impossible" << endl;
        else
            cout << "not sure" << endl;
    }

    return 0;
}