for _ in range(int(input())):
    n = int(input())
    s1 = set(map(int, input().split()))
    s2 = set(map(int, input().split()))
    
    l1 = len(s1)
    l2 = len(s2)
    
    if l1 > l2:  # l1 <= l2
        l1, l2 = l2, l1
    
    if l1 > 1 and l2 > 1: 
        print("YES")
    elif l1 == 1:
        if l2 > 2:
            print("YES")
        else:
            print("NO")
    