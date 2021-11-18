'''
Kattis - catalansquare
Simply follow the task discription to "manually" count s.

Time: O(n), Space: O(n)
'''

cat = [1]
for i in range(5001):
    cat.append(cat[i]*(4*i+2)//(i+2))

n = int(input())
s = sum([cat[i]*cat[n-i] for i in range(n+1)])
print(s)