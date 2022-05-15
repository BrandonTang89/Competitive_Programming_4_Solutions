'''
Kattis - factstone
Observation 1:
    We can't directly compute the factorial and the max size that the computer can hold
    since there are up to 4194304 bits (obviously computing to 2^4194304 is not possible).

    We know that we can store n! if n! < 2**num_bits <=> log2(n!) < num_bits. Thus we work
    with the second inequality to make the numbers reasonable.
     
    Note that log2(n!) = log2(n) + log2(n-1) + ... + log2(1), so we can just do a linear
    search with a for loop.

Time: O(num_bits): Mem: O(1)
'''
from math import log2
while (1):
    year = int(input())
    if (year == 0):
        break
    year -= 1960
    p = year // 10

    bits = 2**p * 4
    print(bits)
    x = log2(2) # 2! = 2
    for i in range(3, 100000000): # 3 to INF
        x += log2(i)
        if (x >= bits):
            print(i-1)
            break