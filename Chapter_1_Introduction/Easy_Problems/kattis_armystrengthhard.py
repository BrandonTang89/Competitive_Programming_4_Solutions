'''
Kattis - armystrengthhard
Simple.
Time: O(n log n), Space: O(n)
'''
t = int(input())
for _ in range(t):
    input()
    n, m = map(int, input().split())
    x = list(map(int, input().split()))
    y = list(map(int, input().split()))
    x.sort()
    y.sort()
    
    i = 0
    j = 0
    
    while i < n and j < m:
        if x[i] < y[j]:
            i += 1
        else:
            j += 1
    
    if i == n:
        print("MechaGodzilla")
    elif j == m:
        print("Godzilla")