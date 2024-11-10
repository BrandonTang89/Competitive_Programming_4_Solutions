for _ in range(int(input())):
    n, b, c = map(int, input().split())
    if n == 1:
        if c == 0:
            print(0)
        else:
            print(1)
        continue

    if b == 0:
        if n > c + 2:
            print(-1)
        else:
            if n == c + 1 or n == c + 2:
                print(n - 1)
            else:
                print(n)
        continue

    maxI = (n - 1 - c) // b
    maxI = max(maxI, -1)

    numSkipped = maxI + 1
    numLeft = n - numSkipped

    print(numLeft)
