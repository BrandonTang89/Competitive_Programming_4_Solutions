'''
Kattis - powereggs
Actually a hard problem, but we read the explanation in CP4 to get this super efficient solution
that runs in O(32*k).

Time: O(32k), Space: O(1)'''
def f(d, k): # number of floors we can determine with d drops and k eggs
    ans = 0
    cur = 1 # d choose i
    
    for i in range(1, k+1):
        cur = cur * (d-i+1) // i # d choose i = d choose (i-1) * (d-i+1) / i
        ans += cur
    return ans

num_tc = int(input())
for _ in range(num_tc):
    n, k = map(int, input().split())
    for i in range(1, 33):
        if (f(i, k) >= n): # able to do these many floors
            print(i)
            break
    else:
        print("Impossible")