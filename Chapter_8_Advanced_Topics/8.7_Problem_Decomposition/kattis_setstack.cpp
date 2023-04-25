/**Kattis - setstack
 * Custom data structure. This is a rare question that requires object oriented programming. The key
 * observation is that we don't need to make deep copies of the sets since they cannot be modifed
 * after they have been inserted into other sets. As such, the dup operation can simply be a shallow
 * copy. The other key trick is to maintain hashes of sets as part of the class to allow for O(1)
 * comparisons. We use a similar hashing function to the rolling hash in string matching. To minimise
 * the probability of hash collisions, we use 2 such hashes in a hash pair. This hash is also used to
 * provide a total order for the sets, allowing us to store the children in sorted order!
 * 
 * Time: O(q^2), Space: O(q)
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

ll p = 131;
ll q = 673;
ll MOD = (1LL << 31) - 1;
vector<ll> pow_p, pow_q;
class se {
   public:
    int n;
    pair<ll, ll> h;
    vector<se *> children;
    se(vector<se *> c)
    {
        children = c;
        n = (int)children.size();
        ll h1 = 3;
        ll h2 = 7;
        sort(children.begin(), children.end(), [](se *a, se *b) {
            assert(a->h != b->h);
            return a->h < b->h;
        });
        for (int i = 0; i < n; i++) {
            h1 = (h1 + (ll)children[i]->h.first * pow_p[i]) % MOD;
            h2 = (h2 + (ll)children[i]->h.second * pow_q[i]) % MOD;
        }
        h = {h1, h2};
    }

    int cardinality() { return n; }

    void print()
    {
        cout << "{";
        for (int i = 0; i < n; i++) {
            children[i]->print();
            if (i != n - 1) {
                cout << ", ";
            }
        }
        cout << "}";
    }
};

vector<se *> st;

int main()
{
    fast_cin();
    pow_p.push_back(1);
    pow_q.push_back(1);
    for (int i = 1; i < 2001; i++) {
        pow_p.push_back(((ll)pow_p.back() * (ll)p) % MOD);
        pow_q.push_back(((ll)pow_q.back() * (ll)q) % MOD);
    }
    int tc;
    cin >> tc;
    while (tc--) {
        int q;
        cin >> q;
        st.clear();
        while (q--) {
            string op;
            cin >> op;
            if (op == "PUSH") {
                st.push_back(new se({}));  // empty set
            }
            else if (op == "DUP") {
                // st.push_back(st.back()->duplicate());
                st.push_back(st.back());
            }
            else if (op == "UNION") {
                se *a = st.back();
                st.pop_back();
                se *b = st.back();
                st.pop_back();
                vector<se *> c;
                int i = 0, j = 0;
                while (i < a->n && j < b->n) {
                    if (a->children[i]->h == b->children[j]->h) {
                        c.push_back(a->children[i]);
                        i++;
                        j++;
                    }
                    else if (a->children[i]->h < b->children[j]->h) {
                        c.push_back(a->children[i]);
                        i++;
                    }
                    else {
                        c.push_back(b->children[j]);
                        j++;
                    }
                }
                while (i < a->n) {
                    c.push_back(a->children[i]);
                    i++;
                }
                while (j < b->n) {
                    c.push_back(b->children[j]);
                    j++;
                }

                st.push_back(new se(c));
            }
            else if (op == "INTERSECT") {
                se *a = st.back();
                st.pop_back();
                se *b = st.back();
                st.pop_back();
                vector<se *> c;
                int i = 0, j = 0;
                while (i < a->n && j < b->n) {
                    if (a->children[i]->h == b->children[j]->h) {
                        c.push_back(a->children[i]);
                        i++;
                        j++;
                    }
                    else if (a->children[i]->h < b->children[j]->h) {
                        i++;
                    }
                    else {
                        j++;
                    }
                }
                st.push_back(new se(c));
            }
            else if (op == "ADD") {
                se *b = st.back();
                st.pop_back();
                se *a = st.back();
                st.pop_back();
                vector<se *> c = a->children;
                bool b_in_a = false;
                for (int i = 0; i < a->n; i++) {
                    if (a->children[i]->h == b->h) {
                        b_in_a = true;
                        break;
                    }
                }
                if (!b_in_a) {
                    c.push_back(b);
                }
                st.push_back(new se(c));
            }
            else {
                assert(false);
            }
            cout << st.back()->cardinality() << endl;
        }
        cout << "***" << endl;
    }

    return 0;
}