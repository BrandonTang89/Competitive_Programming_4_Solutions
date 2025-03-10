for _ in range(int(input())):
    n = int(input())
    arr = list(map(int, input().split()))

    arr.sort(reverse=True)

    left = arr[: n + 1]
    right = arr[n + 1 :]

    gap = sum(left) - sum(right)
    right.append(gap)

    for i in range(2 * n + 1):
        if i % 2 == 1:
            print(right[i // 2], end=" ")
        else:
            print(left[i // 2], end=" ")
    print()
