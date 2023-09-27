/**Kattis - chemistvows
 * Quite straightforward, let dp(i) = whether we can construct s[i:]. Base case is can construct
 * empty string so dp(n) = true. Transitions are taking the first or first 2 letters. We use a
 * hash_set to store the element symbols.
 *
 * Time: O(n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

unordered_set<string> elements;
vector<int> memo;
int n;
string s;
bool dp(int i)
{  // able to construct s[i:]
    if (i == n) return true;
    if (memo[i] != -1) return memo[i];

    // try the first letter
    if (elements.find(s.substr(i, 1)) != elements.end()) {
        if (dp(i + 1)) return (memo[i] = true);
    }

    // try the first two letters
    if (i + 1 < n && elements.find(s.substr(i, 2)) != elements.end()) {
        if (dp(i + 2)) return (memo[i] = true);
    }

    return (memo[i] = false);
}
int main()
{
    {
        elements.insert("h");
        elements.insert("he");
        elements.insert("li");
        elements.insert("be");
        elements.insert("b");
        elements.insert("c");
        elements.insert("n");
        elements.insert("o");
        elements.insert("f");
        elements.insert("ne");
        elements.insert("na");
        elements.insert("mg");
        elements.insert("al");
        elements.insert("si");
        elements.insert("p");
        elements.insert("s");
        elements.insert("cl");
        elements.insert("ar");
        elements.insert("k");
        elements.insert("ca");
        elements.insert("sc");
        elements.insert("ti");
        elements.insert("v");
        elements.insert("cr");
        elements.insert("mn");
        elements.insert("fe");
        elements.insert("co");
        elements.insert("ni");
        elements.insert("cu");
        elements.insert("zn");
        elements.insert("ga");
        elements.insert("ge");
        elements.insert("as");
        elements.insert("se");
        elements.insert("br");
        elements.insert("kr");
        elements.insert("rb");
        elements.insert("sr");
        elements.insert("y");
        elements.insert("zr");
        elements.insert("nb");
        elements.insert("mo");
        elements.insert("tc");
        elements.insert("ru");
        elements.insert("rh");
        elements.insert("pd");
        elements.insert("ag");
        elements.insert("cd");
        elements.insert("in");
        elements.insert("sn");
        elements.insert("sb");
        elements.insert("te");
        elements.insert("i");
        elements.insert("xe");
        elements.insert("cs");
        elements.insert("ba");
        elements.insert("hf");
        elements.insert("ta");
        elements.insert("w");
        elements.insert("re");
        elements.insert("os");
        elements.insert("ir");
        elements.insert("pt");
        elements.insert("au");
        elements.insert("hg");
        elements.insert("tl");
        elements.insert("pb");
        elements.insert("bi");
        elements.insert("po");
        elements.insert("at");
        elements.insert("rn");
        elements.insert("fr");
        elements.insert("ra");
        elements.insert("rf");
        elements.insert("db");
        elements.insert("sg");
        elements.insert("bh");
        elements.insert("hs");
        elements.insert("mt");
        elements.insert("ds");
        elements.insert("rg");
        elements.insert("cn");
        elements.insert("fl");
        elements.insert("lv");
        elements.insert("la");
        elements.insert("ce");
        elements.insert("pr");
        elements.insert("nd");
        elements.insert("pm");
        elements.insert("sm");
        elements.insert("eu");
        elements.insert("gd");
        elements.insert("tb");
        elements.insert("dy");
        elements.insert("ho");
        elements.insert("er");
        elements.insert("tm");
        elements.insert("yb");
        elements.insert("lu");
        elements.insert("ac");
        elements.insert("th");
        elements.insert("pa");
        elements.insert("u");
        elements.insert("np");
        elements.insert("pu");
        elements.insert("am");
        elements.insert("cm");
        elements.insert("bk");
        elements.insert("cf");
        elements.insert("es");
        elements.insert("fm");
        elements.insert("md");
        elements.insert("no");
        elements.insert("lr");
    }

    int tc;
    cin >> tc;
    while (tc--) {
        cin >> s;
        n = s.size();
        memo.assign(n + 1, -1);

        if (dp(0))
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    return 0;
}