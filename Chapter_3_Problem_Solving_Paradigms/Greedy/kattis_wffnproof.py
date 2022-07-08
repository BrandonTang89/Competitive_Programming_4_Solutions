'''
Kattis - wffnproof
Observe that the longest WFF can be of the form NNNNN..NNNXXXX..XXXxxx.xxx where X is a non-N upper case letter
and x is a lowercase letter, and the number of xs is 1 more than the number of Xs. As such, we can first replace
N with @ which has a lower ascii value than A then sort the string. We can then determine the highest number of
xs allowed then print the string, ignoring some Xs or xs as required.

Time: O(n log n), Space: O(n)'''
while 1:
    x = input()
    if x == "0":
        exit()

    x = x.replace('N', '@')
    x = sorted(list(x))

    num_lower = sum(1 if i.islower() else 0 for i in x)
    num_upper = sum(1 if i.isupper() else 0 for i in x)

    if num_lower == 0:
        print("no WFF possible")
        continue

    num_lower -= 1
    num_lower = min(num_lower, num_upper)
    num_upper = num_lower
    num_lower += 1

    for i in x:
        if (i == '@'):
            print('N', end='')
        elif (i.islower() and num_lower):
            print(i, end='')
            num_lower -= 1
        elif (i.isupper() and num_upper):
            print(i, end='')
            num_upper -= 1

    print()
