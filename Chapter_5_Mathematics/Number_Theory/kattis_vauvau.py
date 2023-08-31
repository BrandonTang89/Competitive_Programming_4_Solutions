'''
Kattis - vauvau
Simple math.
Time: O(1), Mem: O(1)
'''
a, b, c, d = map(int, input().split())


def dog_status(t):
    x = (1 if t % (a + b) < a else 0) + (1 if t % (c + d) < c else 0)
    if x == 2:
        return "both"
    elif x == 1:
        return "one"
    else:
        return "none"


for t in map(int, input().split()):
    print(dog_status(t-1))
