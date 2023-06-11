'''
Kattis - sort
Just sort according to freq and first occurrence of the value. Use hashmaps.
Time: O(n log n), Space: O(n)
'''
from collections import Counter
n, c = map(int, input().split())
a = list(map(int, input().split()))
fo = {}
for i in range(len(a)):
    if a[i] not in fo:
        fo[a[i]] = i
cnt = Counter(a)
print(' '.join(map(str, (sorted(a, key=lambda x: (-cnt[x], fo[x]))))))