for _ in range(int(input())):
    n = int(input())
    x = n // 15 + 1
    ans = 3 * x
    if n % 15 == 0:
        ans -= 2
    elif (n - 1) % 15 == 0:
        ans -= 1
    print(ans)
