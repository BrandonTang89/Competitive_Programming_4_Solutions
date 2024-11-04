n, k, q = map(int, input().split())

arr = [list(map(int, input().split())) for _ in range(n)]

for r in range(k):
    cur = 0
    for c in range(n):
        cur |= arr[c][r]
        arr[c][r] = cur

for _ in range(q):
    m = int(input())
    mini = 0
    maxi = n-1
    
    for _ in range(m):
        region, o, val = input().split()
        region = int(region) - 1
        val = int(val)
        
        if o == '>':
            # find smallest row that has column region with value greater than val
            lo = mini
            hi = n
            
            while lo < hi:
                mid = (lo+hi)//2
                if arr[mid][region] > val:
                    hi = mid
                else:
                    lo = mid+1
            mini = lo
            
        else:
            # find largest row that has column region with value less than val
            lo = -1
            hi = maxi
            while lo < hi:
                mid = (lo+hi+1)//2
                if arr[mid][region] < val:
                    lo = mid
                else:
                    hi = mid-1
            maxi = lo
    
    if mini <= maxi:
        print(mini + 1)
    else:
        print(-1)