'''
Kattis - Arithmetic

Abridge Problem Statement: Convert an a number from octal to hexadecimal

This is actually insanely easy with python. 
    Use int(val, base) to interprete a string val of a certain base
    Use hex(x) to format the number as a hexadecimal and perform simple string manipulations

Time: O(1) Mem: O(1)
'''
x = int(input(), 8)
x = str(hex(x)).upper()[2:]

print(x)