'''
Kattis - licenselaunch
Easy qn.

Time: O(n)
'''
n = int(input())
arr = list(map(int, input().split()))
a = min(arr)

for i in range(n):
    if arr[i] == a:
        print(i)
        break