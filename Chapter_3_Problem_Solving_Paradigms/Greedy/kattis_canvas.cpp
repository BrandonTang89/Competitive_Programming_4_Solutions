/* Kattis - Canvas
This problem requires insight and ingenuity... Once you have that, implementation is easy

Observation 1:
    The trick is to view the problem in reverse. If we already have n distinct colours, how do we reverse them to 
    all white? Well, each time we do a reversal move, we shold aim to combine 2 colours into 1 colour. But then, which
    colours to combine??? Its actually pretty easy here to see that we should first combine the 2 smallest colours. 
    Once we combine the 2 smallest colours, they are replaced by 1 larger colour that is the sum of their 2 sizes. Now,
    we have the same problem but with n-1 colours.

    Doing this repeatedly results in an optimal outcome! This should be pretty intuitive even without a rigourous proof.

Time: O(n log n)
Mem: O(n)
*/
#include <bits/stdc++.h>
using namespace std;

long long t, n, s, temp;
priority_queue<long long,vector<long long>, greater<long long>> pq;
int main(){
    cin >> t;
    for (long long tc=0;tc<t;tc++){
        cin >> n;
        for (long long i=0;i<n;i++){
            cin >> s;
            pq.push(s);
        }

        long long counter = 0;
        while (pq.size() > 1){
            temp = pq.top();
            pq.pop();
            temp = temp + pq.top();
            pq.pop();
            counter+=temp;

            pq.push(temp);
        }
        cout << counter << endl;
        pq.pop();
    }

    return 0;
}