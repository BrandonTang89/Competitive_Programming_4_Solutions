for _ in range(int(input())):
    
    n = int(input())
    p = [-1] * n
    
    for pi in range(n):
        row = list(input())
        idx = 0
        for pj in range(n):
            if pi > pj and row[pj] == '1':
                idx += 1
            if pi < pj and row[pj] == '0':
                idx += 1
        p[idx] = pi + 1
    
    print(' '.join(map(str, p)))
    