for _ in range(int(input())):
    n = int(input())
    arr = list(sorted(map(int, input().split())))
    maxi = max(arr)
    ans = 0

    for i in range(n):
        a = arr[i]
        top = 0  # exclusive
        bottom = n - 1  # exclusive
        for j in range(i + 1, n):
            b = arr[j]
            while top < n and arr[top] < a + b:
                top += 1
            while bottom > j and arr[bottom] > maxi - a - b:
                bottom -= 1
            bottom = max(bottom, j)

            if top > bottom:
                ans += top - bottom - 1

    print(ans)
