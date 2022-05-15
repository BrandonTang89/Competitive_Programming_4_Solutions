'''
Kattis - bobby

The key observation is that the expected winnings after a single game is a the weighted average
of the expected winnings from wining or losing a single game.

Time: O(y**2), Space: O(1)
'''

num_tc = int(input())
for _ in range(num_tc):
    r, s, x, y, w = map(int, input().split())
    
    p_win_1 = (s - r + 1)/s
    p_lose_1 = 1 - p_win_1
    
    def exp_val(num_roll, num_success):
        if (num_roll == y):
            return (num_success >= x)*w

        return p_win_1*exp_val(num_roll+1, num_success+1) + p_lose_1*exp_val(num_roll+1, num_success)

    print("yes" if exp_val(0, 0) > 1 else "no")