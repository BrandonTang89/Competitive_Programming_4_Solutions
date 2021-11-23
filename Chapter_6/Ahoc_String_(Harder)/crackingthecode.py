'''
Kattis - crackingthecode
Id consider this a time waster problem since its very tedious to debug. There were many different
bugs I had to fix.

Time: O(E), Space: O(E)
'''
num_tc = int(input())

alphabets = set("abcdefghijklmnopqrstuvwxyz")
def get_substitution(E, D):
    if (len(E) != len(D)):
        return {}
    subsitution = {} # subsitution[cipher_text_char] = plain_text_char
    for cipher_text_char, plain_text_char in zip(E, D):
        if (cipher_text_char in subsitution): # either both inside and matching
            if (subsitution[cipher_text_char] != plain_text_char):
                return {}
        elif (plain_text_char in subsitution.values()): # Potential BUG: Check this
            return {}
        else: # or non matching
            subsitution[cipher_text_char] = plain_text_char
    
    assert(len(set(subsitution.values())) == len(set(subsitution.keys())))        
    return subsitution

def merge_subtitutions(sub1, sub2):
    merged_sub = {}
    for cipher_char in sub1:
        if (cipher_char in sub2):
            if (sub1[cipher_char] == sub2[cipher_char]):
                merged_sub[cipher_char] = sub2[cipher_char]
    return merged_sub

for _ in range(num_tc):
    n = int(input())
    encrypted = [input() for _ in range(n)]
    D = input()
    X = input()
    
    found_sub = False # Potential BUG: use this rather than using the fact that substitution = {}
    subsitution = {}
    for E in encrypted:
        if (get_substitution(E, D) != {}): 
            if (found_sub):
                subsitution = merge_subtitutions(subsitution, get_substitution(E, D))
            else:
                subsitution = get_substitution(E, D)
                found_sub = True
        # print(get_substitution(E, D), subsitution)
        
    if len(subsitution) == 25: # Potential BUG: check this here rather than during merging
        unlisted_cipher_char = alphabets - set(subsitution.keys())
        unlisted_plain_char = alphabets - set(subsitution.values())
        subsitution[unlisted_cipher_char.pop()] = unlisted_plain_char.pop()
        
    if (not found_sub):
        print("IMPOSSIBLE")
    else:
        decrypted_x = ""
        for cipher_char in X:
            if (cipher_char in subsitution):
                decrypted_x += subsitution[cipher_char]
            else:
                decrypted_x += "?"
        print(decrypted_x)
    