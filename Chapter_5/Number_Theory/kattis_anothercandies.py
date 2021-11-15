'''
Kattis - anothercandies
Simple modulo arithmetic. Just take sum mod n, we can mod n as we go from preventing the sum
from becoming too big.

Time: O(num_tc * n), Space: O(1)
'''
num_tc = int(input())

for _ in range(num_tc):
    n = input() # clear the empty line
    n = int(input())
    
    ans = 0
    for i in range(n):
        ans += int(input())
        ans %= n
    
    print("YES" if ans == 0 else "NO")