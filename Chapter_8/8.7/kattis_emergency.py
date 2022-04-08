''' Kattis - emergency
Just a simple programme. But please interpret the problem correctly... And work carefully,

Time: O(1), Space: O(1)
'''
n, k = map(int, input().split())
if (k < n-1):
    print(k + (1 if 2*k <= n-1 else 0) + (n-1) - k*((n-1)//k))
else:
    print(n-1)