for _ in range(int(input())):
    s = list(input())
    n = len(s)
    x = 0
    # number of significant zeros
    for i in range(n - 1, -1, -1):
        if s[i] != "0":
            break
        else:
            x += 1

    print(len(s) - s.count("0") + x - 1)
