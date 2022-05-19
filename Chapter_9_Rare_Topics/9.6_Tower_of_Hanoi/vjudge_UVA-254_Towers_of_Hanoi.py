'''vjudge_UVA-254 - Towers of Hanoi
We define a recursive formula as seen below. Essentially we see if the biggest
piece has been moved. In each case, modify the initial, destination and intermediate
pegs.

Time: O(n), Space: O(1)
'''
while True:
    n, m = map(int, input().split())
    if (n == 0 and m == 0): break
    
    s = [0,0,0]
    
    init = 0
    dest = 1 if n%2 == 1 else 2
    inter = 2 if n%2 == 1 else 1
    for i in range(n-1, -1, -1):
        if (m >= 2**i):
            s[dest] += 1
            init, dest, inter = inter, dest, init
            m -= 2**i
        else:
            s[init] += 1
            init, dest, inter = init, inter, dest
    
    print(s[0], s[1], s[2])