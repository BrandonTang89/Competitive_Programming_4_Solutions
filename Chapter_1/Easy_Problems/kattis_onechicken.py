'''
Kattis - onechicken
Just do.

Time: O(1), Space: O(1)
'''
a, b = map(int, input().split())
if b > a:
    print(f"Dr. Chaz will have {b-a} piece{'s' if b-a > 1 else ''} of chicken left over!")
else:
    print(f"Dr. Chaz needs {a-b} more piece{'s' if a-b > 1 else ''} of chicken!")