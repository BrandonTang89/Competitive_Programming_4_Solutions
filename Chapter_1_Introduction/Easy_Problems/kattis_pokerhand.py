'''
Kattis - pokerhand
Easy question. Use Counter.

Time: O(n), Space: O(n)
'''
s = input().split()
s = [x[0] for x in s]

from collections import Counter
s = Counter(s)
print(max(s.values()))