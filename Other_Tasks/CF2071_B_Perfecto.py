
from functools import lru_cache

@lru_cache(maxsize=None)
def isSquare(n):
    if n == 0 or n == 1:
        return True

    start = 1
    end = n
    while start <= end:
        mid = (start + end) // 2
        if mid * mid == n:
            return True
        elif mid * mid < n:
            start = mid + 1
        else:
            end = mid - 1
    return False


for _ in range(int(input())):
    n = int(input())
    
    s = 0
    i = 1
    ans = []
    while i < n+1:
        s += i
        if isSquare(s):
            if i == n:
                ans = [-1]
                break
            else:
                ans.append(i+1)
                ans.append(i)
                s += i+1
                i += 2
        else:
            ans.append(i)
            i += 1
    
    print(" ".join(map(str, ans)))