'''
Kattis - helpaphd
Easy.

Time: O(n), Space: O(1)
'''
n = int(input())
for i in range(n):
    x = input()
    if x == "P=NP":
        print("skipped")
    else:
        print(eval(x))