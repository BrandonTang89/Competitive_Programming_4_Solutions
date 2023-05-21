'''
Kattis - inverteddeck
Relatively simple, sort the array and find the first and last index that are different then check if the subarray is sorted in reverse order
Time: O(n log n), Space: O(n)
'''
n = int(input())
xs = list(map(int, input().split()))

arr = sorted(xs)

i = 0
while (i < n and arr[i] == xs[i]):
    i += 1
if (i == n):
    print(1, 1)
    exit()

j = n - 1
while (j >= i and arr[j] == xs[j]):
    j -= 1

if arr[i:j+1] == xs[i:j+1][::-1]:
    print(i+1, j+1)
else:
    print("impossible")
