for _ in range(int(input())):

    n, k = map(int, input().split())

    ans = 0
    if n % 2 == 1:
        ans = 1
        n -= k

    ans += (n + k - 1 - 1) // (k - 1)

    print(ans)
