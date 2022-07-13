'''
Kattis - htoo
Lowkey just a input parsing problem. Just refer to below on how to parse the input. We don't need to BSTA, just take the min considering
each element.

Time: O(len(mol)), Space: O(len(mol))
'''
mol, n = input().split()
n = int(n)

def get_elements(mol):
    mol += 'A' # dummy terminator character
    cur = ""
    elements = {}
    for c in mol:
        if (c.isalpha()):
            if (cur == ""): 
                cur = c
                continue
            
            el = cur[0]
            amt = int(cur[1:]) if len(cur) > 1 else 1
            if (el in elements):
                elements[el] += amt
            else:
                elements[el] = amt
            cur = c
        else: 
            cur += c
    return elements
elements = get_elements(mol)
elements = {el: amt*n for el, amt in elements.items()}

target = input()
target_elements = get_elements(target)

ans = 1e10
for el, amt in target_elements.items():
    if (not el in elements):
        print(0)
        exit()
    
    ans = min(ans, elements[el]//amt)
print(ans)