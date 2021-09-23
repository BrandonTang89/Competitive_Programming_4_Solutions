'''
Kattis - WizardofOdds

Simple knowledge of binary search is required. The first if statement is to prevent the monsterous calculation of 2**(10**101).

Python is used for native big integer support

Time: O(1), Mem; O(1)
'''
n, k = input().split()
n = int(n)
k = int(k)

if k > 350: # Since 2**350 > MAX_N
    print("Your wish is granted!")
elif 2**k >= n:
    print("Your wish is granted!")
else:
    print("You will become a flying monkey!")