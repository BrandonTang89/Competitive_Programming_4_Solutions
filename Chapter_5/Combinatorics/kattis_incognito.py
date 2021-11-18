'''
Kattis - incognito
About mutually exclusive and independant events. Just take the product of (the number of things in
each category + 1 for not wearing) - 1 since we need at least 1 thing.

Time: O(n), Space: O(n)
'''
num_tc = int(input())
for _ in range(num_tc):
    n = int(input())
    attributes = {}
    for i in range(n):
        attribute, attribute_type = input().split()
        if (not attribute_type in attributes):
            attributes[attribute_type] = 1
        attributes[attribute_type]+= 1
    
    ans = 1
    for key, val in attributes.items():
        ans *= val
    print(ans-1)