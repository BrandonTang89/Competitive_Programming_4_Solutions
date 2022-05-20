''' vjudge - UVA-10254 - The Priest Mathematician
We make use of 2 key ideas to speed up the computation: 
- the optimal k for n is always >= the optimal k for n-1
- the graph of ans has only 1 minima, so we can stop the search once it starts to increase

From examining the optimal k for many different values of n, we notice that k for n is usually
very very (<10) near k for n-1, so using both of the above strategies is sufficiently fast to AC.

Time: O(?), Space: O(n)
'''

T = [0,1]
opt = 2
for i in range(2,10001):
    ans = 2*T[1]+2**(i-1)-1
    for j in range(opt, i):
        cur = 2*T[j]+2**(i-j)-1
        if (cur < ans):
            ans = cur
            opt = j
        else:
            break
            
    T.append(ans)

from sys import stdin
for line in stdin:
    print(T[int(line)])