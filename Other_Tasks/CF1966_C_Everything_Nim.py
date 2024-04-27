t = int(input())

for _ in range(t):
    n = int(input())
    arr = map(int, input().split())
    arr = sorted(list(set(arr)))
    n = len(arr)
    
    for i in range(n):  
        if arr[i] == i+1: continue
        if (i%2 == 0): print("Alice")
        else: print("Bob")
        break
    else:
        if (n%2 == 0): print("Bob")
        else: print("Alice")