'''
Kattis - trainpassengers
Ensure to consider all the cases where it is impossible

Time: O(n), Space: O(1)
'''
c, n = map(int, input().split())

cur = 0
for station in range(n):
    alighted, boarded, wait = map(int, input().split())
    
    cur -= alighted
    if cur < 0:
        print("impossible")
        exit()
    
    cur += boarded
    if cur > c:
        print("impossible")
        exit()
    
    if (wait > 0) and cur != c:
        print("impossible")
        exit()
    
    if (wait != 0 and station == n-1):
        print("impossible")
        exit()
        
    if (station == n-1 and cur != 0):
        print("impossible")
        exit()
print("possible")