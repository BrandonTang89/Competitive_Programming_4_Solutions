'''
Kattis - bitsequializer
Note that the order of the input doesn't really matter, only for each char in S, what the
corresponding char in T is. So we can reduce the input to 4 integers one for each case of
x[i] != y[i]. Now, we just use the greedy strategy that we should always repair (0-1 and 1-0)
together. Then from there, we look at different cases to determine the rest of the algorithm.

Time: O(n), Space: O(n)
'''
num_tc = int(input())
for tc in range(num_tc):
    x, y = input(), input()
    a = b = c = d = 0
    for i in range(len(x)):
        if x[i] != y[i]:
            if x[i] == '0' and y[i] == '1': a += 1
            elif x[i] == '1' and y[i] == '0': b += 1
            elif x[i] == '?' and y[i] == '1': c += 1
            elif x[i] == '?' and y[i] == '0': d += 1
    
   # print(a, b, c, d)
    ans = 0
    ans += min(a, b)
    a, b = a - min(a, b), b - min(a, b)
    
    if b == 0:
        ans += a + c + d
    else:
        if b > c:
            ans = -1
        else:
            ans += c + d + b
    
    print(f"Case {tc+1}: {ans}")