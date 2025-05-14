for _ in range(int(input())):
    n, k = map(int, input().split())
    arr = list(map(int, input().split()))
    arr.sort()
    remove_right = arr[:-k] if k != 0 else arr
    
    if len(remove_right) % 2 == 0:
        left_median = remove_right[len(remove_right) // 2 - 1]
    else:
        left_median = remove_right[len(remove_right) // 2]
    
    remove_left = arr[k:]
    if len(remove_left) % 2 == 0:
        right_median = remove_left[len(remove_left) // 2]
    else:
        right_median = remove_left[len(remove_left) // 2]
    
    print(right_median - left_median + 1)
        