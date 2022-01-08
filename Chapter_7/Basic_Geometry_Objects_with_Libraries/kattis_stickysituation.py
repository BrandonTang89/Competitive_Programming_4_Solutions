'''
Kattis - stickysituation
A triangle is non-degenerate if a + b > c where a < b < c and a, b, c are the sides of the
triangle.

Observe that if we choose the longest side c, then our best option for the other 2 sides is
going to be the 2 sticks that are just shorter than c. To determine the 2 sticks just shorter
than c, we sort the array first.

Time: O(n log n), Space: O(n)
'''
n = int(input())
arr = list(map(int, input().split()))
arr.sort()

for i in range(2, n):
    if arr[i-2] + arr[i-1] > arr[i]:
        print("possible")
        exit()
print("impossible")