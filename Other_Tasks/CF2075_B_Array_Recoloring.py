for _ in range(int(input())):
    n, k = map(int, input().split())
    arr = list(map(int, input().split()))

    if k >= 2:
        top_kp1 = sorted(arr, reverse=True)[: k + 1]
        print(sum(top_kp1))
    else:

        x = arr[0] + arr[-1]
        if n > 2:
            y = max(arr[0], arr[-1]) + max(arr[1:-1])
            print(max(x, y))
        else:
            print(x)
