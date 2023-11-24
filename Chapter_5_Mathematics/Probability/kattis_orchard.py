'''
Kattis - orchard
Simple conditional probability problem. The probability of winning in a given state is the weighted sum of the probabilities of
winning in any othe next possible states.

Time: O(rgbys), Space: O(rgbys)
'''
from functools import lru_cache

@lru_cache(maxsize=None)
def dp(r, g, b, y, s): # probability of winning given this current game state
    if s == 0: return 0 
    if r+g+b+y == 0: return 1
    
    ans = 0
    moves = 2 # the basket and raven moves will always be valid
    if r>0: 
        ans += dp(r-1, g, b, y, s)
        moves += 1
    if g>0: 
        ans += dp(r, g-1, b, y, s)
        moves += 1
    if b>0: 
        ans += dp(r, g, b-1, y, s)
        moves += 1
    if y>0: 
        ans += dp(r, g, b, y-1, s)
        moves += 1
    ans += dp(r, g, b, y, s-1)
    
    if r == max(r, g, b, y): ans += dp(r-1, g, b, y, s) # note that due to symmetry it doesn't matter which max is removed
    elif g == max(r, g, b, y): ans += dp(r, g-1, b, y, s)
    elif b == max(r, g, b, y): ans += dp(r, g, b-1, y, s)
    elif y == max(r, g, b, y): ans += dp(r, g, b, y-1, s)

    ans /= moves
    return ans

r, g, b, y, s = map(int, input().split())
print(dp(r, g, b, y, s))