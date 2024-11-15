for _ in range(int(input())):

    n = int(input())
    if n % 2 == 0:
        for i in range(1, n + 1):
            print((i + 1) // 2, end=" ")
        print()
        continue

    if n < 27:
        print(-1)
        continue

    ans = [0] * n
    ans[0] = 1
    ans[9] = 1
    ans[25] = 1
    ans[26] = 2
    ans[22] = 2

    cur = 3
    i = 0
    while i < n:
        if ans[i] == 0:
            ans[i] = cur
            ans[i + 1] = cur
            cur += 1
            i += 2
        else:
            i += 1

    print(" ".join(map(str, ans)))
