'''
Kattis - character
Return the number of subsets with >= 2 characters. Ie total number of subsets - subsets with 1 char
and subsets with 0 char
Time: O(log n), Space: O(1)
'''
n = int(input())
print(2**n - n - 1)