"""
Kattis - blockgame2
An interesting game. Let the height of the stacks be N and M, N > M.
Obviously if N == 0 mod M, then the current player can win. If 2M > N > M, we can only do 1 move,
to remove M from N. But the interesting part is if N > 2M...

If N > 2M, then N = M + M + ... + M + (N mod M). We don't actually know if the current player
will win if we remove the maximum number of M, but we know that there are 2 cases
1. Current player wins if we move to (N mod M, M), so we just do it.
2. Current player loses if we move to (N mod M, M). Well, in this case we move to (M + N mod M, M)
   instead. This causes the opponent to need to play to (N mod M, M) since M < M + N mod M < 2M,
   note that N mod M is never 0 since we would have caught it in the above cases. This means that 
   the opponent would lose.
Thus, if N > 2M, we will always win.

Time: O(n), Space: O(1)
"""
n, m = map(int, input().split())
n, m = (max(n, m), min(n, m))

def player_wins(n, m):
    if n % m == 0:
        return True
    if n > 2 * m:
        return True
    return not player_wins(m, n % m)    

print("win" if player_wins(n, m) else "lose")