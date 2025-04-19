for _ in range(int(input())):
    n, k = map(int, input().split())
    
    rs = map(int, input().split())
    ls = map(int, input().split())
    
    together = [(r, l) for r, l in zip(rs, ls)]
    together.sort(key=lambda x: min(x[0], x[1]), reverse=True)
    
    ans = sum(max(x[0], x[1]) for x in together)
    ans += sum(min(x[0], x[1]) for x in together[:k-1])
    ans += 1
    
    print(ans)