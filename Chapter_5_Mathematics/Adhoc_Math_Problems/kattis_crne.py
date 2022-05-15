'''
Kattis - crne
Note that the positions of the cuts don't matter, only the number of horizontal and vertical cuts. Total number of pieces is 
(number of vertical cuts +1) * (number of horizontal cuts +1). So it should be intuitive that to maximise the number of cuts, we divide
the cuts between the vertical and horizontal cuts as evenly as possible (can be proved by calculus).
'''
n = int(input())

if (n %2 == 0):
    print((n//2 +1 )*(n//2 + 1))
else:
    print((n//2 +1 )*((n+1)//2+1))