'''
Kattis - judgingmoose
Read and type.

Time: O(1), Space: O(1)
'''
a, b = map(int, input().split())
if a == b == 0: print('Not a moose')
elif a == b: print("Even", a + b)
else: print("Odd", max(a, b)*2)