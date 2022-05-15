'''
Kattis - textencryption
Yet another time wasty problem :(
This one is somewhat annoying since the question is rather vague on what to do when the pointer
goes back to the same location as a char that has already been used...

The key idea for encryptions is: for each new letter in our plain text P[counter], we put it at the
first unused location accessed by pt (pointer). The movement of pointer starts from i and moves by
n every iteration until it reaches the end of the plain text.

Time: O(l**2), Space: O(l**2)
'''
while 1:
    n = int(input())
    if n == 0:
        break
    P = ("".join(input().split())).upper()
    C = list("_"*len(P))
    l = len(P)
    used = [0] * len(C)

    counter = 0
    for i in range(l):
        pt = i
        while pt < l:
            if (not used[pt]):
                C[pt] = P[counter]
                used[pt] = 1
                counter += 1
            pt += n

    print("".join(C))