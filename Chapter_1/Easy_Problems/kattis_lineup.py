'''
Kattis - lineup
Compare list with the sorted version of the list.

Time: O(n log n), Space: O(n)
'''
n = int(input())
arr = [input() for _ in range(n)]

if arr == sorted(arr):
    print("INCREASING")
elif arr == sorted(arr, reverse=True):
    print("DECREASING")
else:
    print("NEITHER")