# Kattis - euclid's game
# Use a theorem from theinnerframe.org/2021/01/03/euclids-game/
# Time: O(1), Space: O(1)
while True:
    x, y = map(int, input().split())
    if x == 0 and y == 0:
        break
    x, y = min(x, y), max(x, y)
    if (y%x == 0 or y / x > 1.6180):
        print("Stan wins")
    else:
        print("Ollie wins")