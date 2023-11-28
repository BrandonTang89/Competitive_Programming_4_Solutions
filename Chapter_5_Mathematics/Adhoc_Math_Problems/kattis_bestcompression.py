'''
Kattis - bestcompression
Just math.
Time: O(1), Space: O(1)
'''
n, b = map(int, input().split())
print("yes" if (1 << (b + 1)) - 1 >= n else "no")