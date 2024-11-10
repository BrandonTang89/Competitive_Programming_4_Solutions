for _ in range(int(input())):
    n, a, b = map(int, input().split())
    moves = input()

    dx = {"N": 0, "S": 0, "E": 1, "W": -1}
    dy = {"N": 1, "S": -1, "E": 0, "W": 0}
    x, y = 0, 0

    found = False
    for _ in range(30):
        for move in moves:
            x += dx[move]
            y += dy[move]

            if x == a and y == b:
                found = True
                break

        if found:
            break

    if found:
        print("YES")
    else:
        print("NO")