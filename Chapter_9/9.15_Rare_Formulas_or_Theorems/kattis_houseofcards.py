'''
Kattis - houseofcards
The number of cards in a house of height h is h*(3h+1)/2. We just brute force check... It's
abit scary because of the large h0, but just believe in python and itll be okay. Note that
we should remember to do integer division, else floating point errors will occur!

Time: O(?), Space: O(1)
'''
x = int(input())

import sys
while True:
    if (x % 2 == 0):
        if (((x//2) % 4) * ((1-x)%4))%4 == 0:
            print(x)
            sys.exit()
    else:
        if ((x % 4) * (((3*x+1)//2)%4))%4 == 0:
            print(x)
            sys.exit()
    x += 1
