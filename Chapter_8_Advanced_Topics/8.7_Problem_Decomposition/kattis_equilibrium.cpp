/**Kattis - equilibrium
 * Math + Input Parsing. This took way longer than it supposed to. The parsing stuff
 * is quite routine, seems like some regular grammar thing. Then after, observe that if we
 * fix a specific leaf value, it actually fixes the entire tree. So we can try fixing each
 * leaf value and see how many other leaf values need to be changed. This is captured by the
 * "relative value" idea where we divide 1e16 across the tree and divide by the value to see
 * the factor by which the leaf fixes the tree.
 * 
 * Time: O(2^16), Space: O(2^16)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

struct node {
    int val;
    int numLeaves;
    node* left;
    node* right;
    int relativeVal;
    node(node* l, node* r, int v, int n)
    {
        left = l;
        right = r;
        val = v;
        numLeaves = n;
    }
};

inline bool isDigit(char c) { return c >= '0' && c <= '9'; }
string s;
pair<int, node*> parser(int l)
{
    // parse s[l..] until the end of the expression, return the index of the next char
    if (isDigit(s[l])) {
        int num = 0;
        while (isDigit(s[l])) {
            num = num * 10 + (s[l] - '0');
            l++;
        }
        return make_pair(l, new node(NULL, NULL, num, 1));
    }
    else {
        pair<int, node*> left = parser(l + 1);
        pair<int, node*> right = parser(left.first + 1);  // left.first + 1 to skip the comma
        // return right.first + 1 to skip the closing bracket
        return make_pair(right.first + 1,
                         new node(left.second, right.second, left.second->val + right.second->val,
                                  left.second->numLeaves + right.second->numLeaves));
    }
}

map<double, int> m;
void annotate(int relativeVal, node* r){
    if (r == NULL) return;
    r->relativeVal = relativeVal;
    if (r->left == NULL && r->right == NULL){ //leaf
        m[relativeVal/(double) r->val]++;
    }
    annotate(relativeVal>>1, r->left);
    annotate(relativeVal>>1, r->right);
}

int main()
{
    int tc;
    cin >> tc;

    while (tc--) {
        m.clear();
        cin >> s;
        pair<int, node*> p = parser(0);
        node* root = p.second;
        assert(p.first == (int) s.length());
        annotate(1<<16, root);

        int maxCount = 0;
        for (auto it = m.begin(); it != m.end(); it++){
            maxCount = max(maxCount, it->second);
        }
        cout << root->numLeaves - maxCount << endl;
    }

    return 0;
}