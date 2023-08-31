'''
Kattis - modulo
Straightforward.
Time: O(1), Space: O(1)
'''
print(len({int(input()) % 42 for _ in range(10)}))
