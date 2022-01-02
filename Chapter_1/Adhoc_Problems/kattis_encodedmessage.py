'''
Kattis - encodedmessage
Load the message in row major order into a 2D array, then read it in a different order.

Time: O(n^2), Space: O(n^2)
'''
num_tc = int(input())
for _ in range(num_tc):
    s = list(input())
    n = len(s)
    n = int(n**0.5)
    
    grid = [ [s.pop(0) for _ in range(n)] for _ in range(n) ]
    
    ans = ""
    for i in range(n-1, -1, -1):
        for j in range(n):
            ans += grid[j][i]
    print(ans)