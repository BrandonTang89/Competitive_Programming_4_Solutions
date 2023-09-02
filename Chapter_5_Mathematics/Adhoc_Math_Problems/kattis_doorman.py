'''
Kattis - doorman
Greedily select the gender that will minimise the current absolute difference.
Suppose both first and second person have the same gender, clearly picking anything
will be optimal. So we assume the first and second person have different gender.
Assume more male than female, taking female first will not be any worse than taking
the male first. By symmetry, we should always take the lacking gender first. If all the
same, we can just take either one first since we will take the other next to maintain
a difference of 0.
Time: O(n), Space: O(n)
'''
x = int(input())
diff = 0 # men - women
a = list(input())
ans = 0
while len(a) > 0:
    if diff < 0: # more women then man
        if a[0] == 'W':
            diff += 1
            a.pop(0)
        elif len(a) > 1 and a[1] == 'W':
            diff += 1
            a.pop(1)
        else:
            a.pop(0)
            diff -= 1
    else: 
        if a[0] == 'M':
            diff -= 1
            a.pop(0)
        elif len(a) > 1 and a[1] == 'M':
            diff -= 1
            a.pop(1)
        else:
            a.pop(0)
            diff += 1
    if (abs(diff) > x):
        break
    ans += 1
print(ans)