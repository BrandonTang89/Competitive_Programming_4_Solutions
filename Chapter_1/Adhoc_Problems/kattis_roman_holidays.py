'''
Kattis - Roman Holidays
This is why they said adhoc problems aren't always easy...
While no superb optimisation or insane algorithm is needed, it's hard to wrap your head around the new number ordering
C.....M,MC...MM     ,MMC..............INF.........MMV.....MMXXXVIII, MV,...,MXXXVIII, V... XXXVIII
1   946 947  946*2  946*2+1                    (-54*3)   (-54*2-1),(-54*2)  -54*1-1   -54     -1    

Time: O(n * 1000)
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
hundreds = {
    0: "",
    100: "C",
    200: "CC",
    300: "CCC",
    400: "CD",
    500: "D",
    600: "DC",
    700: "DCC",
    800: "DCCC",
    900: "CM",
}

arab_rom_thousand = {}
rom_arab_thousand = {}
for hundred_arab, hundred_rom in hundreds.items():
    for ten_arab, ten_rom in tens.items():
        for one_arab, one_rom in ones.items():
            if hundred_arab+ten_arab+one_arab == 0:
                continue
            arab_rom_thousand[hundred_arab+ten_arab+one_arab] = hundred_rom+ten_rom+one_rom
            rom_arab_thousand[hundred_rom+ten_rom+one_rom] = hundred_arab+ten_arab+one_arab

arab_rom_thousand[1000] = "M"
rom_arab_thousand["M"] = 1000

sorted_rom_arab = {}
for index in sorted(rom_arab_thousand):
    sorted_rom_arab[index] = rom_arab_thousand[index]

from pprint import pprint
#pprint(sorted_rom_arab)


n = int(input())
for tc in range(n):
    a = int(input())
    
    a_000 = a%1000
    a_thousands = a // 1000

    if a_000 == 0:
        print(a_thousands * 946) # edge case
        continue

    ans = 0
    a_000_rom = arab_rom_thousand[a_000]
    if a_000_rom[0] != "V" and a_000_rom[0] != "X":
        for index, val in enumerate(sorted_rom_arab.keys()):
            if val == a_000_rom:
                ans = index+1
                ans += 946*a_thousands
                break
    else:
        for index, val in enumerate(sorted_rom_arab.keys()):
            if val == a_000_rom:
                ans = index-1000
                ans += (-54)*a_thousands

    print(ans)