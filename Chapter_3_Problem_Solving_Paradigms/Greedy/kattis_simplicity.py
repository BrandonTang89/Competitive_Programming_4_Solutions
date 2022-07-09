'''
Kattis - simplicity
Simply keep the most frequent 2 characters

Time: O(n log n), Space: O(n)'''
x = input()
from collections import Counter
c = Counter(x)
arr = sorted(c.values())
ans = sum(arr[:-2])
print(ans)