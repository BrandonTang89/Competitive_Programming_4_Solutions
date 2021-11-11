'''
Kattis - mixedbasearithmetic

The idea itself is not that hard. From the least sigificant digit to the most, we convert the digit
to decimal and add the amount remaining to add. Then, the new number in its place is just the total
amount mod the base size and converted back. The amount to add to the next base is the amount to add
divided by the base size. This continues until we reach the front.

This is where the problem is kinda dumb.. In decimal, the next digit would be 1 if we needed to add
1 to 9. However, the next digit in the other 2 bases when 1 is added to z or Z is aa or AA, which
would be like having 1 + 9 = 00. So, we need to remove 1 from the amount to add for everytime
we add a new digit for the other 2 bases to accout for this.

Time: O(len(ans)), Space: O(len(ans))
'''
from sys import stdin
lines = stdin.readlines()

base_lower = {'a': 0, 'b': 1, 'c': 2, 'd': 3, 'e': 4, 'f': 5, 'g': 6, 'h': 7, 'i': 8, 'j': 9, 'k': 10, 'l': 11, 'm': 12,
              'n': 13, 'o': 14, 'p': 15, 'q': 16, 'r': 17, 's': 18, 't': 19, 'u': 20, 'v': 21, 'w': 22, 'x': 23, 'y': 24, 'z': 25}
lower_base = {0: 'a', 1: 'b', 2: 'c', 3: 'd', 4: 'e', 5: 'f', 6: 'g', 7: 'h', 8: 'i', 9: 'j', 10: 'k', 11: 'l', 12: 'm',
              13: 'n', 14: 'o', 15: 'p', 16: 'q', 17: 'r', 18: 's', 19: 't', 20: 'u', 21: 'v', 22: 'w', 23: 'x', 24: 'y', 25: 'z'}

base_upper = {'A': 0, 'B': 1, 'C': 2, 'D': 3, 'E': 4, 'F': 5, 'G': 6, 'H': 7, 'I': 8, 'J': 9, 'K': 10, 'L': 11, 'M': 12,
              'N': 13, 'O': 14, 'P': 15, 'Q': 16, 'R': 17, 'S': 18, 'T': 19, 'U': 20, 'V': 21, 'W': 22, 'X': 23, 'Y': 24, 'Z': 25}
upper_base = {0: 'A', 1: 'B', 2: 'C', 3: 'D', 4: 'E', 5: 'F', 6: 'G', 7: 'H', 8: 'I', 9: 'J', 10: 'K', 11: 'L', 12: 'M',
              13: 'N', 14: 'O', 15: 'P', 16: 'Q', 17: 'R', 18: 'S', 19: 'T', 20: 'U', 21: 'V', 22: 'W', 23: 'X', 24: 'Y', 25: 'Z'}

base_num = {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9}
num_base = {0: '0', 1: '1', 2: '2', 3: '3', 4: '4', 5: '5', 6: '6', 7: '7', 8: '8', 9: '9'}


def type_char(char):  # returns the 0th number on the base
    if (char in base_lower):
        return 'a'
    elif (char in base_upper):
        return 'A'
    elif (char in base_num):
        return '0'

for line_num in range(0, len(lines)):
    x, n = lines[line_num].split()
    n = int(n)

    x = x[::-1]
    x = list(x)

    index = 0
    while n > 0:
        # print(x)
        if index >= len(x):
            # to spawn new char
            x.append(type_char(x[-1]))
            if (type_char(x[-1]) == 'a' or type_char(x[-1]) == 'A'):
                n -= 1

        c = x[index]
        if (type_char(c) == '0'):
            base = base_num
            r_base = num_base
            base_size = 10
        elif (type_char(c) == 'a'):
            base = base_lower
            r_base = lower_base
            base_size = 26
        elif (type_char(c) == 'A'):
            base = base_upper
            r_base = upper_base
            base_size = 26

        deci = base[c] + n
        new_char = r_base[deci % base_size]
        x[index] = new_char
        n = deci // base_size
        index += 1
        # print(n, c,  deci, base_size)

    print(''.join(x[::-1]))