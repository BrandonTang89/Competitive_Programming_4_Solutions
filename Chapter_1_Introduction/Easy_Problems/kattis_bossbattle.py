'''
Kattis - bossbattle
Just look at the pattern, draw if necessary.

Time: O(1), Space: O(1)
'''
x = int(input())
if x <= 3:
    print(1)
else:
    print(x-2)