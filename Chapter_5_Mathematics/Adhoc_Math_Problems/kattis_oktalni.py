'''
Kattis - oktalni
Use built-in functions to convert binary to decimal and then to octal

Time: O(1), Space: O(1)
'''
x = int(input(), 2)
print(oct(x)[2:]) # remove the front part "0o"