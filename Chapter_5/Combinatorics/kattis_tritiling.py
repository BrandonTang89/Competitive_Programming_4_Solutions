'''
Kattis - tritiling
Note that to get a(n), we have the following cases at the end:
1: 
||
||
--
2:
--
||
||
3:
--
--
--
or
------
 ----|
 ----|
eventually ending with
...------
|...----|
|...----|
(and the vertical flip of these cases)

Just use recursion with these cases to get the answer.

Time: O(n^2), Space: O(n)
'''
a = [1, 0, 3]
for i in range(3, 31):
    x = 3*a[i-2] # basic 3 cases
    for j in range(1, 40): # j horizontal blocks in the center row followed by the | block
        if (2*j + 2 > i): # too long
            break
        x += 2*a[i - 2*j - 2]
    a.append(x)
while (1):
    x = int(input())
    if (x == -1):
        break

    print(a[x])