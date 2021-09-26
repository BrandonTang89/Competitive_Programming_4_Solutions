'''
Kattis - Ignore

Observation 1:
    Only the digits 1,2,5,6,8,9 result in a valid digit when rotated 180 degrees
    Thus, the kth number will be 
        the k in base 7,
        with the digits replaced by their corresponding rotated digit
        and the number in reverse direction (least significant digit at the front)

Time: O(1 per k) Mem: O(1)
'''

import sys 

dat = [0,1,2,5,9,8,6] #  after the 180 degree rotation, i -> dat[i]
for k in sys.stdin:
    
    k = int(k)
    arr = ""
    while k>0:
        arr+=str(dat[k%7])
        k//=7

    print (arr)