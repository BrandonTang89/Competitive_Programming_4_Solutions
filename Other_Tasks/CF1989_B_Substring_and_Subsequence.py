t = int(input())
for _ in range(t):
    a = input()
    b = input()
    
    na, nb = len(a), len(b)
    
    def dp(i, j): # maximum number of chars that can be matched from a[i:] and b[j:]
        if i == na or j == nb: return 0
        if a[i] == b[j]: return 1 + dp(i+1, j+1)
        return dp(i+1, j) # skip a[i]

    maxSaved = 0
    for j in range(nb):
        maxSaved = max(maxSaved, dp(0, j))
    
    print(na + nb - maxSaved)