'''
Kattis - Rimski
A relatively easy roman numeral question. Doing it case by case results in too many annoying corner cases.
Given the small input size, it is easy to just 
    precompute all roman numerals from 1 to 99
    and compare all permutations of the input with the dictory of roman numerals

Time: O(2^[len(n)]), len(n) <= len(LXXXVIII) = 8
Mem: O(2^[len(n)), could be done on the fly for O(1) but thats again unnecessary
'''
ones = {
    0: "",
    1: "I",
    2: "II",
    3: "III",
    4: "IV",
    5: "V",
    6: "VI",
    7: "VII",
    8: "VIII",
    9: "IX"
}
tens = {
    0: "",
    10: "X",
    20: "XX",
    30: "XXX",
    40: "XL",
    50: "L",
    60: "LX",
    70: "LXX",
    80: "LXXX",
    90: "XC",
}

one_to_hundred = {}
for arab_tens, rom_tens in tens.items():
    for (arab_ones, rom_ones) in ones.items():
        one_to_hundred[arab_ones + arab_tens] = rom_tens + rom_ones

one_to_hundred_rom = dict((v,k) for k,v in one_to_hundred.items())


n = input()
from itertools import permutations
perms = [''.join(p) for p in permutations(n)]

min_val_arab = 100
min_val_rom = "C"
for perm in perms:
    if perm in one_to_hundred_rom.keys():
        if one_to_hundred_rom[perm] < min_val_arab:
            min_val_arab = one_to_hundred_rom[perm]
            min_val_rom = perm

print(min_val_rom)
