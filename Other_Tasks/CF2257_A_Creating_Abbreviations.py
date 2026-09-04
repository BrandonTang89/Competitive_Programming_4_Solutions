for _ in range(int(input())):
    n, q = map(int, input().split())
    s = set()
    for _ in range(n):
        s.add(input()[0])
    
    possible = True
    for _ in range(q):
        for c in input().lower():
            if c not in s:
                possible = False
                break
    
    print("YES" if possible else "NO")