'''
Kattis - whichbase
Cheesed the problem with Python's built-in int() function.
Time: O(1), Space: O(1)
'''
n = int(input())
for tc in range(1, n+1):
    _, n = input().split()

    octal = 0
    try:
        octal = int(n, 8)
    except:
        pass

    decimal = int(n)
    hexa = int(n, 16)

    print(f'{tc} {octal} {decimal} {hexa}')