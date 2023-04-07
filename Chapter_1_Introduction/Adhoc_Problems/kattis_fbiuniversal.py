# Kattis - fbiuniversal
# Straightforward but perhaps abit tedious
# Time: O(1), Space: O(1)
tc = int(input())

digit_to_char = "0123456789ACDEFHJKLMNPRTVWX"
char_to_digit = {c: i for i, c in enumerate(digit_to_char)}

def tobase10(s):
    ans = 0
    while s != "":
        ans *= 27
        ans += char_to_digit[s[0]]
        s = s[1:]
    return ans

for t in range(1, tc+1):
    _, s = input().split()
    
    cd = s[-1]
    rest = s[:-1]

    rest = rest.replace("B", "8")
    rest = rest.replace("G", "C")
    rest = rest.replace("I", "1")
    rest = rest.replace("O", "0")
    rest = rest.replace("Q", "0")
    rest = rest.replace("S", "5")
    rest = rest.replace("U", "V")
    rest = rest.replace("Y", "V")
    rest = rest.replace("Z", "2")
    
    # (2*D1 + 4*D2 + 5*D3 + 7*D4 + 8*D5 + 10*D6 + 11*D7 + 13*D8) mod 27
    supposed_check_digit = (2*char_to_digit[rest[0]] + 4*char_to_digit[rest[1]] + 5*char_to_digit[rest[2]] + 7*char_to_digit[rest[3]] + 8*char_to_digit[rest[4]] + 10*char_to_digit[rest[5]] + 11*char_to_digit[rest[6]] + 13*char_to_digit[rest[7]]) % 27
    if digit_to_char[supposed_check_digit] == cd:
        print(t, tobase10(rest))
    else:
        print(t, "Invalid")