'''
Kattis - amultiplicationgame
Constructive game theory problem. It turns out the best strategy for the first player is always to multiply by 9, and the second player
should always multiply by 2. 

Time: O(log n), Space: O(1)
'''
from sys import stdin

for n in map(int, stdin):
    p = 1
    player = 0
    while p < n:
        p *= (9 if player == 0 else 2)
        player ^= 1
    
    print("Stan wins." if player == 1 else "Ollie wins.")