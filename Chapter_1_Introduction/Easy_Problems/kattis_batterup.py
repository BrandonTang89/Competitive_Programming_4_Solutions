'''
Kattis - batterup
use filter to generate an function that returns True if the value is in the list.

Time: O(n), Space: O(n)
'''
n = int(input())
arr = list(map(int, input().split()))
arr = list(filter(lambda x: x!= -1, arr))

print(sum(arr) / len(arr))