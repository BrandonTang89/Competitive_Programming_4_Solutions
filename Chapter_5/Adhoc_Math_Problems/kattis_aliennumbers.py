'''
Kattis - Aliennumbers
Unlike the "trivial" difficulty suggests, this question could be difficult. Luckily run time is not that important so we
can just use python which allows for shorter and neater code (stuff like reversing arrays instead of counting backward)

Time: O(t * (len(an) * log_target_base(source_base))), Mem: O(len(target) + len(source) + len(an))
'''
t = int(input())

for tc in range(t):
    (an, source, target) = tuple(input().split())

    source_dict = {}
    for i,val in enumerate(source):
        source_dict[val] = i
    target_dict = {}
    for i,val in enumerate(target):
        target_dict[i] = val

    source_base = len(source)
    target_base = len(target)

    deci = 0
    an = an[::-1]
    for i in range(len(an)):
        digit = source_dict[an[i]]
        deci += digit*source_base**i
    
    arr = []
    while deci > 0:
        arr.append(deci%target_base)
        deci = deci//target_base
    arr = arr[::-1]

    ans = ""
    for i in arr:
        ans += target_dict[i]

    print(f'Case #{tc+1}: {ans}')