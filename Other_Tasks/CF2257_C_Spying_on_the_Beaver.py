for _ in range(int(input())):
    n = int(input())
    children: dict[int, list[int]] = {i: [] for i in range(n)}

    p = [-1] + [int(c) - 1 for c in input().split()]
    for i in range(1, n):
        children[p[i]].append(i)
    m = int(input())
    dams = {int(c) - 1 for c in input().split()}

    dams_in_sub = [-1] * n  # number of dams in subtree including i
    for u in range(n - 1, -1, -1):
        dams_in_sub[u] = (u in dams) + sum(dams_in_sub[c] for c in children[u])

    needed: list[int] = []

    can_reach = [False] * n
    can_reach[0] = True
    for u in range(n):
        if not can_reach[u]:
            continue

        if u in dams:
            for c in children[u]:
                if dams_in_sub[c] > 0:
                    needed.append(c)
                    can_reach[c] = True
        else:
            # need to guard all except the first rel child
            seen_first = False
            for c in children[u]:
                if dams_in_sub[c] > 0:
                    if seen_first:
                        needed.append(c)
                    else:
                        seen_first = True
                    can_reach[c] = True

    print(len(needed), end=" ")
    print(" ".join(str(x + 1) for x in needed))
