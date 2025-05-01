for _ in range(int(input())):
    n = int(input())
    s = str(input())
    print(sum(1 if c == '0' else n-1 for c in s))