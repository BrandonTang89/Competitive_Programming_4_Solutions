for _ in range(int(input())):
    s = input()
    can = any([s[i] == s[i + 1] for i in range(len(s) - 1)])
    print(1 if can else len(s))