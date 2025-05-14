for _ in range(int(input())):
    n = int(input())
    arr = list(map(int, input().split()))
    arr.sort()

    prev = -1 
    freq = 0
    packed_arr = []
    for i in range(n):
        if arr[i] == prev:
            freq += 1
        else:
            if prev != -1:
                packed_arr.append((prev, freq))
            freq = 1
        prev = arr[i]
    packed_arr.append((prev, freq))
    
    prev = -10
    EMPTY = 0
    HOLDING = 1
    
    state = EMPTY
    for (pos, num) in packed_arr:
        if num >= 4: 
            print("Yes")
            break
        if pos == prev+1:
            if num >= 2 and state == HOLDING:
                print("Yes")
                break
            elif num >= 2 and state == EMPTY:
                state = HOLDING
        else:
            if num >= 2:
                state = HOLDING
            else:
                state = EMPTY        
        prev = pos
    else:
        print("No")