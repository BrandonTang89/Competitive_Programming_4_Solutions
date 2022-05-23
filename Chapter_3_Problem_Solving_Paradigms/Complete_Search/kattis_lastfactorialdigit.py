from math import factorial


'''
Kattis - lastfactorialdigit
Can be precomputed, but we don't even need to do that apparently.
'''
num_tc = int(input())
for _ in range(num_tc):
    x = int(input())
    print(factorial(x) % 10)