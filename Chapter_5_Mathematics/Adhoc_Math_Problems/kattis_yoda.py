'''
Kattis - Yoda
A relatively simple problem, just follow the instructions.

Time: O(max(len(x), len(y))), Space: O(max(len(x), len(y)))
'''
x = input()
y = input()

while len(x) > len(y):
    y = '0' + y
while len(y) > len(x):
    x = '0' + x

x = list(int(i) for i in x)
y = list(int(i) for i in y)

res_x = ""
res_y = ""
for i in range(0, len(x)):
    if (x[i] >= y[i]):
        res_x += str(x[i])
    if (y[i] >= x[i]):
        res_y += str(y[i])

if res_x != '':
    print(int(res_x))
else:
    print("YODA")

if res_y != '':
    print(int(res_y))
else:
    print("YODA")