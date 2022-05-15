'''
Kattis - guess
Introductory interactive problem. Remember to flush the buffer after printing using flush=True parameter in print.
Time: O(1), Space: O(1)
'''
lo = 1
hi = 1000

while True:
    mid = (lo + hi) // 2
    print(mid, flush=True)
    
    response = input()
    if (response == 'lower'):
        hi = mid-1
    elif (response == 'higher'):
        lo = mid+1
    else:
        break