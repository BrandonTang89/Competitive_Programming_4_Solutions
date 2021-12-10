'''
Kattis - timebomb
We use a single string that is the row major representation of each digit to map the image to
the digits. The rest is pretty self explanatory.
Note the pretty useful ljust string method to pad spaces until the string is of the correct length

Time: O(n), Space: O(n)
'''
import sys
fig_to_decimal = {
    "**** ** ** ****": 0,
    "  *  *  *  *  *": 1,
    "***  *****  ***": 2,
    "***  ****  ****": 3,
    "* ** ****  *  *": 4,
    "****  ***  ****": 5,
    "****  **** ****": 6,
    "***  *  *  *  *": 7,
    "**** ***** ****": 8,
    "**** ****  ****": 9
}

max_length = 0
lines = [input() for _ in range(5)]
for line in lines:
    max_length = max(max_length, len(line))
lines = [line.ljust(max_length) for line in lines]

number = ""
for i in range(0, len(lines[0]), 4):
    digit = "".join(lines[j][i:i+3] for j in range(5))
    if (not digit in fig_to_decimal):
        print("BOOM!!")
        sys.exit(0)
    number += str(fig_to_decimal[digit])

number = int(number)
if (number % 6 == 0):
    print("BEER!!")
    sys.exit(0)
print("BOOM!!")