for _ in range(int(input())):
    n = int(input())
    arr = list(map(int, input().split()))
    arr = [x - 1 for x in arr]

    i = 0
    while i < n:
        if arr[i] == i:
            i += 1
            continue

        elif arr[i] == i + 1 and arr[i + 1] == i:
            i += 2
            continue

        else:
            print("NO")
            break
    else:
        print("YES")
