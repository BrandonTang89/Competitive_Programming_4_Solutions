'''
Kattis - paintings
This just managed to scrap by the TLE with the appropriate optimisations. Note how we use the same
function to both count and get the best solution by ensuring that the best solution is the first
produced.

Time: O(n!), Space: O(n)
'''
num_tc = int(input())
for _ in range(num_tc):
    n = int(input())
    colors = list(input().split())
    colour_mask = {c: 1 for c in colors}

    num_hideous = int(input())
    bad = {}
    for i in range(num_hideous):
        a, b = input().split()
        if (a in bad):
            bad[a].add(b)
        else:
            bad[a] = {b}

        if (b in bad):
            bad[b].add(a)
        else:
            bad[b] = {a}

    ans = 0
    sol = []
    ans_string = ""

    def backtrack(prev):
        if (sum(colour_mask.values()) == 0):
            global ans
            ans += 1
            if(ans == 1):
                global ans_string
                ans_string = ' '.join(sol)
        for i in colors:
            if (colour_mask[i] == 0):
                continue
            if ((prev in bad) and (i in bad[prev])):
                continue
            colour_mask[i] = 0
            sol.append(i)
            backtrack(i)
            colour_mask[i] = 1
            sol.pop()

    backtrack('')
    print(ans)
    print(ans_string)
