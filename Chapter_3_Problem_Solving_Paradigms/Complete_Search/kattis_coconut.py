'''
Kattis - coconut
Slightly time waster, but easy.

Time: O(n), Space: O(n)
'''
s, n = map(int, input().split())

arr = [(i, 0) for i in range(n)]
cur = 0
while True:
    cur = (cur + s - 1) % len(arr)

    if arr[cur][1] == 0:    # folded
        arr[cur] = (arr[cur][0], 1)
        arr.insert(cur + 1, (arr[cur][0], 1))
    elif arr[cur][1] == 1:  # fist
        arr[cur] = (arr[cur][0], 2)
        cur = (cur + 1) % len(arr)
    elif arr[cur][1] == 2:  # palm
        arr.pop(cur)
        cur = (cur) % len(arr)
    else:
        assert False

    if len(arr) == 1:
        break
print(arr[0][0] + 1)
