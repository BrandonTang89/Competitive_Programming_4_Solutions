'''
Kattis - creditcard
There is a high probability of floating point errors if we are not careful. Using python is thus a better
option due to its "infinite" precision floats.

Time: O(1200), Space: O(1)
'''
num_tc = int(input())
for _ in range(num_tc):
    r, b, m = map(float, input().split())
    r /= 100
    b *= 100
    b = round(b)
    m *= 100
    m =  round(m)
    
    counter = 0
    while b > 0 and counter <= 1200:
        b *= (r+1)
        b = round(b)
        b -= m
        counter+= 1
    
    if (counter <= 1200 and b <= 0):
        print(counter)
    else:
        print("impossible")