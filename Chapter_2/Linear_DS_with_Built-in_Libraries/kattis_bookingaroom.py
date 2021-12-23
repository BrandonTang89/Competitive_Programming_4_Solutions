'''
Kattis - booking a room
More or less just do a DAT since the max number of rooms is 100.

Time: O(n), Space: O(t)
'''
t, n = map(int, input().split())
arr = [False] * t

for _ in range(n):
    c = int(input())
    c -= 1
    arr[c] = True

for i in range(t):
    if (arr[i] == False):
        print(i + 1)
        break
else:
    print("too late")