# cannot iff there is a subarray [1,0,1]
# assign X to all 1s, and unique numbers to all 0s, the edges are easy
for _ in range(int(input())):
    n = int(input())
    arr = list(map(int, input().split()))
    
    i = 0
    prev = 0
    seen1 = False
    can = True
    for i in range(n-2):
        if arr[i] == 1: 
            if prev == 1 and seen1:
                can = False
                break
            
            seen1 = True
            prev = 0
            continue
        
        prev += 1
    
    print("YES" if can else "NO")    
