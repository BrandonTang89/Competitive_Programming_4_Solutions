for _ in range(int(input())):
    n = int(input())
    arr = list(map(int, input().split()))
    
    done = False
    for a, b in zip(arr, arr[1:]):
        if abs(a - b) <= 1:
            print(0)
            done = True
            break
    else:
        increasing = all(a < b for a, b in zip(arr, arr[1:]))
        decreasing = all(a > b for a, b in zip(arr, arr[1:]))
        if increasing or decreasing:
            print(-1)
        else:
            print(1)
        