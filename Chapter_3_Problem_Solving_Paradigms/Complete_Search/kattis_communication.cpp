/* Kattis - Communication

Observation 1:
    there are much more bytes to process than number of unique bytes. So instead of trying to reverse all the bytes
    in the data stream one by one, we compute all possible encrypted bytes and store it into a hash table which can then be
    used to decrypt the steam bytes in O(1) time for each byte

Time: O(n), Mem: O(n)
*/
#include <bits/stdc++.h>
using namespace std;

unordered_map<int, int> m;  // m[hashed] = byte
int n, h;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // preproces bits;
    for (int b = 0; b < 256; b++) {
        h = b ^ (b << 1);
        h = h & ((1 << 8) - 1);
        //printf("b: %d, h:%d\n", b, h);
        m[h] = b;
    }
    cin >> n;

    int b;
    for (int i = 0; i < n; i++) {
        cin >> b;
        cout << m[b];

        cout << ((i != (n - 1)) ? ' ' : '\n');
    }

    return 0;
}